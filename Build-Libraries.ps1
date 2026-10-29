$ErrorActionPreference = "Stop"

function Invoke-CheckedCommand {
    param(
        [Parameter(Mandatory = $true)]
        [string] $Command,
        [Parameter(Mandatory = $true)]
        [string[]] $Arguments
    )

    & $Command @Arguments
    if ($LASTEXITCODE -ne 0) {
        throw "$Command failed with exit code $LASTEXITCODE."
    }
}

if (-not (Get-Command msbuild -ErrorAction SilentlyContinue)) {
    throw "MSBuild was not found. Run this script from a Visual Studio Developer PowerShell."
}
if (-not (Get-Command dotnet -ErrorAction SilentlyContinue)) {
    throw ".NET SDK was not found. Install the .NET 11 SDK before building."
}
if (-not (dotnet --list-sdks | Where-Object { $_ -match '^11\.' })) {
    throw ".NET 11 SDK was not found. Install the .NET 11 SDK before building."
}
if (-not (Get-Command nuget -ErrorAction SilentlyContinue)) {
    throw "NuGet.exe was not found. Install NuGet.exe and ensure it is on PATH."
}

$sdkLines = @(& dotnet --list-sdks)
$sdkLine = $sdkLines | Where-Object { $_ -match '^11\.' } | Select-Object -Last 1
if (-not $sdkLine) {
    throw ".NET 11 SDK was not found. Install the .NET 11 SDK before building."
}
if ($sdkLine -notmatch '^(?<Version>\S+)\s+\[(?<SdkRoot>.+)\]$') {
    throw "Could not determine the installed .NET 11 SDK path from: $sdkLine"
}

$sdkVersion = $Matches.Version
$sdkInstallRoot = $Matches.SdkRoot
$sdkRoot = Join-Path $sdkInstallRoot $sdkVersion
$env:MSBuildSDKsPath = Join-Path $sdkRoot "Sdks"

$dotnetRoots = @(
    (Split-Path $sdkInstallRoot -Parent),
    $env:DOTNET_ROOT_X64,
    $env:DOTNET_ROOT_X86,
    (Join-Path $env:ProgramW6432 "dotnet"),
    (Join-Path ${env:ProgramFiles(x86)} "dotnet"),
    (Join-Path $env:LOCALAPPDATA "dotnet-sdk-x86")
) | Where-Object { $_ -and (Test-Path (Join-Path $_ "packs")) } | Select-Object -Unique

$runtimePackVersion = $null
$x64PackRoot = $null
foreach ($root in $dotnetRoots) {
    $frameworkPacks = Join-Path $root "packs\Microsoft.NETCore.App.Ref"
    $candidate = Get-ChildItem $frameworkPacks -Directory -ErrorAction SilentlyContinue |
        Where-Object { $_.Name -like "11.*" } |
        Sort-Object Name -Descending |
        Select-Object -First 1
    if ($candidate -and (Test-Path (Join-Path $root "packs\Microsoft.NETCore.App.Host.win-x64\$($candidate.Name)"))) {
        $runtimePackVersion = $candidate.Name
        $x64PackRoot = $root
        break
    }
}
if (-not $runtimePackVersion) {
    throw "The .NET 11 x64 reference and host packs were not found."
}

$x86PackRoot = $null
foreach ($root in $dotnetRoots) {
    if (Test-Path (Join-Path $root "packs\Microsoft.NETCore.App.Host.win-x86\$runtimePackVersion")) {
        $x86PackRoot = $root
        break
    }
}
if (-not $x86PackRoot) {
    throw "The .NET $runtimePackVersion x86 host pack is missing. Install the matching x86 .NET SDK alongside the x64 SDK."
}

$temporaryPackRoot = $null
if (($x64PackRoot -ne $x86PackRoot) -or ($x64PackRoot -ne (Split-Path $sdkInstallRoot -Parent))) {
    $temporaryPackRoot = Join-Path $env:TEMP "xlw-dotnet-packs-$PID"
    $env:NetCoreTargetingPackRoot = $temporaryPackRoot

    foreach ($packName in @("Microsoft.NETCore.App.Ref", "Microsoft.NETCore.App.Host.win-x64")) {
        $source = Join-Path $x64PackRoot "packs\$packName"
        $destination = Join-Path $temporaryPackRoot $packName
        New-Item -ItemType Directory -Force -Path $destination | Out-Null
        Copy-Item -Path (Join-Path $source "*") -Destination $destination -Recurse -Force
    }

    $x86PackSource = Join-Path $x86PackRoot "packs\Microsoft.NETCore.App.Host.win-x86\$runtimePackVersion"
    $x86PackDestination = Join-Path $temporaryPackRoot "Microsoft.NETCore.App.Host.win-x86\$runtimePackVersion"
    New-Item -ItemType Directory -Force -Path $x86PackDestination | Out-Null
    Copy-Item -Path (Join-Path $x86PackSource "*") -Destination $x86PackDestination -Recurse -Force
}

Push-Location $PSScriptRoot
try {
    Write-Host "Step 1/4: restore the native packager."
    Invoke-CheckedCommand "dotnet" @("restore", "xlw\NugetPackager\NugetPackager.csproj")

    Write-Host "Step 2/4: build and package native xlw."
    Invoke-CheckedCommand "msbuild" @("xlw\NugetPackager\NugetPackager.csproj")

    Write-Host "Step 3/4: restore the .NET 11 projects."
    Invoke-CheckedCommand "dotnet" @("restore", "xlwDotNet\Builder\Builder.csproj")
    Invoke-CheckedCommand "dotnet" @("restore", "xlwDotNet\Attributes\Attributes.csproj")
    Invoke-CheckedCommand "dotnet" @("restore", "xlwDotNet\DotNetInterfaceGenerator\DotNetInterfaceGenerator.csproj")
    Invoke-CheckedCommand "dotnet" @("restore", "xlwDotNet\NugetPackager\NugetPackager.csproj")

    Write-Host "Step 4/4: build and package xlwDotNet."
    Invoke-CheckedCommand "msbuild" @("xlwDotNet\NugetPackager\NugetPackager.csproj")
}
finally {
    Pop-Location
    if ($temporaryPackRoot -and (Test-Path $temporaryPackRoot)) {
        Remove-Item -LiteralPath $temporaryPackRoot -Recurse -Force
    }
}

Write-Host "Both library packages were built in nuget_pack\."

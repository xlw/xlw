# Building the XLW libraries

The repository produces two packages, and they must be built in dependency order:

1. `xlw` contains the native VC143 library, headers, and the native `InterfaceGenerator`.
2. `xlwDotNet` contains the .NET 11 attribute assembly, C++/CLI bridge, and `DotNetInterfaceGenerator`, plus the native files copied from the `xlw` build.

Run `.\Build-Libraries.ps1` from a Visual Studio Developer PowerShell at the repository root. Install the .NET 11 SDK targeting packs for both x64 and x86: the C++/CLI bridge requires the architecture-specific IJW host pack for each build. The script checks for MSBuild, both host packs, the .NET 11 SDK, and `nuget.exe`, restores the native packager, then builds both packages in the required order. The resulting `.nupkg` files are placed in `nuget_pack\`.

The script performs these steps:

1. Restore `xlw\NugetPackager\NugetPackager.csproj` for its .NET 10 packaging host.
2. Build the native NugetPackager with Visual Studio MSBuild. This builds the native library for Win32 and x64 in Debug and Release, compiles the native `InterfaceGenerator`, writes the shared `xlw.version.props`, and packages `xlw`.
3. Restore the .NET 11 Builder, DotNetInterfaceGenerator, and NugetPackager projects.
4. Build `xlwDotNet\NugetPackager\NugetPackager.csproj` with Visual Studio MSBuild. The build script sets `MSBuildSDKsPath` to .NET 11 while retaining Visual C++ project support. Its Builder compiles the C++/CLI bridge against the native `xlw` library, then builds the managed `DotNetInterfaceGenerator`; the packager includes those outputs and the native files in `xlwDotNet`.

Do not build the `xlwDotNet` package first: it imports `xlw.version.props` and links the native library produced in step 1.

## Why there are two interface generators

The generators have different inputs and outputs; one does not replace the other:

| Generator | Input | Generated output | Used for |
|---|---|---|---|
| `DotNetInterfaceGenerator.exe` | Compiled C# assembly with XLW attributes | Native AOT mode: C# unmanaged exports and native marshalling shims; legacy mode: C++/CLI wrappers and `AssemblyFinder.cpp` | C# XLLs only |
| `InterfaceGenerator.exe` | C++ interface header | Excel XLL registration/wrapper source | Native C++ XLLs, and after the C# generator for C# XLLs |

Native AOT is the default for C# XLLs. After the C# project compiles, these steps run in order:

1. `DotNetInterfaceGenerator.exe` reflects over the assembly and emits C# Native AOT exports, native marshalling shims, and an interface header.
2. `InterfaceGenerator.exe` reads that header and emits Excel registration code.
3. `dotnet publish` compiles the C# exports into a native DLL; MSBuild compiles the shims and registration code with VC143 and links the XLL. The shim loads the native DLL by an absolute path derived from the XLL's own location when an exported C# function is called.

The resulting `.xll` and companion native `*.NET.dll` are placed beside each other in the project output directory; both files are required. To build the repository's x64 test add-in, first build the libraries as described above, then run from the repository root with Visual Studio MSBuild and the installed .NET 11 SDK:

```powershell
msbuild .\xlwDotNet\DevAndTestProject\VS16\Addin\Template.csproj /p:Configuration=Release /p:Platform=x64 /p:MSBuildSDKsPath="<.NET 11 SDK path>\Sdks"
```

The test `.xll` is written to `xlwDotNet\DevAndTestProject\VS16\Addin\Release\x64\net11.0\Template.xll`. Set `XLWNativeAot=false` to use the legacy C++/CLI wrapper pipeline instead.

In the legacy pipeline, `DotNetInterfaceGenerator.exe` emits C++/CLI wrappers and `AssemblyFinder.cpp`; the native interface generator still emits Excel registration code, and MSBuild compiles the wrappers with CLR support before linking the XLL. This mode does not run Native AOT publish.

For a native C++ XLL, only `InterfaceGenerator.exe` is needed. The NuGet build targets invoke these generators automatically; the app project should not need separate generator build commands.

Use the root script rather than invoking the packagers independently: it selects the .NET 11 SDK for Visual Studio MSBuild and makes the architecture-specific targeting packs available to the C++/CLI build.

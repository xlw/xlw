# Getting started with XLW

This guide walks through creating and using an Excel XLL with XLW in either
C++ or C#. An XLL is an Excel add-in implemented as a Windows DLL. XLW generates
the Excel-facing registration code so you can focus on the functions you want
to use in worksheets.

## Before you start

XLW builds Windows XLLs. You need:

- Windows and a desktop version of Microsoft Excel.
- Visual Studio with the **Desktop development with C++** workload and the
  **VC143 (Visual Studio 2022) C++ toolset** installed.
- The XLW NuGet package (`xlw`) for C++ projects, or `xlwDotNet` for C#
  projects.
- For C# projects, the **.NET 11 SDK** as well as the Visual Studio C++ tools.
  The C# route uses the native compiler and linker to produce an XLL.
- An XLL built for the same architecture as Excel: choose `x64` for 64-bit
  Excel or `Win32` for 32-bit Excel.

If you are unsure which Excel architecture you have, open Excel and choose
**File > Account > About Excel**. The first line identifies 32-bit or 64-bit.
Build and test using the matching platform.

## Build a C++ XLL

### 1. Create a project

In Visual Studio, create a **Dynamic-Link Library (DLL)** C++ project. XLW
changes the built DLL's extension to `.xll`. Use the VC143 toolset and set the
project platform to match Excel (`x64` or `Win32`).

### 2. Install the `xlw` package

Right-click the C++ project, choose **Manage NuGet Packages**, search for
`xlw`, and install it. Alternatively, in Visual Studio's Package Manager
Console, run:

```powershell
Install-Package xlw
```

The package supplies XLW's native headers and libraries, its interface
generator, and MSBuild integration. It also adds a starter `cppinterface.h`
and `source.cpp` to the project. If you do not see the package, check that
NuGet.org is enabled as a package source.

### 3. Declare the Excel function

Open `cppinterface.h`. Declare each function that Excel should call in this
header. The comments after the return type and parameters become descriptions
in Excel's function wizard.

```cpp
#include <xlw/MyContainers.h>

using namespace xlw;

//<xlw:libraryname=MyFunctions

double // Add two numbers
Add(double left,  // First number
    double right  // Second number
);
```

The `libraryname` line groups the functions under a name in Excel. Keep the
function declaration in the interface header; put its implementation in a
`.cpp` source file.

### 4. Implement the function

In `source.cpp`, include the interface header and define the function. The
signature must match the declaration.

```cpp
#include "cppinterface.h"

double Add(double left, double right)
{
    return left + right;
}
```

### 5. Build and load the add-in

Choose **Build > Build Solution** in Visual Studio. The XLW build integration
runs `InterfaceGenerator` for the interface header, compiles the generated
registration code, and produces an `.xll` file in the project's build output
folder.

In Excel, choose **File > Options > Add-ins**. At the bottom, select **Excel
Add-ins** in the **Manage** list and click **Go**. Click **Browse**, select the
generated `.xll`, and approve Excel's prompt if you trust the file. The
function is then available in a worksheet, for example:

```excel
=Add(2,3)
```

When you change the interface or implementation, rebuild the project and
reload the XLL in Excel to test the updated add-in.

## Build a C# XLL

### 1. Create a class library

In Visual Studio, create a **Class Library** project. Set its target framework
to `net11.0` and its platform to match the architecture of Excel:

```xml
<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <TargetFramework>net11.0</TargetFramework>
    <Platforms>x64</Platforms>
  </PropertyGroup>
</Project>
```

Use `Win32`/`x86` instead of `x64` when building for 32-bit Excel. The project
also needs the VC143 C++ tools: XLW uses them to compile the generated native
XLL wrappers.

### 2. Install the `xlwDotNet` package

Right-click the class library, choose **Manage NuGet Packages**, search for
`xlwDotNet`, and install it. Or run this in the Package Manager Console:

```powershell
Install-Package xlwDotNet
```

The package adds the XLW build targets and the attributes used to mark C#
methods as Excel functions.

### 3. Write an Excel function

Add a public static method and decorate it with `[ExcelExport]`. The attribute
argument is the function description shown in Excel's function wizard.
`[Parameter]` supplies descriptions for the function's arguments.

```csharp
using xlwDotNet;

public static class WorksheetFunctions
{
    [ExcelExport("Add two numbers")]
    public static double Add(
        [Parameter("First number")] double left,
        [Parameter("Second number")] double right)
    {
        return left + right;
    }
}
```

XLW's default C# build uses **.NET Native AOT**. The build reflects over the
compiled assembly, generates the Excel registration code and native wrappers,
publishes the C# exports as a native library, and links the XLL. You do not
need to run either interface generator yourself.

The default Native AOT path supports numeric and Boolean scalars, strings,
one-dimensional numeric arrays, and numeric matrices. Custom C# types can be
used by adding a supported conversion method marked `[TypeRegister]`. Generic
exports and by-reference parameters are not supported. If an export cannot be
represented by the Native AOT generator, the build reports the unsupported
method or type.

### 4. Build and load the add-in

Choose **Build > Build Solution** in Visual Studio. The output folder contains
both:

- The `.xll` file that you load in Excel.
- A companion native `*.NET.dll` containing the compiled C# exports.

Keep these two files together. When an exported C# function is first called,
the XLL loads its companion library from the same directory. To load it,
follow the Excel **File > Options > Add-ins > Manage Excel Add-ins > Go >
Browse** steps in the C++ section above.

The example `Add` function can then be called from a cell:

```excel
=Add(2,3)
```

The C# library is compiled natively; end users do not need to install the .NET
11 runtime to use a Native AOT build. The target platform still needs the
appropriate Microsoft Visual C++ runtime when it is not already present.

### Optional: use the legacy C++/CLI build

The Native AOT route is the default. To use the older C++/CLI wrapper pipeline,
set this property in the C# project's `.csproj`:

```xml
<PropertyGroup>
  <XLWNativeAot>false</XLWNativeAot>
</PropertyGroup>
```

This route builds the XLL with CLR support and uses the managed bridge shipped
in `xlwDotNet`. Prefer the default Native AOT option for new projects.

## Troubleshooting

- **Excel does not list or load the XLL:** confirm that the add-in architecture
  matches Excel, and that you selected the `.xll` rather than the companion
  `*.NET.dll`.
- **A C# XLL loads but its functions fail:** keep the companion `*.NET.dll`
  beside the `.xll`; both files must be copied or distributed together.
- **The build cannot find MSBuild, the compiler, or C++ project targets:**
  install Visual Studio's **Desktop development with C++** workload and the
  VC143 toolset, then build from Visual Studio or a Developer PowerShell.
- **The C# project cannot find the .NET SDK:** install the .NET 11 SDK and
  check that `dotnet --list-sdks` lists an 11.x SDK.
- **NuGet cannot find `xlw` or `xlwDotNet`:** enable NuGet.org in Visual
  Studio's package sources. For unreleased CI packages, configure the XLW
  Feedz source described in the repository's [README](README.md).
- **A changed function does not appear in Excel:** rebuild the project, unload
  the old add-in in Excel, and browse to the newly built `.xll`.

## Building XLW itself

Most users who are writing an add-in only need to install the appropriate
NuGet package. If you are building the XLW libraries from this repository
instead, follow [BUILDING.md](BUILDING.md). It explains the package build
order, prerequisites, and why the C# and native builds use two interface
generators.

# XLW

XLW helps you build Excel add-ins (`.xll` files) in **C++** or **C#**. It
generates the Excel registration code and integrates with Visual Studio, so you
can focus on writing worksheet functions.

> **New to XLW? Start here:** [Getting started: build your first C++ or C# XLL](GETTING_STARTED.md).
> The guide walks through setup, installing the package, writing a function,
> building the add-in, and loading it in Excel.

## Choose your language

| | C++ | C# |
|---|---|---|
| NuGet package | [`xlw`](https://www.nuget.org/packages/xlw/) | [`xlwDotNet`](https://www.nuget.org/packages/xlwDotNet/) |
| Project type | Visual Studio C++ Dynamic-Link Library | .NET class library |
| Requirements | Windows, desktop Excel, Visual Studio with the **VC143** C++ toolset | Same, plus the **.NET 11 SDK** |

Build for the same architecture as Excel: usually `x64`; use `Win32`/`x86`
for 32-bit Excel. The C# build also uses the VC143 compiler to produce the
native XLL. It uses Native AOT by default, so end users do not need the .NET
runtime.

### Quick start

1. Install the package for your language from NuGet using the links above.
2. Add worksheet functions to your project:
   - **C++:** declare functions in the XLW interface header and implement them
     in a `.cpp` file.
   - **C#:** write public static methods and mark them with `[ExcelExport]`.
3. Build the project in Visual Studio.
4. In Excel, load the generated `.xll` from **File > Options > Add-ins**.
   For C# add-ins, keep the generated companion `*.NET.dll` beside the `.xll`.

Follow [the getting-started guide](GETTING_STARTED.md) for a complete example
in each language, including the code, project settings, and Excel loading
steps.

## Using CI packages

For packages that are not yet published on NuGet.org, add the XLW CI feed as a
NuGet package source:

```xml
<?xml version="1.0" encoding="utf-8"?>
<configuration>
  <packageSources>
    <clear />
    <add key="XLW" value="https://f.feedz.io/xlw/xlw/nuget/index.json" />
    <add key="NuGet.org" value="https://api.nuget.org/v3/index.json" />
  </packageSources>
</configuration>
```

## Example projects

For complete projects to learn from, see the [C++ examples](https://github.com/xlw/xlw-Examples)
and [C# examples](https://github.com/xlw/xlwDotNet-Examples). They show how XLW
is used in real add-ins and complement the step-by-step
[getting-started guide](GETTING_STARTED.md).

## Building or contributing to XLW

Most add-in developers only need the NuGet package and the
[getting-started guide](GETTING_STARTED.md). To build the libraries in this
repository, see [BUILDING.md](BUILDING.md).

XLW is looking for developers to help maintain and develop the project. This
repository was forked from [John's XLW repository](https://github.com/JohnAdders/xlw),
originally imported from [SourceForge](https://sourceforge.net/projects/xlw/).


| dev | master | prerelease | release |
|:----------:|:----------:|:----------:|:--------------:|
|![Build Nuget](https://github.com/xlw/xlw/workflows/Build%20Nuget/badge.svg?branch=dev)|![Build Nuget](https://github.com/xlw/xlw/workflows/Build%20Nuget/badge.svg?branch=master) |![Build Nuget](https://github.com/xlw/xlw/workflows/Build%20Nuget/badge.svg?branch=prerelease)|![Build Nuget](https://github.com/xlw/xlw/workflows/Build%20Nuget/badge.svg?branch=release)|


# *This project is looking for developers to maintain and take the project forward* #




#### [xlw nuget](https://www.nuget.org/packages/xlw/)   
#### [xlwDotNet nuget](https://www.nuget.org/packages/xlwDotNet/)

## Using CI builds

To use CI builds add the following nuget feed:

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


# **XLW**

XLW aims to facilitate the development of Excel addins with ease. It attempts to do this by wrapping the old Excel XLL C API in essentially a facade which is simplier to consume hence leaving the developer 
to focus on the buisness logic. To this end it hides away intricacies of interfacing with the low level Excel C API.

The concept behind XLW's approach is simplicity. There is nothing clever here !
#### **C++**
- You write your C++ functions
- The interface genertor generates the Excel C API bindings from your C++ header files. 

#### **C#**
- You write your C# functions
- `DotNetInterfaceGenerator` reflects over your C# assembly and emits C++/CLI wrappers.
- `InterfaceGenerator` converts those wrappers into Excel registration code. Native C++ XLLs use this generator directly on their C++ interface header.

It's really not more complicated than that. Moreover, the process should be very transparent and the entry cost for any developer to modify, update or fix XLW should be extremely low. 


xlw is being updated.

This repo was originally forked from [John's XLW repo](https://github.com/JohnAdders/xlw) which itself was imported from it's original home at [SourceForge](https://sourceforge.net/projects/xlw/)


Native XLLs use the Visual C++ 14.3 toolset (VC143). Support for older Visual Studio versions and GCC has been dropped.

The C# XLL build targets .NET 11. The native XLL component remains built with VC143.

For repository build prerequisites, package ordering, and the two generator roles, see [BUILDING.md](BUILDING.md).
For step-by-step beginner instructions for creating C++ and C# XLLs, see [GETTING_STARTED.md](GETTING_STARTED.md).

An initial dev nuget package  for building C/C++ xlls is avaialable at [xlw@nuget](https://www.nuget.org/packages/xlw/).\
And a nuget package for building C# xlls is available at [xlwDotNet@nuget](https://www.nuget.org/packages/xlwDotNet).

---

## xlw
xlw for building C++/C xlls has not changed much at this point.
To build a C++ xll :
1. Create an empty C++ DLL project.
2. Add the xlw nuget package.

*Requires MSVC toolset v143 (VC143).

#### Creating a C++ XLL for Excel with XLW
[![Creating a C++ XLL for Excel with XLW](https://img.youtube.com/vi/k0V6nvWjMnI/0.jpg)](https://www.youtube.com/watch?v=k0V6nvWjMnI)      

---

## xlwDotNet
Use a current Visual Studio/MSVC installation with the VC143 toolset and the .NET 11 SDK. C# XLLs use Native AOT by default, compiling C# exports into a native library. The XLL loads this companion library from its own directory when a C# export is called, so keep the generated `*.NET.dll` beside the `.xll`. Set `XLWNativeAot=false` to use the legacy C++/CLI wrapper pipeline.

To build a C# xll :
1. Create a new .NET 11 class library project.
2. Open the .csproj file with a text editor and set the  `TargetFramework` and  `Platform` for example
```xml
<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <TargetFramework>net11.0</TargetFramework>
    <Platforms>x64</Platforms>
  </PropertyGroup>
</Project>
```
3. Add the xlwDotNet nuget package.

The package targets generate both wrapper layers and build the XLL automatically. Native AOT output includes the `.xll` and companion native `*.NET.dll` in the project output directory. See [BUILDING.md](BUILDING.md) for the generator sequence and a repository test-add-in build command.

#### Creating a C\# XLL for Excel with XLW
[![Creating a C\# XLL for Excel with XLW](https://img.youtube.com/vi/GH0Phpo5S7k/0.jpg)](https://www.youtube.com/watch?v=GH0Phpo5S7k)


## ... And Just Because We Can

#### Embedding ASP.NET Core (kestrel) in an xll 

[![Historical XLL with Embedded ASP.NET Core demo built against .NET 5 Preview](https://img.youtube.com/vi/mQyRnNpG2C4/0.jpg)](https://www.youtube.com/watch?v=mQyRnNpG2C4)

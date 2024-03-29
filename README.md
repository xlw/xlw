
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
- The Dotnet Interface generator uses reflection to generate C++/CLI bindings for your C#
- The (C++) interface genertor generates the  Excel C API bindings from your C++/CLI header files

It's really not more complicated than that. Moreover, the process should be very transparent and the entry cost for any developer to modify, update or fix XLW should be extremely low. 


xlw is being updated.

This repo was originally forked from [John's XLW repo](https://github.com/JohnAdders/xlw) which itself was imported from it's original home at [SourceForge](https://sourceforge.net/projects/xlw/)


This version will only support Visual Studio 2020 for now. Support for all previous Visual Studio versions has been dropped. All support for gcc has also been dropped.

Support is being added for building xlls against .NET 6 & .NET Framework 4.7.2


An initial dev nuget package  for building C/C++ xlls is avaialable at [xlw@nuget](https://www.nuget.org/packages/xlw/).\
And a nuget package for building C# xlls is available at [xlwDotNet@nuget](https://www.nuget.org/packages/xlwDotNet).

---

## xlw
xlw for building C++/C xlls has not changed much at this point.
To build a C++ xll :
1. Create an empty C++ DLL project.
2. Add the xlw nuget package.

*Required MSVC Toolset v143

#### Creating a C++ XLL for Excel with XLW
[![Creating a C++ XLL for Excel with XLW](https://img.youtube.com/vi/k0V6nvWjMnI/0.jpg)](https://www.youtube.com/watch?v=k0V6nvWjMnI)      

---

## xlwDotNet
Only VS2020 is supported right now. 
To build a C# xll :
1. Create a new .NET Core library project. 
2. Open the .csproj file with a text editor and set the  `TargetFramework` and  `Platform` for example
```xml
<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <TargetFrameworks>net6.0</TargetFrameworks>
    <Platforms>x64</Platforms>
  </PropertyGroup>
</Project>
```
3. Add the xlwDotNet nuget package.

#### Creating a C\# XLL for Excel with XLW
[![Creating a C\# XLL for Excel with XLW](https://img.youtube.com/vi/GH0Phpo5S7k/0.jpg)](https://www.youtube.com/watch?v=GH0Phpo5S7k)


## ... And Just Because We Can

#### Embedding ASP.NET Core (kestrel) in an xll 

[![XLL with Embedded ASP.NET Core (Kestrel) - Built with XLW against .NET 5 Preview](https://img.youtube.com/vi/mQyRnNpG2C4/0.jpg)](https://www.youtube.com/watch?v=mQyRnNpG2C4)



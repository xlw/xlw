# **XLW 20**
xlw is being updated.

This repo was originally forked from [John's XLW repo](https://github.com/JohnAdders/xlw) which itself was imported from it's original home at [SourceForge](https://sourceforge.net/projects/xlw/)


This version will only support Visual Studio 2019. In this fork all support for previous Visual Studio versions has been dropped. All support for gcc has also been dropped.\
Support is being added for building xlls against .NET CORE & .NET Framework 4.7.2 simultaneously

## xlw
xlw for building C++/C xlls has not changed much at this point. There is one template project `xlw\xlw\Template_Projects\Template.sln`

## xlwDotNet
The Template xll (xlw\xlwDotNet\Template_Projects\VS16\Template.sln) has been compiled against .NET 5.0.0-preview6 and .NET Framework 4.7.2  and opens in Excel 2019 and works as expected.\
It doesn't currently  work with .NET Core 3.1 and this is being investigated.



1. The VS Solution `xlw\xlw\xlw20.sln` will build xlw. The resulting libraries go to  `xlw\xlw\lib`

```
  lib -> 
      InterfaceGenerator.exe
      Win32 ->
            xlw-vc142-mt-6_0_0.lib
            xlw-vc142-mt-gd-6_0_0.lib
      x64   ->\
            xlw-vc142-mt-6_0_0.lib
            xlw-vc142-mt-gd-6_0_0.lib
```
2. The VS Solution  `xlw\xlwDotNet\xlwDotNet.sln` will build xlwDotNet (expecting xlw to have already been built).\
 Specifically the C# project `Builder` builds the main library and the main library should not be built explicitly. This is because Buidler configures the MSBuild properties for
 xlwDotNet to build.
 ```
  lib -> 
      Debug ->
            Win32 ->
                  net5.0 ->
                        xlwDotNet-vc142-mt-gd-6_0_0.dll
                        DotNetInterfaceGenerator.exe
                  net472 ->
                        xlwDotNet-vc142-mt-gd-6_0_0.dll
                        DotNetInterfaceGenerator.exe
            x64 ->
                  net5.0 ->
                        xlwDotNet-vc142-mt-gd-6_0_0.dll
                        DotNetInterfaceGenerator.exe
                  net472 ->
                        xlwDotNet-vc142-mt-gd-6_0_0.dll
                        DotNetInterfaceGenerator.exe
      Release ->
            Win32 ->
                  net5.0 ->
                        xlwDotNet-vc142-mt-6_0_0.dll
                        DotNetInterfaceGenerator.exe
                  net472 ->
                        xlwDotNet-vc142-mt-6_0_0.dll
                        DotNetInterfaceGenerator.exe
            x64 ->
                  net5.0 ->
                        xlwDotNet-vc142-mt-6_0_0.dll
                        DotNetInterfaceGenerator.exe
                  net472 ->
                        xlwDotNet-vc142-mt-6_0_0.dll
                        DotNetInterfaceGenerator.exe
```

The  .NET Template project `\xlw\xlwDotNet\Template_Projects\VS16\Template.sln` is setup to built an xll for .NET Framework 4.7.2 and .NET 5.0.0
``` <PropertyGroup>
  <TargetFrameworks>net472;net5.0</TargetFrameworks>
    <Platforms>x64;x86</Platforms>
  </PropertyGroup>
```

~~To run the .NET 5 xll you have to add the directory containing the the xll to your Path (not so for the .NET Framework version). This needs to be fixed.
Seems like it's discussed [here](https://github.com/dotnet/runtime/issues/38231)~~


Attempting to build xlwDotNet against .NET Core 3.1 gives the following build error:
``` 
1>C:\Program Files\dotnet\sdk\5.0.100-preview.5.20279.10\Sdks\Microsoft.NET.Sdk\targets\Microsoft.NET.Sdk.targets(565,5): error NETSDK1114: Unable to find a .NET Core IJW host. The .NET Core IJW host is only available on .NET Core 3.1 or higher when targeting Windows.
```



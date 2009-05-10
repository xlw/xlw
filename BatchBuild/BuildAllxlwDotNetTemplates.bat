"C:\Python26\python.exe" prepareDotNetTemplateProject.py

REM Debug

set DevEnvDir=C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\

"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   "C:\Temp\xlwDotNetTemplate_Projects\VS8\Template.sln"  /t:rebuild  /property:Configuration=Debug  >> xlwDotNetTemplate_Debug_8.log 2>&1 

set DevEnvDir=C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE\

"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   "C:\Temp\xlwDotNetTemplate_Projects\VS9\Template.sln"  /t:rebuild  /property:Configuration=Debug  >> xlwDotNetTemplate_Debug_9.log 2>&1 


REM Release

set DevEnvDir=C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\

"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   "C:\Temp\xlwDotNetTemplate_Projects\VS8\Template.sln"  /t:rebuild  /property:Configuration=Release  >> xlwDotNetTemplate_Release_8.log 2>&1 

set DevEnvDir=C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE\

"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   "C:\Temp\xlwDotNetTemplate_Projects\VS9\Template.sln"  /t:rebuild  /property:Configuration=Release  >> xlwDotNetTemplate_Release_9.log 2>&1 

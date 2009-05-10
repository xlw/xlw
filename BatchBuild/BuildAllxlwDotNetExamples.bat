
REM Debug

set DevEnvDir=C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\

"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   ..\xlwDotNet\Example\VS8\Example.sln /t:rebuild   /property:Configuration=Debug >> xlwDotNetExample_Debug_8.log 2>&1 
"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   ..\xlwDotNet\XtraExamples\NonPassive\VS8\NonPassive.sln /t:rebuild /property:Configuration=Debug  >> xlwDotNetNonPassive_Debug_8.log 2>&1 
"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   ..\xlwDotNet\XtraExamples\Python\VS8\PythonDemo.sln /t:rebuild /property:Configuration=Debug  >> xlwDotNetPython_Debug_8.log 2>&1 
"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   ..\xlwDotNet\XtraExamples\RTDExample\VS8\RTDExample.sln /t:rebuild /property:Configuration=Debug  >> xlwDotNetRTDExample_Debug_8.log 2>&1 


set DevEnvDir=C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE\

"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   ..\xlwDotNet\Example\VS9\Example.sln /t:rebuild  /property:Configuration=Debug >> xlwDotNetExample_Debug_9.log 2>&1 
"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   ..\xlwDotNet\XtraExamples\NonPassive\VS9\NonPassive.sln /t:rebuild /property:Configuration=Debug  >> xlwDotNetNonPassive_Debug_9.log 2>&1 
"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   ..\xlwDotNet\XtraExamples\Python\VS9\PythonDemo.sln /t:rebuild /property:Configuration=Debug  >> xlwDotNetPython_Debug_9.log 2>&1 
"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   ..\xlwDotNet\XtraExamples\RTDExample\VS9\RTDExample.sln /t:rebuild  /property:Configuration=Debug >> xlwDotNetRTDExample_Debug_9.log 2>&1 

REM Release

set DevEnvDir=C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\

"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   ..\xlwDotNet\Example\VS8\Example.sln /t:rebuild  c >> xlwDotNetExample_Release_8.log 2>&1 
"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   ..\xlwDotNet\XtraExamples\NonPassive\VS8\NonPassive.sln /t:rebuild /property:Configuration=Release  >> xlwDotNetNonPassive_Release_8.log 2>&1 
"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   ..\xlwDotNet\XtraExamples\Python\VS8\PythonDemo.sln /t:rebuild /property:Configuration=Release  >> xlwDotNetPython_Release_8.log 2>&1 
"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   ..\xlwDotNet\XtraExamples\RTDExample\VS8\RTDExample.sln /t:rebuild  /property:Configuration=Release >> xlwDotNetRTDExample_Release_8.log 2>&1 


set DevEnvDir=C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE\

"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   ..\xlwDotNet\Example\VS9\Example.sln /t:rebuild /property:Configuration=Release  >> xlwDotNetExample_Release_9.log 2>&1 
"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   ..\xlwDotNet\XtraExamples\NonPassive\VS9\NonPassive.sln /t:rebuild /property:Configuration=Release  >> xlwDotNetNonPassive_Release_9.log 2>&1 
"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   ..\xlwDotNet\XtraExamples\Python\VS9\PythonDemo.sln /t:rebuild /property:Configuration=Release  >> xlwDotNetPython_Release_9.log 2>&1 
"C:\WINDOWS\Microsoft.NET\Framework\v3.5\MSBuild"   ..\xlwDotNet\XtraExamples\RTDExample\VS9\RTDExample.sln /t:rebuild  /property:Configuration=Release >> xlwDotNetRTDExample_Release_9.log 2>&1 

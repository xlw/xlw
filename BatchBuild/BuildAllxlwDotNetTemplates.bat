@SETLOCAL
@IF NOT DEFINED XLW_FOUND_PROGRAMS CALL FindPrograms.bat
@IF ERRORLEVEL 1 ECHO Can't find all required programs & exit /b 1

%PYTHON% prepareDotNetTemplateProject.py

CALL BuildProjectNet.bat "C:\Temp\xlwDotNetTemplate Projects\CSharp" xlwDotNetTemplateCS
CALL BuildProjectNet.bat "C:\Temp\xlwDotNetTemplate Projects\FSharp" xlwDotNetTemplateFS
CALL BuildProjectNet.bat "C:\Temp\xlwDotNetTemplate Projects\VisualBasic" xlwDotNetTemplateVB

REM Special Code for Hybrid at the moment

@SET LOG_ROOT=%CD%\xlwDotNetTemplateHybrid-VS8-
@SET VSPROJ="C:\Temp\xlwDotNetTemplate Projects\Hybrid_Cpp_CSharp_XLLs\VS8_PRO\HybridTemplate.sln"
SET DevEnvDir=%VS8DEVENVDIR%
SET vcbuildtoolpath=%VS8TOOLS%
%NET35BUILD% %VSPROJ% /target:XLL /t:clean /property:Configuration=Debug /property:Platform=x86 >> "%LOG_ROOT%x86-Debug.log" 2>&1 
%NET35BUILD% %VSPROJ% /target:XLL /t:clean /property:Configuration=Release /property:Platform=x86 >> "%LOG_ROOT%x86-Release.log" 2>&1 
%NET35BUILD% %VSPROJ% /target:XLL /t:clean /property:Configuration=Debug /property:Platform=x64 >> "%LOG_ROOT%x64-Debug.log" 2>&1 
%NET35BUILD% %VSPROJ% /target:XLL /t:clean /property:Configuration=Release /property:Platform=x64 >> "%LOG_ROOT%x64-Release.log" 2>&1 
%NET35BUILD% %VSPROJ% /target:XLL /t:build /property:Configuration=Debug /property:Platform=x86 >> "%LOG_ROOT%x86-Debug.log" 2>&1 
%NET35BUILD% %VSPROJ% /target:XLL /t:build /property:Configuration=Release /property:Platform=x86 >> "%LOG_ROOT%x86-Release.log" 2>&1 
%NET35BUILD% %VSPROJ% /target:XLL /t:build /property:Configuration=Debug /property:Platform=x64 >> "%LOG_ROOT%x64-Debug.log" 2>&1 
%NET35BUILD% %VSPROJ% /target:XLL /t:build /property:Configuration=Release /property:Platform=x64 >> "%LOG_ROOT%x64-Release.log" 2>&1 

@SET LOG_ROOT=%CD%\xlwDotNetTemplateHybrid-VS9-
@SET VSPROJ="C:\Temp\xlwDotNetTemplate Projects\Hybrid_Cpp_CSharp_XLLs\VS9_PRO\HybridTemplate.sln"
SET DevEnvDir=%VS9DEVENVDIR%
SET vcbuildtoolpath=%VS9TOOLS%
%NET35BUILD% %VSPROJ% /target:XLL /t:clean /property:Configuration=Debug /property:Platform=x86 >> "%LOG_ROOT%x86-Debug.log" 2>&1 
%NET35BUILD% %VSPROJ% /target:XLL /t:clean /property:Configuration=Release /property:Platform=x86 >> "%LOG_ROOT%x86-Release.log" 2>&1 
%NET35BUILD% %VSPROJ% /target:XLL /t:clean /property:Configuration=Debug /property:Platform=x64 >> "%LOG_ROOT%x64-Debug.log" 2>&1 
%NET35BUILD% %VSPROJ% /target:XLL /t:clean /property:Configuration=Release /property:Platform=x64 >> "%LOG_ROOT%x64-Release.log" 2>&1 
%NET35BUILD% %VSPROJ% /target:XLL /t:build /property:Configuration=Debug /property:Platform=x86 >> "%LOG_ROOT%x86-Debug.log" 2>&1 
%NET35BUILD% %VSPROJ% /target:XLL /t:build /property:Configuration=Release /property:Platform=x86 >> "%LOG_ROOT%x86-Release.log" 2>&1 
%NET35BUILD% %VSPROJ% /target:XLL /t:build /property:Configuration=Debug /property:Platform=x64 >> "%LOG_ROOT%x64-Debug.log" 2>&1 
%NET35BUILD% %VSPROJ% /target:XLL /t:build /property:Configuration=Release /property:Platform=x64 >> "%LOG_ROOT%x64-Release.log" 2>&1 

@SET LOG_ROOT=%CD%\xlwDotNetTemplateHybrid-VS10-
@SET VSPROJ="C:\Temp\xlwDotNetTemplate Projects\Hybrid_Cpp_CSharp_XLLs\VS10_PRO\HybridTemplate.sln"
SET DevEnvDir=%VS10DEVENVDIR%
SET vcbuildtoolpath=%VS10TOOLS%
%NET4BUILD% %VSPROJ% /target:XLL /t:clean /property:Configuration=Debug /property:Platform=x86 >> "%LOG_ROOT%x86-Debug.log" 2>&1 
%NET4BUILD% %VSPROJ% /target:XLL /t:clean /property:Configuration=Release /property:Platform=x86 >> "%LOG_ROOT%x86-Release.log" 2>&1 
%NET4BUILD% %VSPROJ% /target:XLL /t:clean /property:Configuration=Debug /property:Platform=x64 >> "%LOG_ROOT%x64-Debug.log" 2>&1 
%NET4BUILD% %VSPROJ% /target:XLL /t:clean /property:Configuration=Release /property:Platform=x64 >> "%LOG_ROOT%x64-Release.log" 2>&1 
%NET4BUILD% %VSPROJ% /target:XLL /t:build /property:Configuration=Debug /property:Platform=x86 >> "%LOG_ROOT%x86-Debug.log" 2>&1 
%NET4BUILD% %VSPROJ% /target:XLL /t:build /property:Configuration=Release /property:Platform=x86 >> "%LOG_ROOT%x86-Release.log" 2>&1 
%NET4BUILD% %VSPROJ% /target:XLL /t:build /property:Configuration=Debug /property:Platform=x64 >> "%LOG_ROOT%x64-Debug.log" 2>&1 
%NET4BUILD% %VSPROJ% /target:XLL /t:build /property:Configuration=Release /property:Platform=x64 >> "%LOG_ROOT%x64-Release.log" 2>&1 

@SET LOG_ROOT=%CD%\xlwDotNetTemplateHybrid-VS11-
@SET VSPROJ="C:\Temp\xlwDotNetTemplate Projects\Hybrid_Cpp_CSharp_XLLs\VS11_PRO\HybridTemplate.sln"
SET DevEnvDir=%VS11DEVENVDIR%
SET vcbuildtoolpath=%VS11TOOLS%
%NET4BUILD% %VSPROJ% /target:XLL /t:clean /property:Configuration=Debug /property:Platform=x86 >> "%LOG_ROOT%x86-Debug.log" 2>&1 
%NET4BUILD% %VSPROJ% /target:XLL /t:clean /property:Configuration=Release /property:Platform=x86 >> "%LOG_ROOT%x86-Release.log" 2>&1 
%NET4BUILD% %VSPROJ% /target:XLL /t:clean /property:Configuration=Debug /property:Platform=x64 >> "%LOG_ROOT%x64-Debug.log" 2>&1 
%NET4BUILD% %VSPROJ% /target:XLL /t:clean /property:Configuration=Release /property:Platform=x64 >> "%LOG_ROOT%x64-Release.log" 2>&1 
%NET4BUILD% %VSPROJ% /target:XLL /t:build /property:Configuration=Debug /property:Platform=x86 >> "%LOG_ROOT%x86-Debug.log" 2>&1 
%NET4BUILD% %VSPROJ% /target:XLL /t:build /property:Configuration=Release /property:Platform=x86 >> "%LOG_ROOT%x86-Release.log" 2>&1 
%NET4BUILD% %VSPROJ% /target:XLL /t:build /property:Configuration=Debug /property:Platform=x64 >> "%LOG_ROOT%x64-Debug.log" 2>&1 
%NET4BUILD% %VSPROJ% /target:XLL /t:build /property:Configuration=Release /property:Platform=x64 >> "%LOG_ROOT%x64-Release.log" 2>&1 

@SET LOG_ROOT=%CD%\xlwDotNetTemplateHybrid-VS12-
@SET VSPROJ="C:\Temp\xlwDotNetTemplate Projects\Hybrid_Cpp_CSharp_XLLs\VS12_PRO\HybridTemplate.sln"
SET DevEnvDir=%VS12DEVENVDIR%
SET vcbuildtoolpath=%VS12TOOLS%
%MSBUILD12% %VSPROJ% /target:XLL /t:clean /property:Configuration=Debug /property:Platform=x86 >> "%LOG_ROOT%x86-Debug.log" 2>&1 
%MSBUILD12% %VSPROJ% /target:XLL /t:clean /property:Configuration=Release /property:Platform=x86 >> "%LOG_ROOT%x86-Release.log" 2>&1 
%MSBUILD12% %VSPROJ% /target:XLL /t:clean /property:Configuration=Debug /property:Platform=x64 >> "%LOG_ROOT%x64-Debug.log" 2>&1 
%MSBUILD12% %VSPROJ% /target:XLL /t:clean /property:Configuration=Release /property:Platform=x64 >> "%LOG_ROOT%x64-Release.log" 2>&1 
%MSBUILD12% %VSPROJ% /target:XLL /t:build /property:Configuration=Debug /property:Platform=x86 >> "%LOG_ROOT%x86-Debug.log" 2>&1 
%MSBUILD12% %VSPROJ% /target:XLL /t:build /property:Configuration=Release /property:Platform=x86 >> "%LOG_ROOT%x86-Release.log" 2>&1 
%MSBUILD12% %VSPROJ% /target:XLL /t:build /property:Configuration=Debug /property:Platform=x64 >> "%LOG_ROOT%x64-Debug.log" 2>&1 
%MSBUILD12% %VSPROJ% /target:XLL /t:build /property:Configuration=Release /property:Platform=x64 >> "%LOG_ROOT%x64-Release.log" 2>&1 


@ENDLOCAL

@SETLOCAL
@SET LOG_ROOT=%CD%\%2-VS9-
SET DevEnvDir=%VS9DEVENVDIR%
SET vcbuildtoolpath=%VS9TOOLS%
%NET35BUILD% %1 /t:rebuild /property:Configuration=Debug /property:Platform=x86 >> "%LOG_ROOT%x86-Debug.log" 2>&1 
%NET35BUILD% %1 /t:rebuild /property:Configuration=Release /property:Platform=x86 >> "%LOG_ROOT%x86-Release.log" 2>&1 
%NET35BUILD% %1 /t:rebuild /property:Configuration=Debug  /property:Platform=x64   >> "%LOG_ROOT%x64-Debug.log" 2>&1 
%NET35BUILD% %1 /t:rebuild /property:Configuration=Release /property:Platform=x64  >> "%LOG_ROOT%x64-Release.log" 2>&1 
@ENDLOCAL
@SETLOCAL
@SET LOG_ROOT=%CD%\%2-cb-
%CODEBLOCKS% --rebuild  --target="Debug" %1 >> "%LOG_ROOT%x86-Debug.log" 2>&1 
%CODEBLOCKS% --rebuild  --target="Release" %1 >> "%LOG_ROOT%x86-Release.log" 2>&1 
@ENDLOCAL
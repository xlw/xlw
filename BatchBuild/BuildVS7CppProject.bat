@SETLOCAL
@SET LOG_ROOT=%CD%\%2-VS7-
%VS7DEVENV% %1  /rebuild Debug    /out "%LOG_ROOT%x86-Debug.log"
%VS7DEVENV% %1  /rebuild Release  /out "%LOG_ROOT%x86-Release.log"
@ENDLOCAL
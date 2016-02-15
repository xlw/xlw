@SETLOCAL
@SET LOG_ROOT=%CD%\%2-VS14-
SET DevEnvDir=%VS14DEVENVDIR%
SET vcbuildtoolpath=%VS14TOOLS%
SET PATH=%VS14BIN%;%OLDPATH%

@SET X86PLATFORM=Win32
@IF "%3"=="NET" SET X86PLATFORM=x86

%MSBUILD14% /p:Configuration=Debug;Platform=%X86PLATFORM% /t:rebuild  %1  >> "%LOG_ROOT%x86-Debug.log" 2>&1 
%MSBUILD14% /p:Configuration=Release;Platform=%X86PLATFORM% /t:rebuild  %1  >> "%LOG_ROOT%x86-Release.log" 2>&1 
%MSBUILD14% /p:Configuration=Debug;Platform=x64 /t:rebuild  %1  >> "%LOG_ROOT%x64-Debug.log" 2>&1 
%MSBUILD14% /p:Configuration=Release;Platform=x64 /t:rebuild  %1  >> "%LOG_ROOT%x64-Release.log" 2>&1 
@ENDLOCAL
@SETLOCAL
@SET LOG_ROOT=%CD%\%2-gcc-
@pushd .
@cd %~p1
make BUILD=DEBUG PLATFORM=WIN32 rebuild >> "%LOG_ROOT%x86-Debug.log" 2>&1 
make BUILD=RELEASE PLATFORM=WIN32 rebuild >> "%LOG_ROOT%x86-Release.log" 2>&1 
make BUILD=DEBUG PLATFORM=x64 rebuild >> "%LOG_ROOT%x64-Debug.log" 2>&1 
make BUILD=RELEASE PLATFORM=x64 rebuild >> "%LOG_ROOT%x64-Release.log" 2>&1 
@popd
@ENDLOCAL
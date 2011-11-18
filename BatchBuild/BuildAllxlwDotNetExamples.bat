@SETLOCAL
@IF NOT DEFINED XLW_FOUND_PROGRAMS CALL FindPrograms.bat
@IF ERRORLEVEL 1 ECHO Can't find all required programs & exit /b 1

CALL BuildProjectNet.bat ..\xlwDotNet\Example xlwDotNetExample
CALL BuildProjectNet.bat ..\xlwDotNet\UserContrib\VisualBasic xlwDotNetExampleVisualBasic
REM CALL BuildProjectNet.bat ..\xlwDotNet\UserContrib\NonPassive xlwDotNetExampleNonPassive
REM CALL BuildProjectNet.bat ..\xlwDotNet\UserContrib\Python xlwDotNetExamplePython
REM CALL BuildProjectNet.bat ..\xlwDotNet\UserContrib\RTDExample xlwDotNetExampleRTD

@ENDLOCAL



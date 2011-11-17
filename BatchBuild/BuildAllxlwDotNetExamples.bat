@SETLOCAL
@IF NOT DEFINED XLW_FOUND_PROGRAMS CALL FindPrograms.bat
@IF ERRORLEVEL 1 ECHO Can't find all required programs & exit /b 1

CALL BuildProjectNet.bat ..\xlwDotNet\Example xlwDotNetExample
CALL BuildProjectNet.bat ..\xlwDotNet\UserContrib\VisualBasic xlwDotNetExampleVisualBasic
CALL BuildProjectNet.bat ..\xlwDotNet\XtraExamples\NonPassive xlwDotNetExampleNonPassive
CALL BuildProjectNet.bat ..\xlwDotNet\XtraExamples\Python xlwDotExampleNetPython
CALL BuildProjectNet.bat ..\xlwDotNet\XtraExamples\RTDExample xlwDotNetExampleRTD

@ENDLOCAL



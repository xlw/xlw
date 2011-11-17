@SETLOCAL
@SET SEPERATOR=--------------------------------------------------------------------------------

@ECHO BUILD: FindPrograms
@ECHO %SEPERATOR%

@IF NOT DEFINED XLW_FOUND_PROGRAMS CALL FindPrograms.bat
@IF ERRORLEVEL 1 ECHO Can't find all required programs & exit /b 1

@ECHO BUILD: Clean All
@ECHO %SEPERATOR%

%PYTHON% CleanAll.py
del *.log

@ECHO BUILD: Build xlw Libraries
@ECHO %SEPERATOR%

CALL BuildProjectCpp.bat ..\xlw\build xlw

@ECHO BUILD: Build Xlw Examples
@ECHO %SEPERATOR%

CALL BuildAllxlwExamples.bat

@ECHO BUILD: Build Xlw Templates
@ECHO %SEPERATOR%

CALL BuildAllxlwTemplates.bat

@ECHO BUILD: Build Xlw .NET 
@ECHO %SEPERATOR%

CALL BuildProjectCpp.bat ..\xlwDotNet\build xlwDotNet

@ECHO BUILD: Build Xlw .NET Examples
@ECHO %SEPERATOR%

CALL BuildAllxlwDotNetExamples.bat

@ECHO BUILD: Build Xlw .NET Templates
@ECHO %SEPERATOR%

CALL BuildAllxlwDotNetTemplates.bat

@ECHO BUILD: Build Xlw Documentation
@ECHO %SEPERATOR%

CALL BuildDocumentation.bat

@ENDLOCAL

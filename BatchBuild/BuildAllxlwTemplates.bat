@SETLOCAL
@IF NOT DEFINED XLW_FOUND_PROGRAMS CALL FindPrograms.bat
@IF ERRORLEVEL 1 ECHO Can't find all required programs & exit /b 1

%PYTHON% prepareTemplateProject.py

CALL BuildProjectCpp.bat "C:\TEMP\xlwTemplate Projects\" xlwTemplate

@ENDLOCAL
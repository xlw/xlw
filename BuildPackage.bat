@SETLOCAL
@SET PATH=%PATH%;%CD%\BatchBuild
@CALL BatchBuild\FindProgram.bat "NSIS\makensis.exe" NSIS
@IF ERRORLEVEL 1 ECHO Can't find NSIS & exit /b 1
@SET PATH=%PATH%;%NSISDIR%

del xlw*.exe

del *.log

%NSIS% xlwDotNetTemplate.nsi   >> xlwDotNetTemplate.log 2>&1 
%NSIS% xlwTemplate.nsi         >> xlwTemplate.log 2>&1 
%NSIS% xlwCppCLITemplate.nsi   >> xlwCppCLITemplate.log 2>&1 
%NSIS% MinGW_Installer\MinGW-Installer.nsi >> MinGW-Installer.log 2>&1
%NSIS% xlwDotNet.nsi           >> xlwDotNet.log 2>&1 

@ENDLOCAL
@SETLOCAL
@IF NOT DEFINED XLW_FOUND_PROGRAMS CALL FindPrograms.bat
@IF ERRORLEVEL 1 ECHO Can't find all required programs & exit /b 1

@SET LOG_ROOT=%CD%\xlw-doxy
@pushd .
@cd ..\xlw\docs

if not exist html mkdir html
if not exist html\sflogo.png copy /Y images\sflogo.png html\sflogo.png
if not exist html\logo_small.jpg copy /Y images\logo_small.jpg html\logo_small.jpg
if not exist html\nazcatech.jpg copy /Y images\nazcatech.jpg html\nazcatech.jpg

@SET PATH=%DOTDIR%;%PATH%
%DOXYGEN% xlw.windows.doxy >> "%LOG_ROOT%.log" 2>&1
%HTMLHELP% html\index.hhp >> "%LOG_ROOT%.log" 2>&1

@popd
@ENDLOCAL
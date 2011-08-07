@SETLOCAL
@if "%~1" == "" goto usage
@if not exist "Debug\%~1.xll" goto usage
@SET DOCGEN=Invalid
@if "%2"=="codeblocks-gcc" SET SUBDIR=bin\Debug
@if "%2"=="gcc-make" SET SUBDIR=Debug\bin
@if "%2"=="vc7" SET SUBDIR=Debug
@if "%2"=="vc8" SET SUBDIR=Debug
@if "%2"=="vc9" SET SUBDIR=Debug
@if "%2"=="vc10" SET SUBDIR=Debug
@if not exist "%SUBDIR%" goto usage
@REM ********** Set path for .net framework2.0, sandcastle,hhc ****************************
@REM assumes default install location for Html Help Workshop
@set TOOLSPATH=%ProgramFiles%
@if exist "%ProgramFiles% (x86)" set TOOLSPATH=%ProgramFiles(x86)%
@if not exist "%TOOLSPATH%\HTML Help Workshop\hhc.exe" goto prereqs
@if not exist "%DXROOT%\ProductionTools" goto prereqs
@if not exist "%windir%\Microsoft.NET\Framework\v2.0.50727" goto prereqs
@set PATH=%windir%\Microsoft.NET\Framework\v2.0.50727;%DXROOT%\ProductionTools;%TOOLSPATH%\HTML Help Workshop;%PATH%
@pushd %SUBDIR%

"%XLW%\xlw\build\%2\%SubDir%\XlwDocGen.exe" "%~1.xll"

if exist output rmdir output /s /q

call "%DXROOT%\Presentation\vs2005\copyOutput.bat" > nul

copy "%XLW%\xlw\build\sandcastle\*.maml" . > nul

BuildAssembler /config:"%XLW%\xlw\build\sandcastle\conceptual.config" .\toc.xml

@if not exist chm mkdir chm
@if not exist chm\html mkdir chm\html
@if not exist chm\icons mkdir chm\icons
@if not exist chm\scripts mkdir chm\scripts
@if not exist chm\styles mkdir chm\styles
@REM: if not exist chm\media mkdir chm\media

@xcopy output\icons\* chm\icons\ /y /r /q
@xcopy output\scripts\* chm\scripts\ /y /r /q
@xcopy output\styles\* chm\styles\ /y /r /q
@copy "%XLW%\xlw\build\sandcastle\alias.h" chm\alias.h

ChmBuilder.exe /project:"%~1" /html:Output\html /lcid:1033 /toc:.\toc.xml /out:Chm /config:.\ChmBuilder.config

DBCSFix.exe /d:Chm /l:1033 


hhc "chm\%~1.hhp"

copy "chm\%~1.chm" ..

@popd
@ENDLOCAL
@exit /b 0

:prereqs

@echo **********************************************************************
@echo Missing Software
@echo 
@echo To build help you will need the following software:
@echo Microsoft Sandcastle
@echo Microsoft HTML Help Workshop
@echo .NET 2.0 Runtime
@echo 
@echo See the Building Help files section in the Xlw Help file
@echo 
@echo If the software is not installed in the default location
@echo Edit the batch file:
@echo %XLW%\xlw\build\sandcastle\BuildChmHelp.bat
@echo **********************************************************************
@ENDLOCAL
exit /b 2

:usage
@echo **********************************************************************
@echo Usage
@echo 
@echo BuildChmHelp.bat ProjectName BuildEnvironment
@echo ProjectName: should be the name of the xll without extension
@echo              and the debug version of the xll must have been built
@echo BuildEnvironment: one of gcc-make, codeblocks-gcc, vc7, vc8, vc9, vc10
@echo **********************************************************************
@ENDLOCAL
exit /b 1

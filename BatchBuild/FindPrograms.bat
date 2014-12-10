@SET XLW_FOUND_PROGRAMS=

@echo Looking for Python
@CALL CheckFile.bat "c:\python27\python.exe" PYTHON
@CALL CheckFile.bat "c:\python32\python.exe" PYTHON
@IF "%PYTHON%" == "" ECHO Error: Can't Find Python & exit /b 1
@echo Found Python at %PYTHON%

@CALL FindProgram.bat "CodeBlocks\codeblocks.exe" CODEBLOCKS
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Microsoft Visual Studio .NET 2003\Common7\IDE\devenv.exe" VS7DEVENV
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Microsoft Visual Studio 8\Common7\IDE\devenv.exe" VS8DEVENV
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Microsoft Visual Studio 8\Common7\IDE\" VS8DEVENVDIR NOPATH
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Microsoft Visual Studio 8\vc\vcpackages" VS8TOOLS NOPATH
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Microsoft Visual Studio 8\VC\vcpackages\vcbuild.exe" VS8VSBUILD
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Microsoft Visual Studio 9.0\Common7\IDE\devenv.exe" VS9DEVENV
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Microsoft Visual Studio 9.0\Common7\IDE\" VS9DEVENVDIR NOPATH
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Microsoft Visual Studio 9.0\vc\vcpackages" VS9TOOLS NOPATH
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Microsoft Visual Studio 9.0\VC\vcpackages\vcbuild.exe" VS9VSBUILD
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Microsoft Visual Studio 10.0\Common7\IDE\devenv.exe" VS10DEVENV
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Microsoft Visual Studio 10.0\Common7\IDE\" VS10DEVENVDIR NOPATH
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Microsoft Visual Studio 10.0\vc\vcpackages" VS10TOOLS NOPATH
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Microsoft Visual Studio 10.0\vc\bin" VS10BIN NOPATH
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Microsoft Visual Studio 11.0\Common7\IDE\" VS11DEVENVDIR NOPATH
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Microsoft Visual Studio 11.0\vc\vcpackages" VS11TOOLS NOPATH
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Microsoft Visual Studio 11.0\vc\bin" VS11BIN NOPATH
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Microsoft Visual Studio 12.0\Common7\IDE\" VS12DEVENVDIR NOPATH
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Microsoft Visual Studio 12.0\vc\vcpackages" VS12TOOLS NOPATH
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Microsoft Visual Studio 12.0\vc\bin" VS12BIN NOPATH
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "MSBuild\12.0\Bin\MSBuild.exe" MSBUILD12
@IF ERRORLEVEL 1 EXIT /b 1

@echo Looking for .NET 3.5 msbuild
@CALL CheckFile.bat "C:\WINDOWS\Microsoft.NET\Framework\v3.5\msbuild.exe" NET35BUILD
@IF "%NET35BUILD%" == "" ECHO Error: Can't Find .NET 3.5 MsBuild & exit /b 1
@echo Found .NET 3.5 MsBuild at %NET35BUILD%

@echo Looking for .NET 4 msbuild
@CALL CheckFile.bat "C:\WINDOWS\Microsoft.NET\Framework\v4.0.30319\msbuild.exe" NET4BUILD
@IF "%NET4BUILD%" == "" ECHO Error: Can't Find .NET 4 MsBuild & exit /b 1
@echo Found .NET 4 MsBuild at %NET4BUILD%

@CALL FindProgram.bat "doxygen\bin\doxygen.exe" DOXYGEN
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "Graphviz2.26.3\bin" DOTPATH NOPATH
@IF ERRORLEVEL 1 EXIT /b 1

@CALL FindProgram.bat "HTML Help Workshop\hhc.exe" HTMLHELP
@IF ERRORLEVEL 1 EXIT /b 1

@SET XLW_FOUND_PROGRAMS=YES

@exit /b 0
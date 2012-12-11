@SETLOCAL
@IF NOT DEFINED XLW_FOUND_PROGRAMS CALL FindPrograms.bat
@IF ERRORLEVEL 1 ECHO Can't find all required programs & exit /b 1

CALL BuildProjectNet.bat "..\xlwDotNet\Examples\Start Here - Example" xlwDotNetExampleStartHere
CALL BuildProjectNet.bat "..\xlwDotNet\Examples\TypeRegister" xlwDotNetExampleTypeRegister
CALL BuildProjectNet.bat "..\xlwDotNet\Examples\ReflectionFactory" xlwDotNetExampleReflectionFactory
CALL BuildProjectNet.bat "..\xlwDotNet\Examples\ObjectCacheDemo" xlwDotNetExampleObjectCacheDemo
CALL BuildProjectNet.bat ..\xlwDotNet\Examples\VisualBasic xlwDotNetExampleVisualBasic
REM CALL BuildProjectNet.bat ..\xlwDotNet\UserContrib\NonPassive xlwDotNetExampleNonPassive
REM CALL BuildProjectNet.bat ..\xlwDotNet\UserContrib\Python xlwDotNetExamplePython
REM CALL BuildProjectNet.bat ..\xlwDotNet\UserContrib\RTDExample xlwDotNetExampleRTD

@ENDLOCAL



@REM Build Documentation for every debug xll
@for %%1 in (Debug\*.xll) do call "%XLW%\xlw\build\sandcastle\BuildChmHelp.bat" "%%~n1" vc7


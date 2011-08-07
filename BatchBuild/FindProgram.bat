@ECHO Looking for %2
@SET %2=
@CALL CheckFile.bat "%ProgramFiles%\%~1" %2 %3
@CALL CheckFile.bat "%ProgramFiles(x86)%\%~1" %2 %3
@IF not defined %2 ECHO Error: Can't Find %2 & exit /b 1
@ECHO Found %2
@EXIT /b 0
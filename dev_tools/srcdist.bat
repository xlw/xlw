
rem start /low srcdist D:\CygRoot\archive\AutomatedBuilds xlw R010100
rem start /low srcdist D:\CygRoot\archive\AutomatedBuilds xlw


echo "clean old crap"
if exist %2-*-src.zip del %2-*-src.zip
FOR /F %%i IN ('DIR /B %2*') DO rmdir /S /Q %%i
if %2==xlw goto XLWCVSROOT
if %2==QuantLib goto QLCVSROOT
exit

:XLWCVSROOT
    SET CVSROOT=:pserver:anonymous@cvs.xlw.sf.net:/cvsroot/xlw
    goto DONECVSROOT
:QLCVSROOT
    SET CVSROOT=:pserver:anonymous@cvs.quantlib.org:/cvsroot/quantlib
:DONECVSROOT


if %3.==. goto MAKEITTODAY
set RELEASESUFFIX
set CVSTAG=-r %3
goto DONERELEASESUFFIX

:MAKEITTODAY
rem this batch works iff date format is american-style : MM\DD\YYYY
rem            if it would be italian-style DD\MM\YYYY then you have to
rem                       substitute %%k%%i%%j    with %%k%%j%%i
FOR /F "tokens=2-4 delims=/ "  %%i IN ('date /T') DO set RELEASESUFFIX=-%%k%%i%%j
set CVSTAG=-D tomorrow
:DONERELEASESUFFIX


cvs -z3 export %CVSTAG% %2
cd %2
ren %2.nsi old%2.nsi
sed -e "s/-cvs/%RELEASESUFFIX%/" old%2.nsi > %2.nsi
del old%2.nsi
cd Docs
ren %2.doxy old%2.doxy
sed -e "s/-cvs/%RELEASESUFFIX%/" old%2.doxy > %2.doxy
del old%2.doxy
cd ..\xlw
ren EXCEL32_API.h oldEXCEL32_API.h
sed -e "s/-cvs/%RELEASESUFFIX%/" oldEXCEL32_API.h > EXCEL32_API.h
del oldEXCEL32_API.h
cd ..\..\

rem VERSIONNUMBER should be read in the checked out files
set VERSIONNUMBER=1.1.1a0
ren %2 %2-%VERSIONNUMBER%%RELEASESUFFIX%
zip -q -r %2-%VERSIONNUMBER%%RELEASESUFFIX%-src.zip %2-%VERSIONNUMBER%%RELEASESUFFIX%

if exist %2-%VERSIONNUMBER%%RELEASESUFFIX%-src.zip del %1\%2\%2-*-src.zip
move %2-%VERSIONNUMBER%%RELEASESUFFIX%-src.zip %1\%2

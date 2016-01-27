@SETLOCAL
@if exist "%~1\codeblocks-gcc" for %%f in ("%~1\codeblocks-gcc\*.workspace") do CALL BuildCodeblocksProject.bat "%%f" %2
@if exist "%~1\gcc-make\Makefile" CALL BuildGccProject.bat "%~1\gcc-make\Makefile" %2
@if exist "%~1\vc10" for %%f in ("%~1\vc10\*.sln") do CALL BuildVS10Project.bat "%%f" %2
@if exist "%~1\vc11" for %%f in ("%~1\vc11\*.sln") do CALL BuildVS11Project.bat "%%f" %2
@if exist "%~1\vc12" for %%f in ("%~1\vc12\*.sln") do CALL BuildVS12Project.bat "%%f" %2
@if exist "%~1\VS10" for %%f in ("%~1\VS10\*.sln") do CALL BuildVS10Project.bat "%%f" %2
@if exist "%~1\VS11" for %%f in ("%~1\VS11\*.sln") do CALL BuildVS11Project.bat "%%f" %2
@if exist "%~1\VS12" for %%f in ("%~1\VS12\*.sln") do CALL BuildVS12Project.bat "%%f" %2

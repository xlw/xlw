@if exist "%~1\VS8" for %%f in ("%~1\VS8\*.sln") do CALL BuildVS8NetProject.bat "%%f" %2
@if exist "%~1\VS9" for %%f in ("%~1\VS9\*.sln") do CALL BuildVS9NetProject.bat "%%f" %2
@if exist "%~1\VS10" for %%f in ("%~1\VS10\*.sln") do CALL BuildVS10Project.bat "%%f" %2 NET
@if exist "%~1\VS11" for %%f in ("%~1\VS11\*.sln") do CALL BuildVS11Project.bat "%%f" %2 NET
@if exist "%~1\VS12" for %%f in ("%~1\VS12\*.sln") do CALL BuildVS12Project.bat "%%f" %2 NET
@if exist "%~1\VS8_PRO" for %%f in ("%~1\VS8_PRO\*.sln") do CALL BuildVS8NetProject.bat "%%f" %2
@if exist "%~1\VS9_PRO" for %%f in ("%~1\VS9_PRO\*.sln") do CALL BuildVS9NetProject.bat "%%f" %2
@if exist "%~1\VS10_PRO" for %%f in ("%~1\VS10_PRO\*.sln") do CALL BuildVS10Project.bat "%%f" %2 NET
@if exist "%~1\VS11_PRO" for %%f in ("%~1\VS11_PRO\*.sln") do CALL BuildVS11Project.bat "%%f" %2 NET
@if exist "%~1\VS12_PRO" for %%f in ("%~1\VS12_PRO\*.sln") do CALL BuildVS12Project.bat "%%f" %2 NET
@if exist "%~1\VB2005" for %%f in ("%~1\VB2005\*.sln") do CALL BuildVS8NetProject.bat "%%f" %2
@if exist "%~1\VB2008" for %%f in ("%~1\VB2008\*.sln") do CALL BuildVS9NetProject.bat "%%f" %2

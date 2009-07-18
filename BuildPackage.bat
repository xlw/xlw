
set PATH=%PATH%;"C:\Program Files\NSIS"

del xlw*.exe

del *.log

makensis.exe xlwDotNetTemplate.nsi   >> xlwDotNetTemplate.log 2>&1 
makensis.exe xlwTemplate.nsi         >> xlwTemplate.log 2>&1 
makensis.exe MinGW_Installer\MinGW-Installer.nsi >> MinGW-Installer.log 2>&1
makensis.exe xlwDotNet.nsi           >> xlwDotNet.log 2>&1 


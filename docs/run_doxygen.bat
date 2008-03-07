if not exist html mkdir html
if not exist html\sfnetlogo.png copy /Y images\sfnetlogo.png html\sfnetlogo.png
"C:\Program Files\doxygen\bin\doxygen.exe" xlw.windows.doxy

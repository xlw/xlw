if not exist html mkdir html
if not exist html\sfnetlogo.png copy /Y images\sfnetlogo.png html\sfnetlogo.png
if not exist html\logo_small.jpg copy /Y images\logo_small.jpg html\logo_small.jpg
"C:\Program Files\doxygen\bin\doxygen.exe" xlw.windows.doxy

if not exist html mkdir html
if not exist html\sflogo.png copy /Y images\sflogo.png html\sflogo.png
if not exist html\logo_small.jpg copy /Y images\logo_small.jpg html\logo_small.jpg
if not exist html\nazcatech.jpg copy /Y images\nazcatech.jpg html\nazcatech.jpg
"C:\Program Files (x86)\doxygen\bin\doxygen.exe" xlw.windows.doxy

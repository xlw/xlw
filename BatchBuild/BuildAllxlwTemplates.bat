"C:\Python26\python.exe" prepareTemplateProject.py

make -f xlwTemplateMakefile DEV=devcpp
make -f xlwTemplateMakefile DEV=gcc-make



"C:\Program Files\Microsoft Visual Studio .NET 2003\Common7\IDE\devenv.exe"   "C:\TEMP\xlwTemplate Projects\vc7\Template.sln"  /rebuild Debug    /out xlwTemplate7Debug.log
"C:\Program Files\Microsoft Visual Studio .NET 2003\Common7\IDE\devenv.exe"   "C:\TEMP\xlwTemplate Projects\vc7\Template.sln"  /rebuild Release  /out xlwTemplate7Release.log
"C:\Program Files\Microsoft Visual Studio 8\VC\vcpackages\vcbuild.exe" /rebuild    "C:\TEMP\xlwTemplate Projects\vc8\Template.sln"  >> xlwTemplate8.log 2>&1 
"C:\Program Files\Microsoft Visual Studio 9.0\VC\vcpackages\vcbuild.exe" /rebuild  "C:\TEMP\xlwTemplate Projects\vc9\Template.sln"  >> xlwTemplate9.log 2>&1 


# Microsoft Developer Studio Generated NMAKE File, Based on test.dsp
!IF "$(CFG)" == ""
CFG=test - Win32 OnTheEdgeDebug
!MESSAGE No configuration specified. Defaulting to test - Win32 OnTheEdgeDebug.
!ENDIF 

!IF "$(CFG)" != "test - Win32 Release" && "$(CFG)" != "test - Win32 Debug" && "$(CFG)" != "test - Win32 OnTheEdgeDebug" && "$(CFG)" != "test - Win32 OnTheEdgeRelease"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "test.mak" CFG="test - Win32 OnTheEdgeDebug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "test - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "test - Win32 OnTheEdgeDebug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "test - Win32 OnTheEdgeRelease" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "test - Win32 Release"

OUTDIR=.\build\Release
INTDIR=.\build\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\xll\Win32\VisualStudio\Release\test.xll"

!ELSE 

ALL : "excel32 - Win32 Release" ".\xll\Win32\VisualStudio\Release\test.xll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"excel32 - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\test.exp"
	-@erase "$(OUTDIR)\test.lib"
	-@erase ".\xll\Win32\VisualStudio\Release\test.xll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "$(XLW_DIR)" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EXCEL32_NOIMPORTEXPORT" /Fp"$(INTDIR)\test.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\test.pdb" /machine:I386 /out:"xll\Win32\VisualStudio\Release\test.xll" /implib:"$(OUTDIR)\test.lib" /libpath:"$(XLW_DIR)\lib\Win32\VisualStudio" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"..\lib\Win32\VisualStudio\excel32.lib"

".\xll\Win32\VisualStudio\Release\test.xll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

OUTDIR=.\build\Debug
INTDIR=.\build\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\xll\Win32\VisualStudio\Debug\test.xll"

!ELSE 

ALL : "excel32 - Win32 Debug" ".\xll\Win32\VisualStudio\Debug\test.xll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"excel32 - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\test.exp"
	-@erase "$(OUTDIR)\test.lib"
	-@erase "$(OUTDIR)\test.pdb"
	-@erase ".\xll\Win32\VisualStudio\Debug\test.ilk"
	-@erase ".\xll\Win32\VisualStudio\Debug\test.xll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(XLW_DIR)" /D "XLW_DEBUG" /D "_DEBUG" /D "TEST_EXPORTS" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EXCEL32_NOIMPORTEXPORT" /Fp"$(INTDIR)\test.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\test.pdb" /debug /machine:I386 /out:"xll\Win32\VisualStudio\Debug\test.xll" /implib:"$(OUTDIR)\test.lib" /pdbtype:sept /libpath:"$(XLW_DIR)\lib\Win32\VisualStudio" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"..\lib\Win32\VisualStudio\excel32d.lib"

".\xll\Win32\VisualStudio\Debug\test.xll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "test - Win32 OnTheEdgeDebug"

OUTDIR=.\build\OnTheEdgeDebug
INTDIR=.\build\OnTheEdgeDebug

!IF "$(RECURSE)" == "0" 

ALL : ".\xll\Win32\VisualStudio\Debug\test.xll"

!ELSE 

ALL : "excel32 - Win32 OnTheEdgeDebug" ".\xll\Win32\VisualStudio\Debug\test.xll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"excel32 - Win32 OnTheEdgeDebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\test.exp"
	-@erase "$(OUTDIR)\test.lib"
	-@erase "$(OUTDIR)\test.pdb"
	-@erase ".\xll\Win32\VisualStudio\Debug\test.ilk"
	-@erase ".\xll\Win32\VisualStudio\Debug\test.xll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\\" /D "XLW_DEBUG" /D "_DEBUG" /D "TEST_EXPORTS" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EXCEL32_NOIMPORTEXPORT" /Fp"$(INTDIR)\test.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\test.pdb" /debug /machine:I386 /out:"xll\Win32\VisualStudio\Debug\test.xll" /implib:"$(OUTDIR)\test.lib" /pdbtype:sept /libpath:"..\lib\Win32\VisualStudio" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"..\lib\Win32\VisualStudio\excel32d.lib"

".\xll\Win32\VisualStudio\Debug\test.xll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "test - Win32 OnTheEdgeRelease"

OUTDIR=.\build\OnTheEdgeRelease
INTDIR=.\build\OnTheEdgeRelease

!IF "$(RECURSE)" == "0" 

ALL : ".\xll\Win32\VisualStudio\Release\test.xll"

!ELSE 

ALL : "excel32 - Win32 OnTheEdgeRelease" ".\xll\Win32\VisualStudio\Release\test.xll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"excel32 - Win32 OnTheEdgeReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\test.exp"
	-@erase "$(OUTDIR)\test.lib"
	-@erase ".\xll\Win32\VisualStudio\Release\test.xll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\\" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EXCEL32_NOIMPORTEXPORT" /Fp"$(INTDIR)\test.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\test.pdb" /machine:I386 /out:"xll\Win32\VisualStudio\Release\test.xll" /implib:"$(OUTDIR)\test.lib" /libpath:"..\lib\Win32\VisualStudio" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"..\lib\Win32\VisualStudio\excel32.lib"

".\xll\Win32\VisualStudio\Release\test.xll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("test.dep")
!INCLUDE "test.dep"
!ELSE 
!MESSAGE Warning: cannot find "test.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "test - Win32 Release" || "$(CFG)" == "test - Win32 Debug" || "$(CFG)" == "test - Win32 OnTheEdgeDebug" || "$(CFG)" == "test - Win32 OnTheEdgeRelease"

!IF  "$(CFG)" == "test - Win32 Release"

"excel32 - Win32 Release" : 
   cd "\Projects\xlw"
   $(MAKE) /$(MAKEFLAGS) /F .\excel32.mak CFG="excel32 - Win32 Release" 
   cd ".\test"

"excel32 - Win32 ReleaseCLEAN" : 
   cd "\Projects\xlw"
   $(MAKE) /$(MAKEFLAGS) /F .\excel32.mak CFG="excel32 - Win32 Release" RECURSE=1 CLEAN 
   cd ".\test"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

"excel32 - Win32 Debug" : 
   cd "\Projects\xlw"
   $(MAKE) /$(MAKEFLAGS) /F .\excel32.mak CFG="excel32 - Win32 Debug" 
   cd ".\test"

"excel32 - Win32 DebugCLEAN" : 
   cd "\Projects\xlw"
   $(MAKE) /$(MAKEFLAGS) /F .\excel32.mak CFG="excel32 - Win32 Debug" RECURSE=1 CLEAN 
   cd ".\test"

!ELSEIF  "$(CFG)" == "test - Win32 OnTheEdgeDebug"

"excel32 - Win32 OnTheEdgeDebug" : 
   cd "\Projects\xlw"
   $(MAKE) /$(MAKEFLAGS) /F .\excel32.mak CFG="excel32 - Win32 OnTheEdgeDebug" 
   cd ".\test"

"excel32 - Win32 OnTheEdgeDebugCLEAN" : 
   cd "\Projects\xlw"
   $(MAKE) /$(MAKEFLAGS) /F .\excel32.mak CFG="excel32 - Win32 OnTheEdgeDebug" RECURSE=1 CLEAN 
   cd ".\test"

!ELSEIF  "$(CFG)" == "test - Win32 OnTheEdgeRelease"

"excel32 - Win32 OnTheEdgeRelease" : 
   cd "\Projects\xlw"
   $(MAKE) /$(MAKEFLAGS) /F .\excel32.mak CFG="excel32 - Win32 OnTheEdgeRelease" 
   cd ".\test"

"excel32 - Win32 OnTheEdgeReleaseCLEAN" : 
   cd "\Projects\xlw"
   $(MAKE) /$(MAKEFLAGS) /F .\excel32.mak CFG="excel32 - Win32 OnTheEdgeRelease" RECURSE=1 CLEAN 
   cd ".\test"

!ENDIF 

SOURCE=.\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 


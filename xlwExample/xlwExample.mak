# Microsoft Developer Studio Generated NMAKE File, Based on xlwExample.dsp
!IF "$(CFG)" == ""
CFG=xlwExample - Win32 OnTheEdgeDebug
!MESSAGE No configuration specified. Defaulting to xlwExample - Win32 OnTheEdgeDebug.
!ENDIF 

!IF "$(CFG)" != "xlwExample - Win32 Release" && "$(CFG)" != "xlwExample - Win32 Debug" && "$(CFG)" != "xlwExample - Win32 OnTheEdgeDebug" && "$(CFG)" != "xlwExample - Win32 OnTheEdgeRelease"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "xlwExample.mak" CFG="xlwExample - Win32 OnTheEdgeDebug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xlwExample - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xlwExample - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xlwExample - Win32 OnTheEdgeDebug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xlwExample - Win32 OnTheEdgeRelease" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "xlwExample - Win32 Release"

OUTDIR=.\build\Release
INTDIR=.\build\Release
# Begin Custom Macros
OutDir=.\build\Release
# End Custom Macros

ALL : ".\xll\Win32\VisualStudio\xlwExample.xll" "$(OUTDIR)\xlwExample.bsc"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\xlwExample.obj"
	-@erase "$(INTDIR)\xlwExample.sbr"
	-@erase "$(OUTDIR)\xlwExample.bsc"
	-@erase "$(OUTDIR)\xlwExample.exp"
	-@erase "$(OUTDIR)\xlwExample.lib"
	-@erase ".\xll\Win32\VisualStudio\xlwExample.xll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "$(XLW_DIR)" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\xlwExample.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xlwExample.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\xlwExample.sbr"

"$(OUTDIR)\xlwExample.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\xlwExample.pdb" /machine:I386 /out:"xll\Win32\VisualStudio\xlwExample.xll" /implib:"$(OUTDIR)\xlwExample.lib" /libpath:"$(XLW_DIR)\lib\Win32\VisualStudio" 
LINK32_OBJS= \
	"$(INTDIR)\xlwExample.obj"

".\xll\Win32\VisualStudio\xlwExample.xll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xlwExample - Win32 Debug"

OUTDIR=.\build\Debug
INTDIR=.\build\Debug
# Begin Custom Macros
OutDir=.\build\Debug
# End Custom Macros

ALL : ".\xll\Win32\VisualStudio\xlwExampled.xll" "$(OUTDIR)\xlwExample.bsc"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\xlwExample.obj"
	-@erase "$(INTDIR)\xlwExample.sbr"
	-@erase "$(OUTDIR)\xlwExample.bsc"
	-@erase "$(OUTDIR)\xlwExampled.exp"
	-@erase "$(OUTDIR)\xlwExampled.lib"
	-@erase "$(OUTDIR)\xlwExampled.pdb"
	-@erase ".\xll\Win32\VisualStudio\xlwExampled.ilk"
	-@erase ".\xll\Win32\VisualStudio\xlwExampled.xll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(XLW_DIR)" /D "XLW_DEBUG" /D "_DEBUG" /D "TEST_EXPORTS" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\xlwExample.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xlwExample.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\xlwExample.sbr"

"$(OUTDIR)\xlwExample.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\xlwExampled.pdb" /debug /machine:I386 /out:"xll\Win32\VisualStudio\xlwExampled.xll" /implib:"$(OUTDIR)\xlwExampled.lib" /pdbtype:sept /libpath:"$(XLW_DIR)\lib\Win32\VisualStudio" 
LINK32_OBJS= \
	"$(INTDIR)\xlwExample.obj"

".\xll\Win32\VisualStudio\xlwExampled.xll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xlwExample - Win32 OnTheEdgeDebug"

OUTDIR=.\build\OnTheEdgeDebug
INTDIR=.\build\OnTheEdgeDebug
# Begin Custom Macros
OutDir=.\build\OnTheEdgeDebug
# End Custom Macros

ALL : ".\xll\Win32\VisualStudio\xlwExampled.xll" "$(OUTDIR)\xlwExample.bsc"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\xlwExample.obj"
	-@erase "$(INTDIR)\xlwExample.sbr"
	-@erase "$(OUTDIR)\xlwExample.bsc"
	-@erase "$(OUTDIR)\xlwExampled.exp"
	-@erase "$(OUTDIR)\xlwExampled.lib"
	-@erase "$(OUTDIR)\xlwExampled.pdb"
	-@erase ".\xll\Win32\VisualStudio\xlwExampled.ilk"
	-@erase ".\xll\Win32\VisualStudio\xlwExampled.xll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\\" /D "XLW_DEBUG" /D "_DEBUG" /D "TEST_EXPORTS" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\xlwExample.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xlwExample.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\xlwExample.sbr"

"$(OUTDIR)\xlwExample.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\xlwExampled.pdb" /debug /machine:I386 /out:"xll\Win32\VisualStudio\xlwExampled.xll" /implib:"$(OUTDIR)\xlwExampled.lib" /pdbtype:sept /libpath:"..\lib\Win32\VisualStudio" 
LINK32_OBJS= \
	"$(INTDIR)\xlwExample.obj"

".\xll\Win32\VisualStudio\xlwExampled.xll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xlwExample - Win32 OnTheEdgeRelease"

OUTDIR=.\build\OnTheEdgeRelease
INTDIR=.\build\OnTheEdgeRelease
# Begin Custom Macros
OutDir=.\build\OnTheEdgeRelease
# End Custom Macros

ALL : ".\xll\Win32\VisualStudio\xlwExample.xll" "$(OUTDIR)\xlwExample.bsc"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\xlwExample.obj"
	-@erase "$(INTDIR)\xlwExample.sbr"
	-@erase "$(OUTDIR)\xlwExample.bsc"
	-@erase "$(OUTDIR)\xlwExample.exp"
	-@erase "$(OUTDIR)\xlwExample.lib"
	-@erase ".\xll\Win32\VisualStudio\xlwExample.xll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\\" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\xlwExample.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xlwExample.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\xlwExample.sbr"

"$(OUTDIR)\xlwExample.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\xlwExample.pdb" /machine:I386 /out:".\xll\Win32\VisualStudio\xlwExample.xll" /implib:"$(OUTDIR)\xlwExample.lib" /libpath:"..\lib\Win32\VisualStudio" 
LINK32_OBJS= \
	"$(INTDIR)\xlwExample.obj"

".\xll\Win32\VisualStudio\xlwExample.xll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("xlwExample.dep")
!INCLUDE "xlwExample.dep"
!ELSE 
!MESSAGE Warning: cannot find "xlwExample.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "xlwExample - Win32 Release" || "$(CFG)" == "xlwExample - Win32 Debug" || "$(CFG)" == "xlwExample - Win32 OnTheEdgeDebug" || "$(CFG)" == "xlwExample - Win32 OnTheEdgeRelease"
SOURCE=.\xlwExample.cpp

"$(INTDIR)\xlwExample.obj"	"$(INTDIR)\xlwExample.sbr" : $(SOURCE) "$(INTDIR)"



!ENDIF 


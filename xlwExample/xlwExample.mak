# Microsoft Developer Studio Generated NMAKE File, Based on xlwExample.dsp
!IF "$(CFG)" == ""
CFG=xlwExample - Win32 Debug SingleThread
!MESSAGE No configuration specified. Defaulting to xlwExample - Win32 Debug SingleThread.
!ENDIF 

!IF "$(CFG)" != "xlwExample - Win32 Release" && "$(CFG)" != "xlwExample - Win32 Debug" && "$(CFG)" != "xlwExample - Win32 Debug MTDLL" && "$(CFG)" != "xlwExample - Win32 Release MTDLL" && "$(CFG)" != "xlwExample - Win32 Release SingleThread" && "$(CFG)" != "xlwExample - Win32 Debug SingleThread"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "xlwExample.mak" CFG="xlwExample - Win32 Debug SingleThread"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xlwExample - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xlwExample - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xlwExample - Win32 Debug MTDLL" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xlwExample - Win32 Release MTDLL" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xlwExample - Win32 Release SingleThread" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xlwExample - Win32 Debug SingleThread" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "xlwExample - Win32 Release"

OUTDIR=.\build\Release
INTDIR=.\build\Release
# Begin Custom Macros
OutDir=.\build\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\xll\xlwExample-vc6-mt-s.xll" "$(OUTDIR)\xlwExample.bsc"

!ELSE 

ALL : "xlw - Win32 Release" ".\xll\xlwExample-vc6-mt-s.xll" "$(OUTDIR)\xlwExample.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"xlw - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Win32StreamBuf.obj"
	-@erase "$(INTDIR)\Win32StreamBuf.sbr"
	-@erase "$(INTDIR)\xlwExample.obj"
	-@erase "$(INTDIR)\xlwExample.sbr"
	-@erase "$(OUTDIR)\xlwExample-vc6-mt-s.exp"
	-@erase "$(OUTDIR)\xlwExample-vc6-mt-s.lib"
	-@erase "$(OUTDIR)\xlwExample.bsc"
	-@erase ".\xll\xlwExample-vc6-mt-s.xll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GR /GX /O2 /I ".." /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "WIN32" /D "_MBCS" /D "XLW_AUTOLINK" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\xlwExample.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xlwExample.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Win32StreamBuf.sbr" \
	"$(INTDIR)\xlwExample.sbr"

"$(OUTDIR)\xlwExample.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\xlwExample-vc6-mt-s.pdb" /machine:I386 /out:"xll\xlwExample-vc6-mt-s.xll" /implib:"$(OUTDIR)\xlwExample-vc6-mt-s.lib" /libpath:"..\lib\Win32\VisualStudio" 
LINK32_OBJS= \
	"$(INTDIR)\Win32StreamBuf.obj" \
	"$(INTDIR)\xlwExample.obj" \
	"..\lib\xlw-vc6-mt-s-1_2_3.lib"

".\xll\xlwExample-vc6-mt-s.xll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xlwExample - Win32 Debug"

OUTDIR=.\build\Debug
INTDIR=.\build\Debug
# Begin Custom Macros
OutDir=.\build\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\xll\xlwExampled-vc6-mt-sgd.xll" "$(OUTDIR)\xlwExample.bsc"

!ELSE 

ALL : "xlw - Win32 Debug" ".\xll\xlwExampled-vc6-mt-sgd.xll" "$(OUTDIR)\xlwExample.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"xlw - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Win32StreamBuf.obj"
	-@erase "$(INTDIR)\Win32StreamBuf.sbr"
	-@erase "$(INTDIR)\xlwExample.obj"
	-@erase "$(INTDIR)\xlwExample.sbr"
	-@erase "$(OUTDIR)\xlwExample.bsc"
	-@erase "$(OUTDIR)\xlwExampled-vc6-mt-sgd.exp"
	-@erase "$(OUTDIR)\xlwExampled-vc6-mt-sgd.lib"
	-@erase "$(OUTDIR)\xlwExampled-vc6-mt-sgd.pdb"
	-@erase ".\xll\xlwExampled-vc6-mt-sgd.ilk"
	-@erase ".\xll\xlwExampled-vc6-mt-sgd.xll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GR /GX /ZI /Od /I ".." /D "_WINDOWS" /D "_USRDLL" /D "WIN32" /D "_MBCS" /D "XLW_AUTOLINK" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\xlwExample.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xlwExample.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Win32StreamBuf.sbr" \
	"$(INTDIR)\xlwExample.sbr"

"$(OUTDIR)\xlwExample.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\xlwExampled-vc6-mt-sgd.pdb" /debug /machine:I386 /out:"xll\xlwExampled-vc6-mt-sgd.xll" /implib:"$(OUTDIR)\xlwExampled-vc6-mt-sgd.lib" /pdbtype:sept /libpath:"..\lib\Win32\VisualStudio" 
LINK32_OBJS= \
	"$(INTDIR)\Win32StreamBuf.obj" \
	"$(INTDIR)\xlwExample.obj" \
	"..\lib\xlw-vc6-mt-sgd-1_2_3.lib"

".\xll\xlwExampled-vc6-mt-sgd.xll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xlwExample - Win32 Debug MTDLL"

OUTDIR=.\build\DebugMTDLL
INTDIR=.\build\DebugMTDLL
# Begin Custom Macros
OutDir=.\build\DebugMTDLL
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\xll\xlwExampled-vc6-mt-gd.xll" "$(OUTDIR)\xlwExample.bsc"

!ELSE 

ALL : "xlw - Win32 Debug MTDLL" ".\xll\xlwExampled-vc6-mt-gd.xll" "$(OUTDIR)\xlwExample.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"xlw - Win32 Debug MTDLLCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Win32StreamBuf.obj"
	-@erase "$(INTDIR)\Win32StreamBuf.sbr"
	-@erase "$(INTDIR)\xlwExample.obj"
	-@erase "$(INTDIR)\xlwExample.sbr"
	-@erase "$(OUTDIR)\xlwExample.bsc"
	-@erase "$(OUTDIR)\xlwExampled-vc6-mt-gd.exp"
	-@erase "$(OUTDIR)\xlwExampled-vc6-mt-gd.lib"
	-@erase "$(OUTDIR)\xlwExampled-vc6-mt-gd.pdb"
	-@erase ".\xll\xlwExampled-vc6-mt-gd.ilk"
	-@erase ".\xll\xlwExampled-vc6-mt-gd.xll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I ".." /D "_WINDOWS" /D "_USRDLL" /D "WIN32" /D "_MBCS" /D "XLW_AUTOLINK" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\xlwExample.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xlwExample.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Win32StreamBuf.sbr" \
	"$(INTDIR)\xlwExample.sbr"

"$(OUTDIR)\xlwExample.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\xlwExampled-vc6-mt-gd.pdb" /debug /machine:I386 /out:"xll\xlwExampled-vc6-mt-gd.xll" /implib:"$(OUTDIR)\xlwExampled-vc6-mt-gd.lib" /pdbtype:sept /libpath:"..\lib\Win32\VisualStudio" 
LINK32_OBJS= \
	"$(INTDIR)\Win32StreamBuf.obj" \
	"$(INTDIR)\xlwExample.obj" \
	"..\lib\xlw-vc6-mt-gd-1_2_3.lib"

".\xll\xlwExampled-vc6-mt-gd.xll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xlwExample - Win32 Release MTDLL"

OUTDIR=.\build\ReleaseMTDLL
INTDIR=.\build\ReleaseMTDLL
# Begin Custom Macros
OutDir=.\build\ReleaseMTDLL
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\xll\xlwExample-vc6-mt.xll" "$(OUTDIR)\xlwExample.bsc"

!ELSE 

ALL : "xlw - Win32 Release MTDLL" ".\xll\xlwExample-vc6-mt.xll" "$(OUTDIR)\xlwExample.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"xlw - Win32 Release MTDLLCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Win32StreamBuf.obj"
	-@erase "$(INTDIR)\Win32StreamBuf.sbr"
	-@erase "$(INTDIR)\xlwExample.obj"
	-@erase "$(INTDIR)\xlwExample.sbr"
	-@erase "$(OUTDIR)\xlwExample-vc6-mt.exp"
	-@erase "$(OUTDIR)\xlwExample-vc6-mt.lib"
	-@erase "$(OUTDIR)\xlwExample.bsc"
	-@erase ".\xll\xlwExample-vc6-mt.xll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /I ".." /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "WIN32" /D "_MBCS" /D "XLW_AUTOLINK" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\xlwExample.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xlwExample.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Win32StreamBuf.sbr" \
	"$(INTDIR)\xlwExample.sbr"

"$(OUTDIR)\xlwExample.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\xlwExample-vc6-mt.pdb" /machine:I386 /out:"xll\xlwExample-vc6-mt.xll" /implib:"$(OUTDIR)\xlwExample-vc6-mt.lib" /libpath:"..\lib\Win32\VisualStudio" 
LINK32_OBJS= \
	"$(INTDIR)\Win32StreamBuf.obj" \
	"$(INTDIR)\xlwExample.obj" \
	"..\lib\xlw-vc6-mt-1_2_3.lib"

".\xll\xlwExample-vc6-mt.xll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xlwExample - Win32 Release SingleThread"

OUTDIR=.\build\ReleaseSingleThread
INTDIR=.\build\ReleaseSingleThread
# Begin Custom Macros
OutDir=.\build\ReleaseSingleThread
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\xll\xlwExample-vc6-s.xll" "$(OUTDIR)\xlwExample.bsc"

!ELSE 

ALL : "xlw - Win32 Release SingleThread" ".\xll\xlwExample-vc6-s.xll" "$(OUTDIR)\xlwExample.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"xlw - Win32 Release SingleThreadCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Win32StreamBuf.obj"
	-@erase "$(INTDIR)\Win32StreamBuf.sbr"
	-@erase "$(INTDIR)\xlwExample.obj"
	-@erase "$(INTDIR)\xlwExample.sbr"
	-@erase "$(OUTDIR)\xlwExample-vc6-s.exp"
	-@erase "$(OUTDIR)\xlwExample-vc6-s.lib"
	-@erase "$(OUTDIR)\xlwExample.bsc"
	-@erase ".\xll\xlwExample-vc6-s.xll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GR /GX /O2 /I ".." /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "WIN32" /D "_MBCS" /D "XLW_AUTOLINK" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\xlwExample.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xlwExample.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Win32StreamBuf.sbr" \
	"$(INTDIR)\xlwExample.sbr"

"$(OUTDIR)\xlwExample.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\xlwExample-vc6-s.pdb" /machine:I386 /out:"xll\xlwExample-vc6-s.xll" /implib:"$(OUTDIR)\xlwExample-vc6-s.lib" /libpath:"..\lib\Win32\VisualStudio" 
LINK32_OBJS= \
	"$(INTDIR)\Win32StreamBuf.obj" \
	"$(INTDIR)\xlwExample.obj" \
	"..\lib\xlw-vc6-s-1_2_3.lib"

".\xll\xlwExample-vc6-s.xll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xlwExample - Win32 Debug SingleThread"

OUTDIR=.\build\DebugSingleThread
INTDIR=.\build\DebugSingleThread
# Begin Custom Macros
OutDir=.\build\DebugSingleThread
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\xll\xlwExampled-vc6-sgd.xll" "$(OUTDIR)\xlwExample.bsc"

!ELSE 

ALL : "xlw - Win32 Debug SingleThread" ".\xll\xlwExampled-vc6-sgd.xll" "$(OUTDIR)\xlwExample.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"xlw - Win32 Debug SingleThreadCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Win32StreamBuf.obj"
	-@erase "$(INTDIR)\Win32StreamBuf.sbr"
	-@erase "$(INTDIR)\xlwExample.obj"
	-@erase "$(INTDIR)\xlwExample.sbr"
	-@erase "$(OUTDIR)\xlwExample.bsc"
	-@erase "$(OUTDIR)\xlwExampled-vc6-sgd.exp"
	-@erase "$(OUTDIR)\xlwExampled-vc6-sgd.lib"
	-@erase "$(OUTDIR)\xlwExampled-vc6-sgd.pdb"
	-@erase ".\xll\xlwExampled-vc6-sgd.ilk"
	-@erase ".\xll\xlwExampled-vc6-sgd.xll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GR /GX /ZI /Od /I ".." /D "_WINDOWS" /D "_USRDLL" /D "WIN32" /D "_MBCS" /D "XLW_AUTOLINK" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\xlwExample.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xlwExample.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Win32StreamBuf.sbr" \
	"$(INTDIR)\xlwExample.sbr"

"$(OUTDIR)\xlwExample.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\xlwExampled-vc6-sgd.pdb" /debug /machine:I386 /out:"xll\xlwExampled-vc6-sgd.xll" /implib:"$(OUTDIR)\xlwExampled-vc6-sgd.lib" /pdbtype:sept /libpath:"..\lib\Win32\VisualStudio" 
LINK32_OBJS= \
	"$(INTDIR)\Win32StreamBuf.obj" \
	"$(INTDIR)\xlwExample.obj" \
	"..\lib\xlw-vc6-sgd-1_2_3.lib"

".\xll\xlwExampled-vc6-sgd.xll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("xlwExample.dep")
!INCLUDE "xlwExample.dep"
!ELSE 
!MESSAGE Warning: cannot find "xlwExample.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "xlwExample - Win32 Release" || "$(CFG)" == "xlwExample - Win32 Debug" || "$(CFG)" == "xlwExample - Win32 Debug MTDLL" || "$(CFG)" == "xlwExample - Win32 Release MTDLL" || "$(CFG)" == "xlwExample - Win32 Release SingleThread" || "$(CFG)" == "xlwExample - Win32 Debug SingleThread"

!IF  "$(CFG)" == "xlwExample - Win32 Release"

"xlw - Win32 Release" : 
   cd "\Projects\XLW"
   $(MAKE) /$(MAKEFLAGS) /F .\xlw.mak CFG="xlw - Win32 Release" 
   cd ".\xlwExample"

"xlw - Win32 ReleaseCLEAN" : 
   cd "\Projects\XLW"
   $(MAKE) /$(MAKEFLAGS) /F .\xlw.mak CFG="xlw - Win32 Release" RECURSE=1 CLEAN 
   cd ".\xlwExample"

!ELSEIF  "$(CFG)" == "xlwExample - Win32 Debug"

"xlw - Win32 Debug" : 
   cd "\Projects\XLW"
   $(MAKE) /$(MAKEFLAGS) /F .\xlw.mak CFG="xlw - Win32 Debug" 
   cd ".\xlwExample"

"xlw - Win32 DebugCLEAN" : 
   cd "\Projects\XLW"
   $(MAKE) /$(MAKEFLAGS) /F .\xlw.mak CFG="xlw - Win32 Debug" RECURSE=1 CLEAN 
   cd ".\xlwExample"

!ELSEIF  "$(CFG)" == "xlwExample - Win32 Debug MTDLL"

"xlw - Win32 Debug MTDLL" : 
   cd "\Projects\XLW"
   $(MAKE) /$(MAKEFLAGS) /F .\xlw.mak CFG="xlw - Win32 Debug MTDLL" 
   cd ".\xlwExample"

"xlw - Win32 Debug MTDLLCLEAN" : 
   cd "\Projects\XLW"
   $(MAKE) /$(MAKEFLAGS) /F .\xlw.mak CFG="xlw - Win32 Debug MTDLL" RECURSE=1 CLEAN 
   cd ".\xlwExample"

!ELSEIF  "$(CFG)" == "xlwExample - Win32 Release MTDLL"

"xlw - Win32 Release MTDLL" : 
   cd "\Projects\XLW"
   $(MAKE) /$(MAKEFLAGS) /F .\xlw.mak CFG="xlw - Win32 Release MTDLL" 
   cd ".\xlwExample"

"xlw - Win32 Release MTDLLCLEAN" : 
   cd "\Projects\XLW"
   $(MAKE) /$(MAKEFLAGS) /F .\xlw.mak CFG="xlw - Win32 Release MTDLL" RECURSE=1 CLEAN 
   cd ".\xlwExample"

!ELSEIF  "$(CFG)" == "xlwExample - Win32 Release SingleThread"

"xlw - Win32 Release SingleThread" : 
   cd "\Projects\XLW"
   $(MAKE) /$(MAKEFLAGS) /F .\xlw.mak CFG="xlw - Win32 Release SingleThread" 
   cd ".\xlwExample"

"xlw - Win32 Release SingleThreadCLEAN" : 
   cd "\Projects\XLW"
   $(MAKE) /$(MAKEFLAGS) /F .\xlw.mak CFG="xlw - Win32 Release SingleThread" RECURSE=1 CLEAN 
   cd ".\xlwExample"

!ELSEIF  "$(CFG)" == "xlwExample - Win32 Debug SingleThread"

"xlw - Win32 Debug SingleThread" : 
   cd "\Projects\XLW"
   $(MAKE) /$(MAKEFLAGS) /F .\xlw.mak CFG="xlw - Win32 Debug SingleThread" 
   cd ".\xlwExample"

"xlw - Win32 Debug SingleThreadCLEAN" : 
   cd "\Projects\XLW"
   $(MAKE) /$(MAKEFLAGS) /F .\xlw.mak CFG="xlw - Win32 Debug SingleThread" RECURSE=1 CLEAN 
   cd ".\xlwExample"

!ENDIF 

SOURCE=.\Win32StreamBuf.cpp

"$(INTDIR)\Win32StreamBuf.obj"	"$(INTDIR)\Win32StreamBuf.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\xlwExample.cpp

"$(INTDIR)\xlwExample.obj"	"$(INTDIR)\xlwExample.sbr" : $(SOURCE) "$(INTDIR)"



!ENDIF 


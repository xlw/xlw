# Microsoft Developer Studio Generated NMAKE File, Based on xlw.dsp
!IF "$(CFG)" == ""
CFG=xlw - Win32 Debug
!MESSAGE No configuration specified. Defaulting to xlw - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "xlw - Win32 Release" && "$(CFG)" != "xlw - Win32 Debug" && "$(CFG)" != "xlw - Win32 OnTheEdgeDebug" && "$(CFG)" != "xlw - Win32 OnTheEdgeRelease"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "xlw.mak" CFG="xlw - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xlw - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "xlw - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "xlw - Win32 OnTheEdgeDebug" (based on "Win32 (x86) Static Library")
!MESSAGE "xlw - Win32 OnTheEdgeRelease" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "xlw - Win32 Release"

OUTDIR=.\build\Release
INTDIR=.\build\Release

ALL : ".\lib\Win32\VisualStudio\xlw.lib"


CLEAN :
	-@erase "$(INTDIR)\excel32.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\XlfAbstractCmdDesc.obj"
	-@erase "$(INTDIR)\XlfArgDesc.obj"
	-@erase "$(INTDIR)\XlfArgDescList.obj"
	-@erase "$(INTDIR)\XlfCmdDesc.obj"
	-@erase "$(INTDIR)\XlfExcel.obj"
	-@erase "$(INTDIR)\XlfException.obj"
	-@erase "$(INTDIR)\XlfFuncDesc.obj"
	-@erase "$(INTDIR)\XlfOper.obj"
	-@erase "$(INTDIR)\XlfRef.obj"
	-@erase ".\lib\Win32\VisualStudio\xlw.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I ".\\" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "XLW_NOIMPORTEXPORT" /Fp"$(INTDIR)\xlw.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xlw.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"lib\Win32\VisualStudio\xlw.lib" 
LIB32_OBJS= \
	"$(INTDIR)\excel32.obj" \
	"$(INTDIR)\XlfAbstractCmdDesc.obj" \
	"$(INTDIR)\XlfArgDesc.obj" \
	"$(INTDIR)\XlfArgDescList.obj" \
	"$(INTDIR)\XlfCmdDesc.obj" \
	"$(INTDIR)\XlfExcel.obj" \
	"$(INTDIR)\XlfException.obj" \
	"$(INTDIR)\XlfFuncDesc.obj" \
	"$(INTDIR)\XlfOper.obj" \
	"$(INTDIR)\XlfRef.obj"

".\lib\Win32\VisualStudio\xlw.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xlw - Win32 Debug"

OUTDIR=.\build\Debug
INTDIR=.\build\Debug

ALL : ".\lib\Win32\VisualStudio\xlwd.lib"


CLEAN :
	-@erase "$(INTDIR)\excel32.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\XlfAbstractCmdDesc.obj"
	-@erase "$(INTDIR)\XlfArgDesc.obj"
	-@erase "$(INTDIR)\XlfArgDescList.obj"
	-@erase "$(INTDIR)\XlfCmdDesc.obj"
	-@erase "$(INTDIR)\XlfExcel.obj"
	-@erase "$(INTDIR)\XlfException.obj"
	-@erase "$(INTDIR)\XlfFuncDesc.obj"
	-@erase "$(INTDIR)\XlfOper.obj"
	-@erase "$(INTDIR)\XlfRef.obj"
	-@erase ".\lib\Win32\VisualStudio\xlwd.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /D "XLW_DEBUG" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "XLW_NOIMPORTEXPORT" /Fp"$(INTDIR)\xlw.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xlw.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"lib\Win32\VisualStudio\xlwd.lib" 
LIB32_OBJS= \
	"$(INTDIR)\excel32.obj" \
	"$(INTDIR)\XlfAbstractCmdDesc.obj" \
	"$(INTDIR)\XlfArgDesc.obj" \
	"$(INTDIR)\XlfArgDescList.obj" \
	"$(INTDIR)\XlfCmdDesc.obj" \
	"$(INTDIR)\XlfExcel.obj" \
	"$(INTDIR)\XlfException.obj" \
	"$(INTDIR)\XlfFuncDesc.obj" \
	"$(INTDIR)\XlfOper.obj" \
	"$(INTDIR)\XlfRef.obj"

".\lib\Win32\VisualStudio\xlwd.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xlw - Win32 OnTheEdgeDebug"

OUTDIR=.\build\OnTheEdgeDebug
INTDIR=.\build\OnTheEdgeDebug

ALL : ".\lib\Win32\VisualStudio\xlwd.lib"


CLEAN :
	-@erase "$(INTDIR)\excel32.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\XlfAbstractCmdDesc.obj"
	-@erase "$(INTDIR)\XlfArgDesc.obj"
	-@erase "$(INTDIR)\XlfArgDescList.obj"
	-@erase "$(INTDIR)\XlfCmdDesc.obj"
	-@erase "$(INTDIR)\XlfExcel.obj"
	-@erase "$(INTDIR)\XlfException.obj"
	-@erase "$(INTDIR)\XlfFuncDesc.obj"
	-@erase "$(INTDIR)\XlfOper.obj"
	-@erase "$(INTDIR)\XlfRef.obj"
	-@erase ".\lib\Win32\VisualStudio\xlwd.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /D "XLW_DEBUG" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "XLW_NOIMPORTEXPORT" /Fp"$(INTDIR)\xlw.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xlw.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"lib\Win32\VisualStudio\xlwd.lib" 
LIB32_OBJS= \
	"$(INTDIR)\excel32.obj" \
	"$(INTDIR)\XlfAbstractCmdDesc.obj" \
	"$(INTDIR)\XlfArgDesc.obj" \
	"$(INTDIR)\XlfArgDescList.obj" \
	"$(INTDIR)\XlfCmdDesc.obj" \
	"$(INTDIR)\XlfExcel.obj" \
	"$(INTDIR)\XlfException.obj" \
	"$(INTDIR)\XlfFuncDesc.obj" \
	"$(INTDIR)\XlfOper.obj" \
	"$(INTDIR)\XlfRef.obj"

".\lib\Win32\VisualStudio\xlwd.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xlw - Win32 OnTheEdgeRelease"

OUTDIR=.\build\OnTheEdgeRelease
INTDIR=.\build\OnTheEdgeRelease

ALL : ".\lib\Win32\VisualStudio\xlw.lib"


CLEAN :
	-@erase "$(INTDIR)\excel32.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\XlfAbstractCmdDesc.obj"
	-@erase "$(INTDIR)\XlfArgDesc.obj"
	-@erase "$(INTDIR)\XlfArgDescList.obj"
	-@erase "$(INTDIR)\XlfCmdDesc.obj"
	-@erase "$(INTDIR)\XlfExcel.obj"
	-@erase "$(INTDIR)\XlfException.obj"
	-@erase "$(INTDIR)\XlfFuncDesc.obj"
	-@erase "$(INTDIR)\XlfOper.obj"
	-@erase "$(INTDIR)\XlfRef.obj"
	-@erase ".\lib\Win32\VisualStudio\xlw.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I ".\\" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "XLW_NOIMPORTEXPORT" /Fp"$(INTDIR)\xlw.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xlw.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"lib\Win32\VisualStudio\xlw.lib" 
LIB32_OBJS= \
	"$(INTDIR)\excel32.obj" \
	"$(INTDIR)\XlfAbstractCmdDesc.obj" \
	"$(INTDIR)\XlfArgDesc.obj" \
	"$(INTDIR)\XlfArgDescList.obj" \
	"$(INTDIR)\XlfCmdDesc.obj" \
	"$(INTDIR)\XlfExcel.obj" \
	"$(INTDIR)\XlfException.obj" \
	"$(INTDIR)\XlfFuncDesc.obj" \
	"$(INTDIR)\XlfOper.obj" \
	"$(INTDIR)\XlfRef.obj"

".\lib\Win32\VisualStudio\xlw.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
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
!IF EXISTS("xlw.dep")
!INCLUDE "xlw.dep"
!ELSE 
!MESSAGE Warning: cannot find "xlw.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "xlw - Win32 Release" || "$(CFG)" == "xlw - Win32 Debug" || "$(CFG)" == "xlw - Win32 OnTheEdgeDebug" || "$(CFG)" == "xlw - Win32 OnTheEdgeRelease"
SOURCE=.\xlw\excel32.cpp

"$(INTDIR)\excel32.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\xlw\XlfAbstractCmdDesc.cpp

"$(INTDIR)\XlfAbstractCmdDesc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\xlw\XlfArgDesc.cpp

"$(INTDIR)\XlfArgDesc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\xlw\XlfArgDescList.cpp

"$(INTDIR)\XlfArgDescList.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\xlw\XlfCmdDesc.cpp

"$(INTDIR)\XlfCmdDesc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\xlw\XlfExcel.cpp

"$(INTDIR)\XlfExcel.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\xlw\XlfException.cpp

"$(INTDIR)\XlfException.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\xlw\XlfFuncDesc.cpp

"$(INTDIR)\XlfFuncDesc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\xlw\XlfOper.cpp

"$(INTDIR)\XlfOper.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\xlw\XlfRef.cpp

"$(INTDIR)\XlfRef.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 


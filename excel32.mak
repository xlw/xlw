# Microsoft Developer Studio Generated NMAKE File, Based on excel32.dsp
!IF "$(CFG)" == ""
CFG=excel32 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to excel32 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "excel32 - Win32 Release" && "$(CFG)" != "excel32 - Win32 Debug" && "$(CFG)" != "excel32 - Win32 OnTheEdgeDebug" && "$(CFG)" != "excel32 - Win32 OnTheEdgeRelease"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "excel32.mak" CFG="excel32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "excel32 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "excel32 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "excel32 - Win32 OnTheEdgeDebug" (based on "Win32 (x86) Static Library")
!MESSAGE "excel32 - Win32 OnTheEdgeRelease" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "excel32 - Win32 Release"

OUTDIR=.\build\Release
INTDIR=.\build\Release

ALL : ".\lib\Win32\VisualStudio\excel32.lib"


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
	-@erase ".\lib\Win32\VisualStudio\excel32.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I ".\\" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "EXCEL32_NOIMPORTEXPORT" /Fp"$(INTDIR)\excel32.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\excel32.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"lib\Win32\VisualStudio\excel32.lib" 
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

".\lib\Win32\VisualStudio\excel32.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "excel32 - Win32 Debug"

OUTDIR=.\build\Debug
INTDIR=.\build\Debug

ALL : ".\lib\Win32\VisualStudio\excel32d.lib"


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
	-@erase ".\lib\Win32\VisualStudio\excel32d.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /D "XLW_DEBUG" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "EXCEL32_NOIMPORTEXPORT" /Fp"$(INTDIR)\excel32.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\excel32.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"lib\Win32\VisualStudio\excel32d.lib" 
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

".\lib\Win32\VisualStudio\excel32d.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "excel32 - Win32 OnTheEdgeDebug"

OUTDIR=.\build\OnTheEdgeDebug
INTDIR=.\build\OnTheEdgeDebug

ALL : ".\lib\Win32\VisualStudio\excel32d.lib"


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
	-@erase ".\lib\Win32\VisualStudio\excel32d.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /D "XLW_DEBUG" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "EXCEL32_NOIMPORTEXPORT" /Fp"$(INTDIR)\excel32.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\excel32.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"lib\Win32\VisualStudio\excel32d.lib" 
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

".\lib\Win32\VisualStudio\excel32d.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "excel32 - Win32 OnTheEdgeRelease"

OUTDIR=.\build\OnTheEdgeRelease
INTDIR=.\build\OnTheEdgeRelease

ALL : ".\lib\Win32\VisualStudio\excel32.lib"


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
	-@erase ".\lib\Win32\VisualStudio\excel32.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I ".\\" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "EXCEL32_NOIMPORTEXPORT" /Fp"$(INTDIR)\excel32.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\excel32.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"lib\Win32\VisualStudio\excel32.lib" 
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

".\lib\Win32\VisualStudio\excel32.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("excel32.dep")
!INCLUDE "excel32.dep"
!ELSE 
!MESSAGE Warning: cannot find "excel32.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "excel32 - Win32 Release" || "$(CFG)" == "excel32 - Win32 Debug" || "$(CFG)" == "excel32 - Win32 OnTheEdgeDebug" || "$(CFG)" == "excel32 - Win32 OnTheEdgeRelease"
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


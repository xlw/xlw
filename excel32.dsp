# Microsoft Developer Studio Project File - Name="excel32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=excel32 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "excel32.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/excel32", BXAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "excel32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "build\Release"
# PROP Intermediate_Dir "build\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\\" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "EXCEL32_NOIMPORTEXPORT" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\Win32\VisualStudio\excel32.lib"

!ELSEIF  "$(CFG)" == "excel32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "excel32___Win32_Debug"
# PROP BASE Intermediate_Dir "excel32___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "build\Debug"
# PROP Intermediate_Dir "build\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "EXCEL32_NOIMPORTEXPORT" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\Win32\VisualStudio\excel32_d.lib"

!ELSEIF  "$(CFG)" == "excel32 - Win32 OnTheEdgeDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "excel32___Win32_OnTheEdgeDebug"
# PROP BASE Intermediate_Dir "excel32___Win32_OnTheEdgeDebug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "build\OnTheEdgeDebug"
# PROP Intermediate_Dir "build\OnTheEdgeDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "EXCEL32_NOIMPORTEXPORT" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"lib\Win32\VisualStudio\excel32_d.lib"
# ADD LIB32 /nologo /out:"lib\Win32\VisualStudio\excel32_d.lib"

!ELSEIF  "$(CFG)" == "excel32 - Win32 OnTheEdgeRelease"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "excel32___Win32_OnTheEdgeRelease"
# PROP BASE Intermediate_Dir "excel32___Win32_OnTheEdgeRelease"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "build\OnTheEdgeRelease"
# PROP Intermediate_Dir "build\OnTheEdgeRelease"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\\" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "EXCEL32_NOIMPORTEXPORT" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"lib\Win32\VisualStudio\excel32.lib"
# ADD LIB32 /nologo /out:"lib\Win32\VisualStudio\excel32.lib"

!ENDIF 

# Begin Target

# Name "excel32 - Win32 Release"
# Name "excel32 - Win32 Debug"
# Name "excel32 - Win32 OnTheEdgeDebug"
# Name "excel32 - Win32 OnTheEdgeRelease"
# Begin Group "Include"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\xlw\config.bcc.h
# End Source File
# Begin Source File

SOURCE=.\xlw\config.msvc.h
# End Source File
# Begin Source File

SOURCE=.\xlw\ERR_Macros.h
# End Source File
# Begin Source File

SOURCE=.\xlw\excel32.h
# End Source File
# Begin Source File

SOURCE=.\xlw\EXCEL32_API.h
# End Source File
# Begin Source File

SOURCE=.\xlw\macros.h
# End Source File
# Begin Source File

SOURCE=.\xlw\port.h
# End Source File
# Begin Source File

SOURCE=.\xlw\pragmas.h
# End Source File
# Begin Source File

SOURCE=.\xlw\xlcall32.h
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfAbstractCmdDesc.h
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfArgDesc.h
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfArgDescList.h
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfCmdDesc.h
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfExcel.h
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfException.h
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfFuncDesc.h
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfOper.h
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfRef.h
# End Source File
# End Group
# Begin Group "Source"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\xlw\excel32.cpp
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfAbstractCmdDesc.cpp
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfArgDesc.cpp
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfArgDescList.cpp
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfCmdDesc.cpp
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfExcel.cpp
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfException.cpp
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfFuncDesc.cpp
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfOper.cpp
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfRef.cpp
# End Source File
# End Group
# Begin Group "Inline"

# PROP Default_Filter ".inl"
# Begin Source File

SOURCE=.\xlw\XlfAbstractCmdDesc.inl
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfExcel.inl
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfException.inl
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfOper.inl
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfRef.inl
# End Source File
# End Group
# Begin Group "doc"

# PROP Default_Filter ".txt"
# Begin Source File

SOURCE=.\Docs\pages\bibliography.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\pages\download.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\pages\excel32.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\pages\faq.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\pages\gettingStarted.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\pages\knownbugs.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\pages\misc.txt
# End Source File
# End Group
# Begin Source File

SOURCE=.\Docs\xlw.doxy
# End Source File
# End Target
# End Project

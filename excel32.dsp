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
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "excel32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "excel32___Win32_Debug"
# PROP BASE Intermediate_Dir "excel32___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "excel32 - Win32 Release"
# Name "excel32 - Win32 Debug"
# Begin Group "Include"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\ERR_Macros.h
# End Source File
# Begin Source File

SOURCE=.\excel32.h
# End Source File
# Begin Source File

SOURCE=.\EXCEL32_API.h
# End Source File
# Begin Source File

SOURCE=.\macros.h
# End Source File
# Begin Source File

SOURCE=.\port.h
# End Source File
# Begin Source File

SOURCE=.\pragmas.h
# End Source File
# Begin Source File

SOURCE=.\xlcall32.h
# End Source File
# Begin Source File

SOURCE=.\XlfAbstractCmdDesc.h
# End Source File
# Begin Source File

SOURCE=.\XlfArgDesc.h
# End Source File
# Begin Source File

SOURCE=.\XlfArgDescList.h
# End Source File
# Begin Source File

SOURCE=.\XlfCmdDesc.h
# End Source File
# Begin Source File

SOURCE=.\XlfExcel.h
# End Source File
# Begin Source File

SOURCE=.\XlfException.h
# End Source File
# Begin Source File

SOURCE=.\XlfFuncDesc.h
# End Source File
# Begin Source File

SOURCE=.\XlfOper.h
# End Source File
# Begin Source File

SOURCE=.\XlfRef.h
# End Source File
# End Group
# Begin Group "Source"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\XlfAbstractCmdDesc.cpp
# End Source File
# Begin Source File

SOURCE=.\XlfArgDesc.cpp
# End Source File
# Begin Source File

SOURCE=.\XlfArgDescList.cpp
# End Source File
# Begin Source File

SOURCE=.\XlfCmdDesc.cpp
# End Source File
# Begin Source File

SOURCE=.\XlfExcel.cpp
# End Source File
# Begin Source File

SOURCE=.\XlfException.cpp
# End Source File
# Begin Source File

SOURCE=.\XlfFuncDesc.cpp
# End Source File
# Begin Source File

SOURCE=.\XlfOper.cpp
# End Source File
# Begin Source File

SOURCE=.\XlfRef.cpp
# End Source File
# End Group
# Begin Group "Inline"

# PROP Default_Filter ".inl"
# Begin Source File

SOURCE=.\XlfAbstractCmdDesc.inl
# End Source File
# Begin Source File

SOURCE=.\XlfExcel.inl
# End Source File
# Begin Source File

SOURCE=.\XlfException.inl
# End Source File
# Begin Source File

SOURCE=.\XlfOper.inl
# End Source File
# Begin Source File

SOURCE=.\XlfRef.inl
# End Source File
# End Group
# Begin Group "doc"

# PROP Default_Filter ".txt"
# Begin Source File

SOURCE=.\bibliography.txt
# End Source File
# Begin Source File

SOURCE=.\download.txt
# End Source File
# Begin Source File

SOURCE=.\excel32.txt
# End Source File
# Begin Source File

SOURCE=.\faq.txt
# End Source File
# Begin Source File

SOURCE=.\gettingStarted.txt
# End Source File
# Begin Source File

SOURCE=.\knownbugs.txt
# End Source File
# Begin Source File

SOURCE=.\misc.txt
# End Source File
# End Group
# Begin Source File

SOURCE=.\doxygen.cfg

!IF  "$(CFG)" == "excel32 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "excel32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Target
# End Project

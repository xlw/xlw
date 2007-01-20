# Microsoft Developer Studio Project File - Name="xlwLib6" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=xlwLib6 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "xlwLib6.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "xlwLib6.mak" CFG="xlwLib6 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xlwLib6 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "xlwLib6 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "xlwLib6 - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../xlwVisio6/xlwLib6.lib"

!ELSEIF  "$(CFG)" == "xlwLib6 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /i ".." /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../xlwVisio6/xlwLib6-Debug.lib"

!ENDIF 

# Begin Target

# Name "xlwLib6 - Win32 Release"
# Name "xlwLib6 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\xlw\ArgList.cpp
# End Source File
# Begin Source File

SOURCE=..\xlw\CellMatrix.cpp
# End Source File
# Begin Source File

SOURCE=..\xlw\DoubleOrNothing.cpp
# End Source File
# Begin Source File

SOURCE=..\xlw\MJmatrices.cpp
# End Source File
# Begin Source File

SOURCE=..\xlw\MyContainers.cpp
# End Source File
# Begin Source File

SOURCE=..\xlw\Win32StreamBuf.cpp
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfAbstractCmdDesc.cpp
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfArgDesc.cpp
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfArgDescList.cpp
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfCmdDesc.cpp
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfExcel.cpp
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfException.cpp
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfFuncDesc.cpp
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfOper.cpp
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfRef.cpp
# End Source File
# Begin Source File

SOURCE=..\xlw\XlFunctionRegistration.cpp
# End Source File
# Begin Source File

SOURCE=..\xlw\XlOpenClose.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project

# Microsoft Developer Studio Project File - Name="xlw" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=xlw - Win32 Debug SingleThread
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "xlw.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "xlw.mak" CFG="xlw - Win32 Debug SingleThread"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xlw - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "xlw - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "xlw - Win32 Release MTDLL" (based on "Win32 (x86) Static Library")
!MESSAGE "xlw - Win32 Debug MTDLL" (based on "Win32 (x86) Static Library")
!MESSAGE "xlw - Win32 Release SingleThread" (based on "Win32 (x86) Static Library")
!MESSAGE "xlw - Win32 Debug SingleThread" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/xlw", BXAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "xlw - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I ".\\" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /FR /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\xlw-vc6-mt-s-1_2_3.lib"

!ELSEIF  "$(CFG)" == "xlw - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "xlw___Win32_Debug"
# PROP BASE Intermediate_Dir "xlw___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "build\Debug"
# PROP Intermediate_Dir "build\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /I ".\\" /D "_LIB" /D "_DEBUG" /D "WIN32" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\xlw-vc6-mt-sgd-1_2_3.lib"

!ELSEIF  "$(CFG)" == "xlw - Win32 Release MTDLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "xlw___Win32_Release_MTDLL"
# PROP BASE Intermediate_Dir "xlw___Win32_Release_MTDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "build\ReleaseMTDLL"
# PROP Intermediate_Dir "build\ReleaseMTDLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GR /GX /O2 /I ".\\" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /FR /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I ".\\" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /FR /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"lib\Win32\VisualStudio\xlw.lib"
# ADD LIB32 /nologo /out:"lib\xlw-vc6-mt-1_2_3.lib"

!ELSEIF  "$(CFG)" == "xlw - Win32 Debug MTDLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "xlw___Win32_Debug_MTDLL"
# PROP BASE Intermediate_Dir "xlw___Win32_Debug_MTDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "build\DebugMTDLL"
# PROP Intermediate_Dir "build\DebugMTDLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /I ".\\" /D "_LIB" /D "_DEBUG" /D "WIN32" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I ".\\" /D "_LIB" /D "_DEBUG" /D "WIN32" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"lib\Win32\VisualStudio\xlwd.lib"
# ADD LIB32 /nologo /out:"lib\xlw-vc6-mt-gd-1_2_3.lib"

!ELSEIF  "$(CFG)" == "xlw - Win32 Release SingleThread"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "xlw___Win32_Release_SingleThread"
# PROP BASE Intermediate_Dir "xlw___Win32_Release_SingleThread"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "build\ReleaseSingleThread"
# PROP Intermediate_Dir "build\ReleaseSingleThread"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GR /GX /O2 /I ".\\" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /FR /YX /FD /c
# ADD CPP /nologo /W3 /GR /GX /O2 /I ".\\" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /FR /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"lib\Win32\VisualStudio\xlw.lib"
# ADD LIB32 /nologo /out:"lib\xlw-vc6-s-1_2_3.lib"

!ELSEIF  "$(CFG)" == "xlw - Win32 Debug SingleThread"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "xlw___Win32_Debug_SingleThread"
# PROP BASE Intermediate_Dir "xlw___Win32_Debug_SingleThread"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "build\DebugSingleThread"
# PROP Intermediate_Dir "build\DebugSingleThread"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /I ".\\" /D "_LIB" /D "_DEBUG" /D "WIN32" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /I ".\\" /D "_LIB" /D "_DEBUG" /D "WIN32" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"lib\Win32\VisualStudio\xlwd.lib"
# ADD LIB32 /nologo /out:"lib\xlw-vc6-sgd-1_2_3.lib"

!ENDIF 

# Begin Target

# Name "xlw - Win32 Release"
# Name "xlw - Win32 Debug"
# Name "xlw - Win32 Release MTDLL"
# Name "xlw - Win32 Debug MTDLL"
# Name "xlw - Win32 Release SingleThread"
# Name "xlw - Win32 Debug SingleThread"
# Begin Group "Include"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\xlw\config.bcc.h
# End Source File
# Begin Source File

SOURCE=.\xlw\config.msvc.h
# End Source File
# Begin Source File

SOURCE=.\xlw\defines.h
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
# Begin Source File

SOURCE=.\xlw\xlw.h
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

SOURCE=.\Docs\pages\copyright.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\pages\download.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\pages\faq.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\pages\gettingStarted.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\pages\history.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\pages\index.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\pages\install.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\pages\knownbugs.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\pages\misc.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\pages\platforms.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\pages\projects.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\pages\usage.txt
# End Source File
# End Group
# Begin Source File

SOURCE=.\Docs\xlw.doxy
# End Source File
# End Target
# End Project

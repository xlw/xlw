# Microsoft Developer Studio Project File - Name="xlwVisio" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=xlwVisio - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "xlwVisio.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "xlwVisio.mak" CFG="xlwVisio - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xlwVisio - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xlwVisio - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "xlwVisio - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XLWVISIO_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XLWVISIO_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib xlwLib6.lib /nologo /dll /incremental:yes /machine:I386 /out:"Release/xlwVisio.xll" /libpath:"../xlwLib/Release"

!ELSEIF  "$(CFG)" == "xlwVisio - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XLWVISIO_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XLWVISIO_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 xlwLib6-Debug.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"Debug/xlwVisio.xll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "xlwVisio - Win32 Release"
# Name "xlwVisio - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\TestFiles\PayOff.cpp
# End Source File
# Begin Source File

SOURCE=..\TestFiles\PayOffConcrete.cpp
# End Source File
# Begin Source File

SOURCE=..\TestFiles\PayOffRegistration.cpp
# End Source File
# Begin Source File

SOURCE=..\TestFiles\Test.cpp
# End Source File
# Begin Source File

SOURCE=..\TestFiles\xlwTest.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\xlw\ArgList.h
# End Source File
# Begin Source File

SOURCE=..\xlw\ArgListFactory.h
# End Source File
# Begin Source File

SOURCE=..\xlw\ArgListFactoryHelper.h
# End Source File
# Begin Source File

SOURCE=..\xlw\CellMatrix.h
# End Source File
# Begin Source File

SOURCE=..\xlw\config.bcc.h
# End Source File
# Begin Source File

SOURCE=..\xlw\config.mgw.h
# End Source File
# Begin Source File

SOURCE=..\xlw\config.msvc.h
# End Source File
# Begin Source File

SOURCE=..\xlw\defines.h
# End Source File
# Begin Source File

SOURCE=..\xlw\DoubleOrNothing.h
# End Source File
# Begin Source File

SOURCE=..\xlw\ERR_Macros.h
# End Source File
# Begin Source File

SOURCE=..\xlw\EXCEL32_API.h
# End Source File
# Begin Source File

SOURCE=..\xlw\macros.h
# End Source File
# Begin Source File

SOURCE=..\xlw\MJmatrices.h
# End Source File
# Begin Source File

SOURCE=..\xlw\MyContainers.h
# End Source File
# Begin Source File

SOURCE=..\TestFiles\PayOff.h
# End Source File
# Begin Source File

SOURCE=..\TestFiles\PayoffConcrete.h
# End Source File
# Begin Source File

SOURCE=..\xlw\port.h
# End Source File
# Begin Source File

SOURCE=..\xlw\pragmas.h
# End Source File
# Begin Source File

SOURCE=..\TestFiles\Test.h
# End Source File
# Begin Source File

SOURCE=.\Test.h
# End Source File
# Begin Source File

SOURCE=..\xlw\Win32StreamBuf.h
# End Source File
# Begin Source File

SOURCE=..\xlw\Win32StreamBuf.inl
# End Source File
# Begin Source File

SOURCE=..\xlw\wrapper.h
# End Source File
# Begin Source File

SOURCE=..\xlw\xlcall32.h
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfAbstractCmdDesc.h
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfAbstractCmdDesc.inl
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfArgDesc.h
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfArgDescList.h
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfCmdDesc.h
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfExcel.h
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfExcel.inl
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfException.h
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfException.inl
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfFuncDesc.h
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfOper.h
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfOper.inl
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfRef.h
# End Source File
# Begin Source File

SOURCE=..\xlw\XlfRef.inl
# End Source File
# Begin Source File

SOURCE=..\xlw\XlFunctionRegistration.h
# End Source File
# Begin Source File

SOURCE=..\xlw\XlOpenClose.h
# End Source File
# Begin Source File

SOURCE=..\xlw\xlw.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project

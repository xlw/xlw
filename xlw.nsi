
# to be used with NSIS 2.0 and up

SetCompressor lzma

!define VER_NUMBER "1.2.3"

# HEADER CONFIGURATION COMMANDS
Name "XLW"
Caption "XLW - Setup"
#do not change the name below
OutFile "..\xlw-${VER_NUMBER}-installer.exe"

InstType "Full (w/ Documentation)"
InstType Minimal

ComponentText "This will install XLW ${VER_NUMBER} on your computer"

SilentInstall normal
CRCCheck on
LicenseText "You must agree with the following license before installing:"
LicenseData License.txt
DirText "Please select a location to install XLW (or use the default):"
InstallDir $PROGRAMFILES\XLW
InstallDirRegKey HKEY_LOCAL_MACHINE SOFTWARE\XLW "Install_Dir"
AutoCloseWindow false
ShowInstDetails hide
SetDateSave on

# INSTALLATION EXECUTION COMMANDS



Section "-XLW"
SectionIn 1 2
# this directory must be created first, or the CreateShortCut will not work
    CreateDirectory "$SMPROGRAMS\XLW"
    SetOutPath $INSTDIR

    # these MUST be present
    File "README.TXT"
    File "LICENSE.TXT"
    File "NEWS.TXT"
    File "xlw.dsw"
    File "xlw.sln"

    File "*.TXT"
    File "*.txt"
    File "*.dsw"
    File "*.sln"
    File "*.dsp"
    File "*.vcproj"
    File "*.nsi"

    SetOutPath  $INSTDIR\xlw
    File /r "xlw\*.h"
    File /r "xlw\*.inl"
    File /r "xlw\*.cpp"

    SetOutPath  $INSTDIR\xlwExample
    File /r "xlwExample\xlwExample.dsw"
    File /r "xlwExample\xlwExample.sln"
    File /r "xlwExample\*.dsp"
    File /r "xlwExample\*.vcproj"
    File /r "xlwExample\xlwExample.xls"
	File /r "xlwExample\*.h"
	File /r "xlwExample\*.inl"
    File /r "xlwExample\*.cpp"

    WriteRegStr HKEY_LOCAL_MACHINE \
                "Software\Microsoft\Windows\CurrentVersion\Uninstall\XLW" \
                "DisplayName" "XLW (remove only)"
    WriteRegStr HKEY_LOCAL_MACHINE \
                "Software\Microsoft\Windows\CurrentVersion\Uninstall\XLW" \
                "UninstallString" '"XLWUninstall.exe"'
    WriteRegStr HKEY_LOCAL_MACHINE \
                "SOFTWARE\XLW" \
                "Install_Dir" "$INSTDIR"
    WriteRegStr HKEY_CURRENT_USER \
                "Environment" \
                "XLW_DIR" "$INSTDIR"
    CreateShortCut "$SMPROGRAMS\XLW\Uninstall XLW.lnk" \
                   "$INSTDIR\XLWUninstall.exe" \
                   "" "$INSTDIR\XLWUninstall.exe" 0
    CreateShortCut "$SMPROGRAMS\XLW\README.TXT.lnk" \
                   "$INSTDIR\README.TXT"
    CreateShortCut "$SMPROGRAMS\XLW\LICENSE.TXT.lnk" \
                   "$INSTDIR\LICENSE.TXT"
    CreateShortCut "$SMPROGRAMS\XLW\What's new.lnk" \
                   "$INSTDIR\NEWS.TXT"

    CreateShortCut "$SMPROGRAMS\XLW\Demo XLL VC 6 workspace.lnk" \
                   "$INSTDIR\xlwExample\xlwExample.dsw"
    CreateShortCut "$SMPROGRAMS\XLW\Demo XLL VC 7 workspace.lnk" \
                   "$INSTDIR\xlwExample\xlwExample.sln"

    CreateShortCut "$SMPROGRAMS\XLW\Demo spreadsheet.lnk" \
                   "$INSTDIR\xlwExample\xlwExample.xls"

    CreateShortCut "$SMPROGRAMS\XLW\XLW VC 6 project workspace.lnk" \
                   "$INSTDIR\xlw.dsw"

    CreateShortCut "$SMPROGRAMS\XLW\XLW VC 7 project workspace.lnk" \
                   "$INSTDIR\xlw.sln"

    WriteUninstaller "XLWUninstall.exe"
SectionEnd


Section "WinHelp documentation"
SectionIn 1
  SetOutPath "$INSTDIR\Docs"
  File /nonfatal "Docs\html\index.chm"
  IfFileExists "$INSTDIR\Docs\index.chm" 0 NoWinHelpDoc
  CreateShortCut "$SMPROGRAMS\XLW\WinHelp Documentation.lnk" \
                 "$INSTDIR\Docs\index.chm"
  NoWinHelpDoc:
SectionEnd

Section "PDF documentation"
SectionIn 1
  SetOutPath "$INSTDIR\Docs"
  File /nonfatal "Docs\latex\refman.pdf"
  IfFileExists "$INSTDIR\Docs\latex\refman.pdf" 0 NoPDFDoc
  CreateShortCut "$SMPROGRAMS\XLW\Documentation (PDF).lnk" \
                 "$INSTDIR\Docs\refman.pdf"
  NoPDFDoc:
SectionEnd


Section "Start Menu Group"
SectionIn 1 2
  SetOutPath $SMPROGRAMS\XLW

  WriteINIStr "$SMPROGRAMS\XLW\XLW Home Page.url" \
              "InternetShortcut" "URL" "http://xlw.sf.net"

  CreateShortCut "$SMPROGRAMS\XLW\XLW Directory.lnk" \
                 "$INSTDIR"
SectionEnd


UninstallText "This will uninstall XLW. Hit next to continue."


Section "Uninstall"
    DeleteRegKey HKEY_LOCAL_MACHINE \
        "Software\Microsoft\Windows\CurrentVersion\Uninstall\XLW"
    DeleteRegKey HKEY_LOCAL_MACHINE SOFTWARE\XLW
    DeleteRegValue HKEY_CURRENT_USER  "Environment" "XLW_DIR"
    Delete "$SMPROGRAMS\XLW\*.*"
    RMDir "$SMPROGRAMS\XLW"
    RMDir /r "$INSTDIR\xlwExample"
    RMDir /r "$INSTDIR\Docs\html"
    RMDir /r "$INSTDIR\lib"
    RMDir /r "$INSTDIR\xlw"
    RMDir /r "$INSTDIR"
SectionEnd

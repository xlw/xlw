;NSIS Installation script for xlw
;Uses NSIS version 2.35

;--------------------------------
;Include Modern UI

    !include "MUI2.nsh"

;--------------------------------
;Definitions

    !define APP "xlw"
    !define VER_NUMBER "3.0.0b0"
    !define APP_VER ${APP}-${VER_NUMBER}

;--------------------------------
;General

    ;Name and file
    Name "${APP}"
    OutFile "${APP_VER}.exe"

    ;Default installation folder
    InstallDir "$PROGRAMFILES\${APP_VER}"

    ;Get installation folder from registry if available
    ;InstallDirRegKey HKCU "Software\${APP_VER}" ""

    ;Request application privileges for Windows Vista
    RequestExecutionLevel user

;--------------------------------
;Interface Settings

    !define MUI_ABORTWARNING

;--------------------------------
;Pages

    !insertmacro MUI_PAGE_LICENSE "LICENSE.TXT"
    ;!insertmacro MUI_PAGE_COMPONENTS
    !insertmacro MUI_PAGE_DIRECTORY
    !insertmacro MUI_PAGE_INSTFILES

    !insertmacro MUI_UNPAGE_CONFIRM
    !insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------
;Languages

    !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section

    SetOutPath "$INSTDIR"

    File "Authors.txt"
    File "ChangeLog.txt"
    File "Contributors.txt"
    File "History.txt"
    File "LICENSE.TXT"
    File "NEWS.TXT"
    File "README.TXT"
    File "TODO.txt"

    File /r "*.cpp"
    File /r "*.h"
    File /r "*.inl"

    SetOutPath "$INSTDIR\build"

    File /r "build\*.bat"
    File /r "build\*.bat"
    File /r "build\*.dev"
    File /r "build\*.nmake"
    File /r "build\*.sln"
    File /r "build\*.vcproj"
    File "build\devcpp\README.TXT"

    SetOutPath "$INSTDIR\docs"

    File "docs\${APP_VER}-docs.chm"
    ;File "docs\xlwplus2.pdf"

    SetOutPath "$INSTDIR\examples"

    File /r "examples\*.xls"

    ;Store installation folder
    ;WriteRegStr HKCU "Software\${APP_VER}" "" $INSTDIR

    WriteRegStr HKEY_LOCAL_MACHINE \
                "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_VER}" \
                "DisplayName" "${APP} ${VER_NUMBER} (remove only)"

    WriteRegStr HKEY_LOCAL_MACHINE \
                "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_VER}" \
                "UninstallString" "$INSTDIR\Uninstall.exe"

    ;Create uninstaller
    WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

;--------------------------------
;Uninstaller Section

Section "Uninstall"

    RMDir /r /REBOOTOK "$INSTDIR"

    ;DeleteRegKey /ifempty HKCU "Software\${APP_VER}"

    DeleteRegKey HKEY_LOCAL_MACHINE \
        "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_VER}"

SectionEnd


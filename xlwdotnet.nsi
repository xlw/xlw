;------------------------------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------------------------------
;Include Modern UI

    !include "MUI2.nsh"
	!include ".\version.nsh"
	!include ".\xlw.nsh"
	!include "LogicLib.nsh"
	!include "winmessages.nsh"

;------------------------------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------------------------------
;Definitions

    !define APP "xlw"
    !define APP_VER ${APP}-${XLW_VERSION}
	 
;------------------------------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------------------------------
;General

    ;Name and file
    Name "${APP}"
    !ifndef RELEASE_VERSION
        OutFile "${APP_VER}-${SHORT_REL_DATE}.exe"
    !else
        OutFile "${APP_VER}.exe"
    !endif

	LicenseForceSelection radiobuttons "I Accept" "I Decline"
	BrandingText "${APP_VER} ${DEV_OR_RELEASE}"

    ;Default installation folder
    InstallDir $PROGRAMFILES\XLW\${APP_VER}
    ;InstallDir C:\TEMP\${APP_VER}

    ;Get installation folder from registry if available
    InstallDirRegKey HKLM "Software\XLW\${XLW_VERSION}" "InstallDir"

    ;Request application privileges for Windows Vista
    RequestExecutionLevel admin
	
;------------------------------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------------------------------
;Interface Settings

    !define MUI_ABORTWARNING
    !define MUI_ICON "xlw\docs\images\xlw_32x32.ico"
    !define MUI_UNICON "xlw\docs\images\xlw_32x32.ico"
	!define MUI_HEADERIMAGE

	!define MUI_HEADERIMAGE_BITMAP "xlw\docs\images\logo.bmp"
	!define MUI_WELCOMEFINISHPAGE_BITMAP   "xlw\docs\images\header5.bmp"
	!define MUI_WELCOMEPAGE_TITLE "Welcome to the installer of xlw ${RELEASE_SHORT}"
	
;------------------------------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------------------------------
;Pages
    !insertmacro MUI_PAGE_WELCOME
    !insertmacro MUI_PAGE_LICENSE "xlwLICENSE.rtf"

    !insertmacro MUI_PAGE_COMPONENTS
	Page custom ExcelPatchPage ;Custom page
    !insertmacro MUI_PAGE_DIRECTORY
    !insertmacro MUI_PAGE_INSTFILES

    !insertmacro MUI_UNPAGE_CONFIRM
    !insertmacro MUI_UNPAGE_INSTFILES

;------------------------------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------------------------------
;Languages

    !insertmacro MUI_LANGUAGE "English"
	
;------------------------------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------------------------------
;Global Status Vaiables

	; Excel Patcher
	
	Var DIALOG_PATCH

	Var BUTTON_PATCH

	Var EXCEL97
	Var EXCEL2000
	Var EXCEL2002
	Var EXCEL2003

	Var EXCEL97_CHECK
	Var EXCEL2000_CHECK
	Var EXCEL2002_CHECK
	Var EXCEL2003_CHECK

	Var EXCEL97_SEL
	Var EXCEL2000_SEL
	Var EXCEL2002_SEL
	Var EXCEL2003_SEL

;------------------------------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------------------------------
; macros
	!macro projectfiles dir
		SetOutPath "$INSTDIR\${dir}"
		File /nonfatal /r "${dir}\*.vcxproj"
		File /nonfatal /r "${dir}\*.vcxproj.filters"
		File /nonfatal /r "${dir}\*.sln"
		File /nonfatal /r "${dir}\*.mak"
		File /nonfatal /r "${dir}\*.nmake"
		File /nonfatal /r "${dir}\Makefile"
		File /nonfatal /r "${dir}\*.dev"
		File /nonfatal /r "${dir}\*.cbp"
		File /nonfatal /r "${dir}\*.workspace"
		File /nonfatal /r "${dir}\*.bat"
	!macroend
	
	!macro doExample dir gccaswell hasobjects

		SetOutPath "$INSTDIR\${dir}"
		File  /nonfatal /r "${dir}\*.xls"
		File  /nonfatal /r "${dir}\*.txt"
		
		SetOutPath "$INSTDIR\${dir}\common_source"
		File  /nonfatal /r "${dir}\common_source\*.cpp"
		File  /nonfatal /r "${dir}\common_source\*.h"
		File  /nonfatal /r "${dir}\common_source\*.resx"
		
		!insertmacro projectfiles "${dir}\vc10"
		!insertmacro projectfiles "${dir}\vc11"
		!insertmacro projectfiles "${dir}\vc12"
		!insertmacro projectfiles "${dir}\vc14"
		
		${If} "${gccaswell}" == "1"
			!insertmacro projectfiles "${dir}\codeblocks-gcc"
			!insertmacro projectfiles "${dir}\gcc-make"
		${EndIf}

		${If} "${hasobjects}" == "1"
			SetOutPath "$INSTDIR\${dir}\Objects"
			File  /nonfatal /r "${dir}\Objects\*.cpp"
			File  /nonfatal /r "${dir}\Objects\*.h"
		${EndIf}

	!macroend
	

;------------------------------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------------------------------

;Installer Sections

Section #
	SetOutPath "$INSTDIR\xlw"
	File "xlw\*.txt"

	SetOutPath "$INSTDIR\xlw\include"
	File /r "xlw\include\*.h"
	File /r "xlw\include\*.inl"
	File /r "xlw\include\*.def"
	
	SetOutPath "$INSTDIR\xlw\make"
	File  "xlw\make\*.*"

	SetOutPath "$INSTDIR\xlw\src"
	File /r "xlw\src\*.cpp"
	File /nonfatal /r "xlw\src\*.h"
	SetOutPath "$INSTDIR\xlw\InterfaceGenerator"
	File /r "xlw\InterfaceGenerator\*.cpp"
	File /r "xlw\InterfaceGenerator\*.h"
	SetOutPath "$INSTDIR\xlw\xlcall32stub"
	File /r "xlw\xlcall32stub\*.cpp"
	File /r "xlw\xlcall32stub\*.def"
	SetOutPath "$INSTDIR\xlw\XlwDocGen"
	File /r "xlw\XlwDocGen\*.cpp"
	
	SetOutPath "$INSTDIR\xlw\build\sandcastle"
	File "xlw\build\sandcastle\*.*"

	!insertmacro projectfiles "xlw\build\codeblocks-gcc"
	!insertmacro projectfiles "xlw\build\gcc-make"
	!insertmacro projectfiles "xlw\build\vc10"
	!insertmacro projectfiles "xlw\build\vc11"
	!insertmacro projectfiles "xlw\build\vc12"
	!insertmacro projectfiles "xlw\build\vc14"
	
	SetOutPath "$INSTDIR\xlw\bin"
	File  "xlw\bin\*.exe"
	File  "xlw\bin\*.dll"

	SetOutPath "$INSTDIR\TemplateExtractors"
	File  ".\xlwTemplateExtractor.exe"
	File  ".\xlwCppCLITemplateExtractor.exe"
	
	SetOutPath "$INSTDIR"
	File "xlwLICENSE.TXT"
	
	SetOutPath "$INSTDIR"
	File /oname=Xlw-${RELEASE_SHORT}.chm "Xlw.chm"
	
	WriteUninstaller $INSTDIR\Uninstall.exe
	
	CreateDirectory "$SMPROGRAMS\XLW\${APP_VER}\xlw"
	CreateShortCut  "$SMPROGRAMS\XLW\${APP_VER}\xlw\Extract XLW xll template.lnk" "$INSTDIR\TemplateExtractors\xlwTemplateExtractor.exe"
	CreateShortCut  "$SMPROGRAMS\XLW\${APP_VER}\xlw\Extract XLW C++/CLI xll template.lnk" "$INSTDIR\TemplateExtractors\xlwCppCLITemplateExtractor.exe"
	CreateShortCut  "$SMPROGRAMS\XLW\${APP_VER}\XLW Help.lnk" "$INSTDIR\Xlw-${RELEASE_SHORT}.chm"
	CreateShortCut  "$SMPROGRAMS\XLW\${APP_VER}\XLW License.lnk" "$INSTDIR\xlwLICENSE.TXT"
	CreateShortCut  "$SMPROGRAMS\XLW\${APP_VER}\Uninstall XLW.lnk" "$INSTDIR\Uninstall.exe"

SectionEnd

;--------------------------------
;Descriptions

;--------------------------------------------------
; xlw
SubSection "xlw" xlw

	Section "Examples" xlwExamples
	
		!insertmacro doExample "xlw\examples\Start Here - Example" 1 0
		!insertmacro doExample "xlw\examples\Commands and Attributes" 1 0
		!insertmacro doExample "xlw\examples\ObjectCacheDemo" 1 1
		!insertmacro doExample "xlw\examples\Handwritten" 1 0
		!insertmacro doExample "xlw\examples\MJ - Design Patterns" 1 0
		!insertmacro doExample "xlw\examples\LoggerDemo" 1 0
		!insertmacro doExample "xlw\examples\Typeregister" 1 0
		!insertmacro doExample "xlw\examples\C++CLR" 0 0
		!insertmacro doExample "xlw\examples\C++CLR_password" 0 0
		CreateShortCut  "$SMPROGRAMS\XLW\${APP_VER}\xlw\Examples.lnk" "$INSTDIR\xlw\Examples"
		SetOutPath "$INSTDIR\xlw\usercontrib"
		File  /r "xlw\usercontrib\*.txt"
		!insertmacro doExample "xlw\usercontrib\matrix\ublas" 1 0
		!insertmacro doExample "xlw\usercontrib\matrix\dlib" 1 0
		!insertmacro doExample "xlw\usercontrib\matrix\fortran" 1 0
		CreateShortCut  "$SMPROGRAMS\XLW\${APP_VER}\xlw\User Contributed Examples.lnk" "$INSTDIR\xlw\usercontrib"
	SectionEnd

SubSectionEnd


;----------------------------------------------------------------------------------------------------------------------
;----------------------------------------------------------------------------------------------------------------------
;Section Descriptions

LangString DESC_xlwExamples ${LANG_ENGLISH} "xlw Examples"

;Assign language strings to sections
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN

	!insertmacro MUI_DESCRIPTION_TEXT  ${xlwExamples} $(DESC_xlwExamples)

!insertmacro MUI_FUNCTION_DESCRIPTION_END

    
;----------------------------------------------------------------------------------------------------------------------
;----------------------------------------------------------------------------------------------------------------------
;Uninstaller Section

Section "Uninstall"

	Delete $INSTDIR\Uninstall.exe
	RMDir /r $INSTDIR
	DeleteRegValue HKCU "Environment" "XLW"
	DeleteRegValue HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment" "XLW"
    ; make sure windows knows about the change
    SendMessage ${HWND_BROADCAST} ${WM_WININICHANGE} 0 "STR:Environment" /TIMEOUT=5000
	
	RMDir /r "$SMPROGRAMS\XLW\${APP_VER}"
	RMDir  "$SMPROGRAMS\XLW"
    

SectionEnd

;------------------------------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------------------------------
; Functions 
Function .onInit 
	
    InitPluginsDir
	SetOutPath $TEMP
    File /oname=logo.bmp "xlw\docs\images\logo.bmp"

    advsplash::show 1000 1000 2000 0xFF6410 $TEMP\logo

    Delete $TEMP\logo.bmp

FunctionEnd

  
Function .OnInstSuccess

   	DeleteRegValue HKCU "Environment" "XLW"
	DeleteRegValue HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment" "XLW" 
    ; make sure windows knows about the change
    SendMessage ${HWND_BROADCAST} ${WM_WININICHANGE} 0 "STR:Environment" /TIMEOUT=5000
   
   
   WriteRegExpandStr HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment" "XLW" $INSTDIR
   ; make sure windows knows about the change
   SendMessage ${HWND_BROADCAST} ${WM_WININICHANGE} 0 "STR:Environment" /TIMEOUT=5000

FunctionEnd


Function ExcelPatchPage

	!insertmacro MUI_HEADER_TEXT "XLW .NET Template Extractor"  "Select the Dev environment for which the template project is to be extracted"

	StrCpy $2 0
	
	ReadRegStr $EXCEL97   HKLM "Software\Microsoft\Office\8.0\Excel\InstallRoot" "Path"  
	${If} $EXCEL97 != "" 
		IntOp $2 $2 + 1
	${EndIF}
	ReadRegStr $EXCEL2000 HKLM "Software\Microsoft\Office\9.0\Excel\InstallRoot" "Path"
	${If} $EXCEL2000 != "" 
		IntOp $2 $2 + 1
	${EndIF}	
	ReadRegStr $EXCEL2002 HKLM "Software\Microsoft\Office\10.0\Excel\InstallRoot" "Path"  
	${If} $EXCEL2002 != "" 
		IntOp $2 $2 + 1
	${EndIF}
	ReadRegStr $EXCEL2003 HKLM "Software\Microsoft\Office\11.0\Excel\InstallRoot" "Path" 
	${If} $EXCEL2003 != "" 
		IntOp $2 $2 + 1
	${EndIF}
	
	${If} $2 != 0
	
		GetDlgItem $0 $HWNDPARENT 1
		EnableWindow $0 1

		nsDialogs::Create 1018
		Pop $DIALOG_PATCH
		
		
		${NSD_CreateLabel} 5 2 100% 17% "Detected the following of version(s) of Excel that do not correctly load .NET CLR 2 at startup. Select the Excel(s) that you would like the installer to patch, else leave unselected to either patch manualy later or if you only intend to write C++ xlls."
		Pop $2
		${NSD_CreateLabel} 5 50 100% 10% "Note : .NET xlls will not work without the correct CLR being loaded at Excel startup"  
		Pop $2
		
		GetFunctionAddress $0 CheckChanged
		StrCpy $1 70
		
		
		${If} $EXCEL97 != "" 
			${NSD_CreateCheckBox} 170 $1 100% 10% "Excel 97"    
			Pop $EXCEL97_CHECK
			nsDialogs::OnClick   $EXCEL97_CHECK $0
			IntOp $1 $1 + 30
		${EndIF}
		

		${If} $EXCEL2000 != "" 
			${NSD_CreateCheckBox} 170 $1 100% 10% "Excel 2000"     
			Pop $EXCEL2000_CHECK
			nsDialogs::OnClick   $EXCEL2000_CHECK $0
			IntOp $1 $1 + 30
		${EndIF}
		

		${If} $EXCEL2002 != "" 
			${NSD_CreateCheckBox} 170 $1 100% 10% "Excel XP (2002)"     
			Pop $EXCEL2002_CHECK
			nsDialogs::OnClick   $EXCEL2002_CHECK $0
			IntOp $1 $1 + 30
		${EndIF}
		
	 
		${If} $EXCEL2003 != "" 
			${NSD_CreateCheckBox} 170 $1 100% 10% "Excel 2003"      
			Pop $EXCEL2003_CHECK
			nsDialogs::OnClick   $EXCEL2003_CHECK $0
			IntOp $1 $1 + 30
		${EndIF}
			

		${NSD_CreateButton} 170 200 30% 10% "Tell Me More ..."
		Pop $BUTTON_PATCH
		
		GetFunctionAddress $0 OnClick_PATCH
		nsDialogs::OnClick $BUTTON_PATCH $0


		nsDialogs::Show
			
	${EndIF}

FunctionEnd

Function CheckChanged
	Pop $0 # dir hwnd
	
	${NSD_GetState} $EXCEL97_CHECK $EXCEL97_SEL
	${NSD_GetState} $EXCEL2000_CHECK $EXCEL2000_SEL
	${NSD_GetState} $EXCEL2002_CHECK $EXCEL2002_SEL
	${NSD_GetState} $EXCEL2003_CHECK $EXCEL2003_SEL


FunctionEnd

Function OnClick_PATCH

	Pop $0 # HWND
	
	StrCpy $0    " Some versions of Excel do not load the correct .NET Runtime at startup. C# and other .NET xlls built by XLW require$\r$\n"
	StrCpy $0 "$0 CLR 2, the runtime for .NET 2.0, .NET 3.0 and .NET 3.5 Frameworks. Excel can be forced to load v2 of the runtime (CLR), $\r$\n"
	StrCpy $0 "$0 by placing a small xml file  'Excel.exe.config' :$\r$\n"
	StrCpy $0 "$0 $\r$\n$\r$\n"
	StrCpy $0 '$0            <?xml version="1.0"?>$\r$\n'
	StrCpy $0 "$0                <configuration>$\r$\n"
	StrCpy $0 "$0                   <startup>$\r$\n"
	StrCpy $0 '$0                       <supportedRuntime version="v2.0.50727" /> $\r$\n'
	StrCpy $0 "$0                   <startup>$\r$\n"
	StrCpy $0 "$0                <configuration>"
	StrCpy $0 "$0 $\r$\n$\r$\n"
	StrCpy $0 "$0 into the same directory as the Excel executable.$\r$\n"
	StrCpy $0 "$0 This can either be done by the installer or manualy by the user after installation. For the installer to carry out this$\r$\n"
	StrCpy $0 "$0 workaround just tick the checkboxes alongside the Excel version you would like to patch.$\r$\n$\r$\n"
	StrCpy $0 "$0 See MSDN documentation for more information $\r$\n$\r$\n"
	StrCpy $0 "$0 http://msdn.microsoft.com/en-us/library/w4atty68.aspx $\r$\n"
	MessageBox MB_OK $0

FunctionEnd

















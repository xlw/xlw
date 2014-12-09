    !include "MUI2.nsh"
	!include ".\version.nsh"
	!include ".\xlw.nsh"
	!include "LogicLib.nsh"


;------------------------------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------------------------------
;Definitions

    !define APP "xlwTemplateExtractor"
	Name "${APP}"
    OutFile "${APP}.exe"
	RequestExecutionLevel user
	BrandingText "${APP}"
	InstallDir "$DOCUMENTS\XLL_Project"


;------------------------------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------------------------------
;Interface Settings

	!define MUI_PAGE_HEADER_TEXT "Select Installation Directory"
	!define MUI_PAGE_HEADER_SUBTEXT "Select the directory where the template project will be placed"
	!define MUI_DIRECTORYPAGE_TEXT_TOP "When the project is extracted, you should start by changing the name of the project folder and any relevant project files"
    !define MUI_ABORTWARNING
    !define MUI_ICON "xlw\docs\images\xlw_32x32.ico"
    !define MUI_UNICON "xlw\docs\images\xlw_32x32.ico"
	!define MUI_HEADERIMAGE

	!define MUI_HEADERIMAGE_BITMAP "xlw\docs\images\logo.bmp"
	
	



;------------------------------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------------------------------
;Pages

	Page custom ExtractorPage ;Custom page

    !insertmacro MUI_PAGE_DIRECTORY
    !insertmacro MUI_PAGE_INSTFILES

	
;------------------------------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------------------------------
;Languages

    !insertmacro MUI_LANGUAGE "English"
	
;------------------------------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------------------------------

;------------------------------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------------------------------

Var DIALOG
Var HEADLINE
Var TEXT
Var IMAGECTL
Var IMAGE
Var DIRECTORY
Var FREESPACE

Var HEADLINE_FONT
Var STATE
	
Var VC12
Var VC11
Var VC10
Var VC9
Var VC8
Var VC71
Var CODEBLOCKS

Var GCC

Var VC12_STATE
Var VC11_STATE
Var VC10_STATE
Var VC9_STATE
Var VC8_STATE
Var VC71_STATE
Var CODEBLOCKS_STATE

Var GCC_STATE



	
Function ExtractorPage

	!insertmacro MUI_HEADER_TEXT "XLW Template Extractor"  "Select the Dev environment for which the template project is to be extracted"

	GetDlgItem $0 $HWNDPARENT 1
	EnableWindow $0 0

	nsDialogs::Create 1018
	Pop $DIALOG

	GetFunctionAddress $0 RadioChanged
	
    ${NSD_CreateRadioButton} 100 30 100% 10% "Visual C++ 2013 (VC12)"    
	Pop $VC12
	nsDialogs::OnClick  $VC12 $0
    ${NSD_CreateRadioButton} 100 30 100% 10% "Visual C++ 2012 (VC11)"    
	Pop $VC11
	nsDialogs::OnClick  $VC11 $0
	${NSD_CreateRadioButton} 100 60 100% 10% "Visual C++ 2010 (VC10)"    
	Pop $VC10
	nsDialogs::OnClick  $VC10 $0
	${NSD_CreateRadioButton} 100 90 100% 10% "Visual C++ 2008 (VC9)"    
	Pop $VC9
	nsDialogs::OnClick  $VC9 $0
    ${NSD_CreateRadioButton} 100 120 100% 10% "Visual C++ 2005 (VC8)" 
	Pop $VC8
	nsDialogs::OnClick  $VC8 $0
	${NSD_CreateRadioButton} 100 150 100% 10% "Visual C++ 2003 (VC7.1)" 
	Pop $VC71
	nsDialogs::OnClick  $VC71 $0
	${NSD_CreateRadioButton} 100 180 100% 10% "Code::Blocks(MingW)"
	Pop $CODEBLOCKS
	nsDialogs::OnClick  $CODEBLOCKS $0
	;${NSD_CreateRadioButton} 100 150 100% 10% "Dev-C++"
	;Pop $DEVCPP
	;nsDialogs::OnClick  $DEVCPP $0
	${NSD_CreateRadioButton} 100 210 100% 10% "GCC/Make"
	Pop $GCC
	nsDialogs::OnClick  $GCC $0
	
	nsDialogs::Show

FunctionEnd

Var RadioStatus

Function RadioChanged
	Pop $0 # dir hwnd

	GetDlgItem $0 $HWNDPARENT 1
	EnableWindow $0 1

	${NSD_GetState} $VC12 $VC12_STATE
	${NSD_GetState} $VC11 $VC11_STATE
	${NSD_GetState} $VC10 $VC10_STATE
	${NSD_GetState} $VC9 $VC9_STATE
	${NSD_GetState} $VC8 $VC8_STATE
	${NSD_GetState} $VC71 $VC71_STATE
	${NSD_GetState} $CODEBLOCKS $CODEBLOCKS_STATE
	${NSD_GetState} $GCC $GCC_STATE
	
FunctionEnd

Var DIR

!macro projectfiles dir
		SetOutPath "$INSTDIR"
		File /nonfatal /r "xlw\Template_Projects\${dir}\*.vcxproj"
		File /nonfatal /r "xlw\Template_Projects\${dir}\*.vcproj"
		File /nonfatal /r "xlw\Template_Projects\${dir}\*.csproj"
		File /nonfatal /r "xlw\Template_Projects\${dir}\*.sln"
		File /nonfatal /r "xlw\Template_Projects\${dir}\*.mak"
		File /nonfatal /r "xlw\Template_Projects\${dir}\*.nmake"
		File /nonfatal /r "xlw\Template_Projects\${dir}\Makefile.RELEASE"
		File /nonfatal /r "xlw\Template_Projects\${dir}\Makefile"
		File /nonfatal /r "xlw\Template_Projects\${dir}\*.dev"
		File /nonfatal /r "xlw\Template_Projects\${dir}\*.cbp"
		File /nonfatal /r "xlw\Template_Projects\${dir}\*.workspace"
		File /nonfatal /r "xlw\Template_Projects\${dir}\*.bat"
		CreateDirectory  "$INSTDIR\AutoGeneratedSource"

	!macroend
	
		
	!macro sourcefiles dir
		SetOutPath "$INSTDIR"
		File /nonfatal /r "xlw\Template_Projects\${dir}\*.cpp"
		File /nonfatal /r "xlw\Template_Projects\${dir}\*.h"
		File /nonfatal /r "xlw\Template_Projects\${dir}\*.cs"
		File /nonfatal /r "xlw\Template_Projects\${dir}\*.snk"
	!macroend



!macro GETDIR  STATEFLAG TDIR

	${If} ${STATEFLAG} ==  ${BST_CHECKED}

			!insertmacro projectfiles ${TDIR}
			!insertmacro sourcefiles  ${TDIR}
			 Exec "explorer.exe $INSTDIR" 
	${Endif}


!macroend

Section #
	!insertmacro GETDIR $VC12_STATE "vc12"
	!insertmacro GETDIR $VC11_STATE "vc11"
	!insertmacro GETDIR $VC10_STATE "vc10"
	!insertmacro GETDIR $VC9_STATE "vc9"
	!insertmacro GETDIR $VC8_STATE "vc8"
	!insertmacro GETDIR $VC71_STATE "vc7"
	!insertmacro GETDIR $CODEBLOCKS_STATE "codeblocks-gcc"
	!insertmacro GETDIR $GCC_STATE "gcc-make"

SectionEnd 











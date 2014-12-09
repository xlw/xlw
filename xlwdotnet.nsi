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

	Page custom DevEnvironFinder ;Custom page
	Page custom PlatformSDK ;Custom page
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

	 Var VS2003_Saved
	 Var VS2005_Saved
	 Var VS2008_Saved
	 Var VS2010_Saved
	 Var VS2012_Saved
	 Var VS2013_Saved
	 Var CODEBLOCKS_Saved
	 Var GCCMAKE_Saved
	 
	 Var VS2005DotNet_Saved
	 Var VS2008DotNet_Saved
	 Var VS2010DotNet_Saved
	 Var VS2012DotNet_Saved
	 Var VS2013DotNet_Saved
	 
	Var Dialog
	Var Label
	Var ListBox
	
	
	Var VS2013_INST
	
	Var VS2012_INST
	
	Var VS2010PRO_CPP_INST
	Var VS2010PRO_CSharp_INST
	Var VS2010PRO_VisualBasic_INST
	
	Var VS2010EXP_CPP_INST
	Var VS2010EXP_CSharp_INST
	Var VS2010EXP_VisualBasic_INST
	
	Var VS2008PRO_CPP_INST
	Var VS2008PRO_CSharp_INST
	Var VS2008PRO_VisualBasic_INST
	
	Var VS2008EXP_CPP_INST
	Var VS2008EXP_CSharp_INST
	Var VS2008EXP_VisualBasic_INST
	
	Var VS2005PRO_CPP_INST
	Var VS2005PRO_CSharp_INST
	Var VS2005PRO_VisualBasic_INST
	
	Var VS2005EXP_CPP_INST
	Var VS2005EXP_CSharp_INST
	Var VS2005EXP_VisualBasic_INST
	
	Var VS2003PRO_CPP_INST
	Var CodeBlocks_INST

	Var PSDK
	
	Var CPP_DETECTED
	
	Var CodeBlocks_FRMWK
	
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
		File /nonfatal /r "${dir}\*.vcproj"
		File /nonfatal /r "${dir}\*.vcxproj"
		File /nonfatal /r "${dir}\*.csproj"
		File /nonfatal /r "${dir}\*.vbproj"
		File /nonfatal /r "${dir}\*.sln"
		File /nonfatal /r "${dir}\*.mak"
		File /nonfatal /r "${dir}\*.nmake"
		File /nonfatal /r "${dir}\Makefile.RELEASE"
		File /nonfatal /r "${dir}\Makefile"
		File /nonfatal /r "${dir}\*.dev"
		File /nonfatal /r "${dir}\*.cbp"
		File /nonfatal /r "${dir}\*.workspace"
		File /nonfatal /r "${dir}\*.bat"
		CreateDirectory  "$INSTDIR\${dir}\AutoGeneratedSource"
	!macroend
	
		
	!macro sourcefiles dir
		SetOutPath "$INSTDIR\${dir}"
		File /nonfatal /r "${dir}\*.cpp"
		File /nonfatal /r "${dir}\*.h"
		File /nonfatal /r "${dir}\*.cs"
		File /nonfatal /r "${dir}\*.snk"
		File /nonfatal /r "${dir}\*.vb"
	!macroend
	
	!macro addsource
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
	!macroend
	

	!macro buildfiles  dir
		!insertmacro projectfiles "xlw\build\${dir}"
		!insertmacro addsource
	!macroend

	Var X
	
	!macro insertline
		${NSD_LB_AddString} $ListBox_right ""
	!macroend
	
	!macro FINDENV root key subkey env
		ReadRegStr $X  ${root} "${key}"  "${subkey}" 
		${If} $X != ""
			${NSD_LB_AddString} $ListBox_right "Detected ${env}"
			!insertmacro insertline
		${EndIf}
		Push $X
	!macroend
	
	!macro DotNetbuildfiles  dir
		SetOutPath "$INSTDIR\xlwDotNet\xlwDotNet"
		File  "xlwDotNet\xlwDotNet\*.cpp"

		SetOutPath "$INSTDIR\xlwDotNet\build\${dir}"
		File /r "xlwDotNet\build\${dir}\*.sln"
		File /r "xlwDotNet\build\${dir}\*.vcproj"
		File /r "xlwDotNet\build\${dir}\*.csproj"
	
	!macroend
	
	
	!macro DotNetbuildfiles_VS10  dir
		SetOutPath "$INSTDIR\xlwDotNet\xlwDotNet"
		File  "xlwDotNet\xlwDotNet\*.cpp"

		SetOutPath "$INSTDIR\xlwDotNet\build\${dir}"
		File /r "xlwDotNet\build\${dir}\*.sln"
		File /r "xlwDotNet\build\${dir}\*.vcxproj"
		File /r "xlwDotNet\build\${dir}\*.csproj"
	
	!macroend
	
	
	
	!macro DotNetHeaders
			SetOutPath "$INSTDIR\xlwDotNet\xlwDotNet"
			File  "xlwDotNet\xlwDotNet\*.h"
			File  "xlwDotNet\xlwDotNet\*.snk"
			
			SetOutPath "$INSTDIR\xlwDotNet\vc_common"
			File  "xlwDotNet\vc_common\*.nmake"
	
	!macroend
	
	!macro dotNetInterfaceGenSource
			SetOutPath "$INSTDIR\xlwDotNet\DotNetInterfaceGenerator"
			File  /r "xlwDotNet\DotNetInterfaceGenerator\*.cs"
	!macroend	
	
	!macro DotNetInterfaceGenerator  dir
			SetOutPath "$INSTDIR\xlwDotNet\build\${dir}\Debug"
			File  "xlwDotNet\build\${dir}\Debug\*.dll"
			File  "xlwDotNet\build\${dir}\Debug\*.exe"
			File  "xlwDotNet\build\${dir}\Debug\*.pdb"
			
			SetOutPath "$INSTDIR\xlwDotNet\build\${dir}\Release"
			File  "xlwDotNet\build\${dir}\Release\*.dll"
			File  "xlwDotNet\build\${dir}\Release\*.exe"
			
			!insertmacro DotNetHeaders
	!macroend

	!macro DotNetInterfaceGenerator64  dir
			SetOutPath "$INSTDIR\xlwDotNet\build\${dir}\x64_Debug"
			File  "xlwDotNet\build\${dir}\x64_Debug\*.dll"
			File  "xlwDotNet\build\${dir}\x64_Debug\*.exe"
			File  "xlwDotNet\build\${dir}\x64_Debug\*.pdb"
			
			SetOutPath "$INSTDIR\xlwDotNet\build\${dir}\x64_Release"
			File  "xlwDotNet\build\${dir}\x64_Release\*.dll"
			File  "xlwDotNet\build\${dir}\x64_Release\*.exe"
			
			!insertmacro DotNetHeaders
	!macroend
	
	!macro InterfaceGenerator  dir
			SetOutPath "$INSTDIR\xlw\build\${dir}\Debug"
			File  "xlw\build\${dir}\Debug\*.exe"
			File  "xlw\build\${dir}\Debug\*.pdb"
			File  "xlw\build\${dir}\Debug\*.dll"
			
			SetOutPath "$INSTDIR\xlw\build\${dir}\Release"
			File  "xlw\build\${dir}\Release\*.exe"
			File  "xlw\build\${dir}\Release\*.dll"
			
	!macroend
	
	!macro doExampleVCHelper dir
	
			SetOutPath "$INSTDIR\${dir}"
			File  /nonfatal /r "${dir}\*.cpp"
			File  /nonfatal /r "${dir}\*.h"
			File  /nonfatal /r "${dir}\*.vcproj"
			File  /nonfatal /r "${dir}\*.vcxproj"
			File  /nonfatal /r "${dir}\*.csproj"
			File  /nonfatal /r "${dir}\*.vcxproj.filters"
			File  /nonfatal /r "${dir}\*.sln"
			File  /nonfatal /r "${dir}\*.nmake"
			File  /nonfatal /r "${dir}\*.bat"
			;CreateDirectory  "$INSTDIR\${dir}\AutoGeneratedSource"
	!macroend
	
	!macro doExample dir gccaswell vs2003aswell
			Push $0
			
			SetOutPath "$INSTDIR\${dir}"
			File  /nonfatal /r "${dir}\*.xls"
			File  /nonfatal /r "${dir}\*.txt"
			
			SetOutPath "$INSTDIR\${dir}\common_source"
			File  /nonfatal /r "${dir}\common_source\*.cpp"
			File  /nonfatal /r "${dir}\common_source\*.h"
			File  /nonfatal /r "${dir}\common_source\*.resx"
			
			SetOutPath "$INSTDIR\${dir}\Objects"
			File  /nonfatal /r "${dir}\Objects\*.cpp"
			File  /nonfatal /r "${dir}\Objects\*.h"
			
			
			${If} ${vs2003aswell} == 1
				SectionGetFlags ${VS2003} $0 
				${If} $0 == "1"
					!insertmacro doExampleVCHelper "${dir}\vc7"
				${EndIf}
			${EndIf}
			
			SectionGetFlags ${VS2005} $0 
			${If} $0 == "1"
				!insertmacro doExampleVCHelper "${dir}\vc8"
			${EndIf}
			
			SectionGetFlags ${VS2008} $0 
			${If} $0 == "1"
				!insertmacro doExampleVCHelper "${dir}\vc9"
			${EndIf}
			
			SectionGetFlags ${VS2010} $0 
			${If} $0 == "1"
				!insertmacro doExampleVCHelper "${dir}\vc10"
			${EndIf}
			
			SectionGetFlags ${VS2012} $0 
			${If} $0 == "1"
				!insertmacro doExampleVCHelper "${dir}\vc11"
			${EndIf}

			SectionGetFlags ${VS2013} $0 
			${If} $0 == "1"
				!insertmacro doExampleVCHelper "${dir}\vc12"
			${EndIf}
			
			${If} ${gccaswell} == 1
			
					SectionGetFlags ${CODEBLOCKS} $0 
					${If} $0 == "1"
						SetOutPath "$INSTDIR\${dir}\codeblocks-gcc"
						File  /nonfatal /r "${dir}\codeblocks-gcc\*.cbp"
						File  /nonfatal /r "${dir}\codeblocks-gcc\*.mak"
						File  /nonfatal /r "${dir}\codeblocks-gcc\*.workspace"
						File  /nonfatal /r "${dir}\codeblocks-gcc\*.bat"
					${EndIf}
					
					SectionGetFlags ${GCCMAKE} $0 
					${If} $0 == "1"
						SetOutPath "$INSTDIR\${dir}\gcc-make"
						File  /nonfatal /r "${dir}\gcc-make\Makefile"
						File  /nonfatal /r "${dir}\gcc-make\*.mak"
						File  /nonfatal /r "${dir}\gcc-make\*.bat"
					${EndIf}
					
			${EndIf}
			
			Pop $0
	!macroend
	
	!macro doDotNetExample dir
			Push $0
			
			SetOutPath "$INSTDIR\${dir}"
			File  /nonfatal /r "${dir}\*.xls"
			File  /nonfatal /r "${dir}\*.txt"
			
			SetOutPath "$INSTDIR\${dir}\common_source"
			File  /nonfatal /r "${dir}\common_source\*.cs"
			File  /nonfatal /r "${dir}\common_source\*.snk"
			

			SectionGetFlags ${VS2005DotNet} $0 
			${If} $0 == "1"
				!insertmacro doExampleVCHelper "${dir}\VS8"
			${EndIf}
			
			SectionGetFlags ${VS2008DotNet} $0 
			${If} $0 == "1"
				!insertmacro doExampleVCHelper "${dir}\VS9"
			${EndIf}
			
			SectionGetFlags ${VS2010DotNet} $0 
			${If} $0 == "1"
				!insertmacro doExampleVCHelper "${dir}\VS10"
			${EndIf}
			
			SectionGetFlags ${VS2012DotNet} $0 
			${If} $0 == "1"
				!insertmacro doExampleVCHelper "${dir}\VS11"
			${EndIf}

			SectionGetFlags ${VS2013DotNet} $0 
			${If} $0 == "1"
				!insertmacro doExampleVCHelper "${dir}\VS12"
			${EndIf}
			
			Pop $0
	!macroend
	
	!macro xlwDotNetReadMes
		SetOutPath "$INSTDIR\xlwDotNet"
		File "xlwDotNet\*.txt"
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
		
		SetOutPath "$INSTDIR\TemplateExtractors"
		File  ".\xlwTemplateExtractor.exe"
		File  ".\xlwDotNetTemplateExtractor.exe"
		File  ".\xlwCppCLITemplateExtractor.exe"

		
		SetOutPath "$INSTDIR"
		File "xlwLICENSE.TXT"
		
		SetOutPath "$INSTDIR"
		File /oname=Xlw-${RELEASE_SHORT}.chm "Xlw.chm"
		
		SetOutPath "$INSTDIR\utils"
		File "MinGW_Installer\xlw-MinGW-Installer-gcc-4.5.2-1.exe"
		
		
		!insertmacro xlwDotNetReadMes
		
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

    ; vanilla xlw
	SectionGroup "Libraries" Libraries
	
		Section "VS2003"  VS2003
			SetOutPath "$INSTDIR\xlw\lib"
			File  "xlw\lib\xlw-vc71*.lib"
			File  "xlw\lib\xlw-vc71*.pdb"
			!insertmacro InterfaceGenerator vc7
			
		SectionEnd
		
		Section "VS2005" VS2005
			SetOutPath "$INSTDIR\xlw\lib"
			File "xlw\lib\xlw-vc80*.lib"
			File "xlw\lib\xlw-vc80*.pdb"
			SetOutPath "$INSTDIR\xlw\lib\x64"
			File  "xlw\lib\x64\xlw-vc80*.lib"
			File  "xlw\lib\x64\xlw-vc80*.pdb"
			!insertmacro InterfaceGenerator vc8
		SectionEnd
		
		Section "VS2008" VS2008
			SetOutPath "$INSTDIR\xlw\lib"
			File  "xlw\lib\xlw-vc90*.lib"
			File  "xlw\lib\xlw-vc90*.pdb"
			SetOutPath "$INSTDIR\xlw\lib\x64"
			File  "xlw\lib\x64\xlw-vc90*.lib"
			File  "xlw\lib\x64\xlw-vc90*.pdb"
			!insertmacro InterfaceGenerator vc9
		SectionEnd
		
		
		Section "VS2010" VS2010
			SetOutPath "$INSTDIR\xlw\lib"
			File  "xlw\lib\xlw-vc100*.lib"
			File  "xlw\lib\xlw-vc100*.pdb"
			SetOutPath "$INSTDIR\xlw\lib\x64"
			File  "xlw\lib\x64\xlw-vc100*.lib"
			File  "xlw\lib\x64\xlw-vc100*.pdb"
			!insertmacro InterfaceGenerator vc10
		SectionEnd
		
		Section "VS2012" VS2012
			SetOutPath "$INSTDIR\xlw\lib"
			File  "xlw\lib\xlw-vc110*.lib"
			File  "xlw\lib\xlw-vc110*.pdb"
			SetOutPath "$INSTDIR\xlw\lib\x64"
			File  "xlw\lib\x64\xlw-vc110*.lib"
			File  "xlw\lib\x64\xlw-vc110*.pdb"
			!insertmacro InterfaceGenerator vc11
		SectionEnd

		Section "VS2013" VS2013
			SetOutPath "$INSTDIR\xlw\lib"
			File  "xlw\lib\xlw-vc120*.lib"
			File  "xlw\lib\xlw-vc120*.pdb"
			SetOutPath "$INSTDIR\xlw\lib\x64"
			File  "xlw\lib\x64\xlw-vc120*.lib"
			File  "xlw\lib\x64\xlw-vc120*.pdb"
			!insertmacro InterfaceGenerator vc12
		SectionEnd
		
		Section "Code::Blocks(mingw)" CODEBLOCKS
			SetOutPath "$INSTDIR\xlw\lib"
			File  "xlw\lib\libxlw-gcc*.a"
			SetOutPath "$INSTDIR\xlw\lib\x64"
			File  "xlw\lib\x64\libxlw-gcc*.a"
			SetOutPath "$INSTDIR\xlw\build\codeblocks-gcc\bin"
			File /r "xlw\build\codeblocks-gcc\bin\*.exe"
			File /r "xlw\build\codeblocks-gcc\bin\*.dll"
		SectionEnd
		
		Section "make(mingw)" GCCMAKE
			SetOutPath "$INSTDIR\xlw\lib"
			File  "xlw\lib\libxlw-gcc*.a"
			SetOutPath "$INSTDIR\xlw\lib\x64"
			File  "xlw\lib\x64\libxlw-gcc*.a"
			SetOutPath "$INSTDIR\xlw\build\gcc-make"
			File /r "xlw\build\gcc-make\*.exe"
			File /r "xlw\build\gcc-make\*.dll"
		SectionEnd
		


	SectionGroupEnd

	Section "Examples" xlwExamples
	
		!insertmacro doExample "xlw\examples\Start Here - Example" 1 1
		!insertmacro doExample "xlw\examples\Commands and Attributes" 1 1
		!insertmacro doExample "xlw\examples\ObjectCacheDemo" 1 1
		!insertmacro doExample "xlw\examples\Handwritten" 1 1
		!insertmacro doExample "xlw\examples\MJ - Design Patterns" 1 1
		!insertmacro doExample "xlw\examples\LoggerDemo" 1 1
		!insertmacro doExample "xlw\examples\Typeregister" 1 1
		!insertmacro doExample "xlw\examples\C++CLR" 0 0
		!insertmacro doExample "xlw\examples\C++CLR_password" 0 0
		CreateShortCut  "$SMPROGRAMS\XLW\${APP_VER}\xlw\Examples.lnk" "$INSTDIR\xlw\Examples"
		SetOutPath "$INSTDIR\xlw\usercontrib"
		File  /r "xlw\usercontrib\*.txt"
		!insertmacro doExample "xlw\usercontrib\matrices\ublas" 1 1
		!insertmacro doExample "xlw\usercontrib\matrices\dlib" 1 1
		!insertmacro doExample "xlw\usercontrib\matrices\fortran" 1 1
		CreateShortCut  "$SMPROGRAMS\XLW\${APP_VER}\xlw\User Contributed Examples.lnk" "$INSTDIR\xlw\usercontrib"
	SectionEnd

	Section "Sandcastle" sandcastle
			SetOutPath "$INSTDIR\xlw\build\sandcastle"
			File "xlw\build\sandcastle\*.*"
	SectionEnd
	
	; vanilla xlw sources
	SectionGroup "Source" Source
	


		Section "VS2003" VS2003_SRC
			!insertmacro buildfiles "vc7"
			!insertmacro projectfiles "xlw\Template_Projects\vc7"
			!insertmacro sourcefiles  "xlw\Template_Projects\vc7"

		SectionEnd
		
		Section "VS2005" VS2005_SRC
			!insertmacro buildfiles "vc8"
			!insertmacro projectfiles "xlw\Template_Projects\vc8"
			!insertmacro sourcefiles  "xlw\Template_Projects\vc8"
		SectionEnd
		
		
		Section "VS2008" VS2008_SRC
			!insertmacro buildfiles "vc9"
			!insertmacro projectfiles "xlw\Template_Projects\vc9"
			!insertmacro sourcefiles  "xlw\Template_Projects\vc9"
		SectionEnd
		
		
		Section "VS2010" VS2010_SRC
			!insertmacro buildfiles "vc10"
			!insertmacro projectfiles "xlw\Template_Projects\vc10"
			!insertmacro sourcefiles  "xlw\Template_Projects\vc10"
		SectionEnd
		
		Section "VS2012" VS2012_SRC
			!insertmacro buildfiles "vc11"
			!insertmacro projectfiles "xlw\Template_Projects\vc11"
			!insertmacro sourcefiles  "xlw\Template_Projects\vc11"
		SectionEnd

		Section "VS2013" VS2013_SRC
			!insertmacro buildfiles "vc12"
			!insertmacro projectfiles "xlw\Template_Projects\vc12"
			!insertmacro sourcefiles  "xlw\Template_Projects\vc12"
		SectionEnd

		
		Section "Code::Blocks(mingw)" CODEBLOCKS_SRC
			!insertmacro buildfiles "codeblocks-gcc"
			!insertmacro projectfiles "xlw\Template_Projects\codeblocks-gcc"
			!insertmacro sourcefiles  "xlw\Template_Projects\codeblocks-gcc"
		SectionEnd
		
		Section "make(mingw)" GCCMAKE_SRC
			!insertmacro buildfiles "gcc-make"
			!insertmacro projectfiles "xlw\Template_Projects\gcc-make"
			!insertmacro sourcefiles  "xlw\Template_Projects\gcc-make"
		SectionEnd
		
		

		
	SectionGroupEnd
SubSectionEnd



;--------------------------------------------------
; xlwDotNet
SubSection "xlwDotNet" xlwDotNet

		
    ; vanilla xlw
	SectionGroup "Libraries" xlwDotNetLibraries
	
	Section #
				${If} $EXCEL97_SEL  ==  ${BST_CHECKED}
						IfFileExists "$EXCEL97\Excel.exe.config" Warn97 Install97 
						Install97:
							SetOutPath "$EXCEL97"
							File  "ExcelPatch\Excel.exe.config"
							Goto Do2000
						Warn97:
						MessageBox MB_OK "$EXCEL97\Excel.exe.config exists. Installer will not overwrite it. A manual patch maybe required"

				${EndIF}
				
				Do2000:
				${If} $EXCEL2000_SEL ==  ${BST_CHECKED} 
						IfFileExists "$EXCEL2000\Excel.exe.config"  Warn2000 Install2000
						Install2000:
							SetOutPath "$EXCEL2000"
							File  "ExcelPatch\Excel.exe.config"
							Goto Do2002
						Warn2000:
						MessageBox MB_OK "$EXCEL2000\Excel.exe.config exists. Installer will not overwrite it. A manual patch maybe required"
				${EndIF}

				Do2002:
				${If} $EXCEL2002_SEL ==  ${BST_CHECKED} 
						IfFileExists "$EXCEL2002\Excel.exe.config" Warn2002 Install2002
						Install2002:
							SetOutPath "$EXCEL2002"
							File  "ExcelPatch\Excel.exe.config"
							Goto Do2003
						Warn2002:
						MessageBox MB_OK "$EXCEL2002\Excel.exe.config exists. Installer will not overwrite it. A manual patch maybe required"
				${EndIF}

				Do2003:
				${If} $EXCEL2003_SEL ==  ${BST_CHECKED}
						IfFileExists "$EXCEL2003\Excel.exe.config" Warn2003 Install2003
						Install2003:
							SetOutPath "$EXCEL2003"
							File  "ExcelPatch\Excel.exe.config"
							Goto FINISH
						Warn2003:
						MessageBox MB_OK "$EXCEL2003\Excel.exe.config exists. Installer will not overwrite it. A manual patch maybe required"
				${EndIF}
				
				FINISH:

		SectionEnd 


	
		Section "VS2005" VS2005DotNet
			SetOutPath "$INSTDIR\xlwDotNet\lib"
			File "xlwDotNet\lib\xlwDotNet-vc80*.dll"
			File "xlwDotNet\lib\xlwDotNet-vc80*.pdb"
			SetOutPath "$INSTDIR\xlwDotNet\lib\x64"
			File "xlwDotNet\lib\x64\xlwDotNet-vc80*.dll"
			File "xlwDotNet\lib\x64\xlwDotNet-vc80*.pdb"
			!insertmacro DotNetInterfaceGenerator VS8
			!insertmacro DotNetInterfaceGenerator64 VS8
			!insertmacro projectfiles "xlwDotNet\Template_Projects\VS8"
			!insertmacro sourcefiles  "xlwDotNet\Template_Projects\VS8"
			!insertmacro projectfiles "xlwDotNet\Template_Projects\VisualBasic\VB2005"
			!insertmacro sourcefiles  "xlwDotNet\Template_Projects\VisualBasic\VB2005"
			!insertmacro projectfiles "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS8_PRO"
			!insertmacro sourcefiles  "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS8_PRO"
			CreateDirectory "$SMPROGRAMS\XLW\${APP_VER}\xlwDotNet"
			CreateShortCut  "$SMPROGRAMS\XLW\${APP_VER}\xlwDotNet\Extract XLW .NET xll template.lnk" "$INSTDIR\TemplateExtractors\xlwDotNetTemplateExtractor.exe"

		SectionEnd
		
		Section "VS2008" VS2008DotNet
			SetOutPath "$INSTDIR\xlwDotNet\lib"
			File "xlwDotNet\lib\xlwDotNet-vc90*.dll"
			File "xlwDotNet\lib\xlwDotNet-vc90*.pdb"
			SetOutPath "$INSTDIR\xlwDotNet\lib\x64"
			File "xlwDotNet\lib\x64\xlwDotNet-vc90*.dll"
			File "xlwDotNet\lib\x64\xlwDotNet-vc90*.pdb"
			!insertmacro DotNetInterfaceGenerator VS9
			!insertmacro DotNetInterfaceGenerator64 VS9
			!insertmacro projectfiles "xlwDotNet\Template_Projects\VS9"
			!insertmacro sourcefiles  "xlwDotNet\Template_Projects\VS9"
			!insertmacro projectfiles "xlwDotNet\Template_Projects\VisualBasic\VB2008"
			!insertmacro sourcefiles  "xlwDotNet\Template_Projects\VisualBasic\VB2008"
			!insertmacro projectfiles "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS9_PRO"
			!insertmacro sourcefiles  "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS9_PRO"
			CreateDirectory "$SMPROGRAMS\XLW\${APP_VER}\xlwDotNet"
			CreateShortCut  "$SMPROGRAMS\XLW\${APP_VER}\xlwDotNet\Extract XLW .NET xll template.lnk" "$INSTDIR\TemplateExtractors\xlwDotNetTemplateExtractor.exe"
		SectionEnd
		
		
		Section "VS2010" VS2010DotNet
			SetOutPath "$INSTDIR\xlwDotNet\lib"
			File "xlwDotNet\lib\xlwDotNet-vc100*.dll"
			File "xlwDotNet\lib\xlwDotNet-vc100*.pdb"
			SetOutPath "$INSTDIR\xlwDotNet\lib\x64"
			File "xlwDotNet\lib\x64\xlwDotNet-vc100*.dll"
			File "xlwDotNet\lib\x64\xlwDotNet-vc100*.pdb"
			!insertmacro DotNetInterfaceGenerator VS10
			!insertmacro DotNetInterfaceGenerator64 VS10
			!insertmacro projectfiles "xlwDotNet\Template_Projects\VS10"
			!insertmacro sourcefiles  "xlwDotNet\Template_Projects\VS10"
		;	!insertmacro projectfiles "xlwDotNet\Template_Projects\VisualBasic\VB2010"
		;	!insertmacro sourcefiles  "xlwDotNet\Template_Projects\VisualBasic\VB2010"
			!insertmacro projectfiles "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS10_PRO"
			!insertmacro sourcefiles  "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS10_PRO"
			CreateDirectory "$SMPROGRAMS\XLW\${APP_VER}\xlwDotNet"
			CreateShortCut  "$SMPROGRAMS\XLW\${APP_VER}\xlwDotNet\Extract XLW .NET xll template.lnk" "$INSTDIR\TemplateExtractors\xlwDotNetTemplateExtractor.exe"
		SectionEnd
		
		
		Section "VS2012" VS2012DotNet
			SetOutPath "$INSTDIR\xlwDotNet\lib"
			File "xlwDotNet\lib\xlwDotNet-vc110*.dll"
			File "xlwDotNet\lib\xlwDotNet-vc110*.pdb"
			SetOutPath "$INSTDIR\xlwDotNet\lib\x64"
			File "xlwDotNet\lib\x64\xlwDotNet-vc110*.dll"
			File "xlwDotNet\lib\x64\xlwDotNet-vc110*.pdb"
			!insertmacro DotNetInterfaceGenerator VS11
			!insertmacro DotNetInterfaceGenerator64 VS11
			!insertmacro projectfiles "xlwDotNet\Template_Projects\VS11"
			!insertmacro sourcefiles  "xlwDotNet\Template_Projects\VS11"
			!insertmacro projectfiles "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS11_PRO"
			!insertmacro sourcefiles  "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS11_PRO"
			CreateDirectory "$SMPROGRAMS\XLW\${APP_VER}\xlwDotNet"
			CreateShortCut  "$SMPROGRAMS\XLW\${APP_VER}\xlwDotNet\Extract XLW .NET xll template.lnk" "$INSTDIR\TemplateExtractors\xlwDotNetTemplateExtractor.exe"
		SectionEnd		

		Section "VS2013" VS2013DotNet
			SetOutPath "$INSTDIR\xlwDotNet\lib"
			File "xlwDotNet\lib\xlwDotNet-vc120*.dll"
			File "xlwDotNet\lib\xlwDotNet-vc120*.pdb"
			SetOutPath "$INSTDIR\xlwDotNet\lib\x64"
			File "xlwDotNet\lib\x64\xlwDotNet-vc120*.dll"
			File "xlwDotNet\lib\x64\xlwDotNet-vc120*.pdb"
			!insertmacro DotNetInterfaceGenerator VS12
			!insertmacro DotNetInterfaceGenerator64 VS12
			!insertmacro projectfiles "xlwDotNet\Template_Projects\VS12"
			!insertmacro sourcefiles  "xlwDotNet\Template_Projects\VS12"
			!insertmacro projectfiles "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS12_PRO"
			!insertmacro sourcefiles  "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS12_PRO"
			CreateDirectory "$SMPROGRAMS\XLW\${APP_VER}\xlwDotNet"
			CreateShortCut  "$SMPROGRAMS\XLW\${APP_VER}\xlwDotNet\Extract XLW .NET xll template.lnk" "$INSTDIR\TemplateExtractors\xlwDotNetTemplateExtractor.exe"
		SectionEnd		

	SectionGroupEnd
	
	
  
	Section "Examples" xlwDotNextExamples
	
		!insertmacro xlwDotNetReadMes
		!insertmacro doDotNetExample "xlwDotNet\Examples\Start Here - Example" 
		!insertmacro doDotNetExample "xlwDotNet\Examples\TypeRegister" 
		!insertmacro doDotNetExample "xlwDotNet\Examples\ReflectionFactory" 
		!insertmacro doDotNetExample "xlwDotNet\Examples\VisualBasic" 
		!insertmacro doDotNetExample "xlwDotNet\UserContrib\NonPassive"
		!insertmacro doDotNetExample "xlwDotNet\UserContrib\Python"
		!insertmacro doDotNetExample "xlwDotNet\UserContrib\RTDExample"
		CreateShortCut  "$SMPROGRAMS\XLW\${APP_VER}\xlwDotNet\Examples.lnk" "$INSTDIR\xlwDotNet\Examples"
		CreateShortCut  "$SMPROGRAMS\XLW\${APP_VER}\xlwDotNet\User Contributed Examples.lnk" "$INSTDIR\xlwDotNet\UserContrib"
		
	SectionEnd
	
	; vanilla xlw sources
	SectionGroup "Source" DotNetSource

		Section "VS2005" VS2005DotNet_SRC
			!insertmacro DotNetbuildfiles "VS8"
			!insertmacro DotNetHeaders
			!insertmacro dotNetInterfaceGenSource
			!insertmacro projectfiles "xlwDotNet\Template_Projects\VS8"
			!insertmacro sourcefiles  "xlwDotNet\Template_Projects\VS8"
			!insertmacro projectfiles "xlwDotNet\Template_Projects\VisualBasic\VB2005"
			!insertmacro sourcefiles  "xlwDotNet\Template_Projects\VisualBasic\VB2005"
			${If} VS2005PRO_CSharp_INST != ""  
				!insertmacro projectfiles "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS8_PRO"
				!insertmacro sourcefiles  "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS8_PRO"
			${EndIf}
		SectionEnd
		
		Section "VS2008" VS2008DotNet_SRC
			!insertmacro DotNetbuildfiles "VS9"
			!insertmacro DotNetHeaders
			!insertmacro dotNetInterfaceGenSource
			!insertmacro projectfiles "xlwDotNet\Template_Projects\VS9"
			!insertmacro sourcefiles  "xlwDotNet\Template_Projects\VS9"
			!insertmacro projectfiles "xlwDotNet\Template_Projects\VisualBasic\VB2008"
			!insertmacro sourcefiles  "xlwDotNet\Template_Projects\VisualBasic\VB2008"
			${If} VS2008PRO_CSharp_INST != ""  
				!insertmacro projectfiles "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS9_PRO"
				!insertmacro sourcefiles  "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS9_PRO"
			${EndIf}
		SectionEnd
		
		Section "VS2010" VS2010DotNet_SRC
			!insertmacro DotNetbuildfiles_VS10 "VS10"
			!insertmacro DotNetHeaders
			!insertmacro dotNetInterfaceGenSource
			!insertmacro projectfiles "xlwDotNet\Template_Projects\VS10"
			!insertmacro sourcefiles  "xlwDotNet\Template_Projects\VS10"
		;	!insertmacro projectfiles "xlwDotNet\Template_Projects\VisualBasic\VB2010"
		;	!insertmacro sourcefiles  "xlwDotNet\Template_Projects\VisualBasic\VB2010"
			${If} VS2010PRO_CSharp_INST != ""  
				!insertmacro projectfiles "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS10_PRO"
				!insertmacro sourcefiles  "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS10_PRO"
			${EndIf}
		SectionEnd
		
		
		Section "VS2012" VS2012DotNet_SRC
			!insertmacro DotNetbuildfiles_VS10 "VS11"
			!insertmacro DotNetHeaders
			!insertmacro dotNetInterfaceGenSource
			!insertmacro projectfiles "xlwDotNet\Template_Projects\VS11"
			!insertmacro sourcefiles  "xlwDotNet\Template_Projects\VS11"
			${If} VS2012PRO_CSharp_INST != ""  
				!insertmacro projectfiles "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS11_PRO"
				!insertmacro sourcefiles  "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS11_PRO"
			${EndIf}
		SectionEnd
		
		Section "VS2013" VS2013DotNet_SRC
			!insertmacro DotNetbuildfiles_VS10 "VS12"
			!insertmacro DotNetHeaders
			!insertmacro dotNetInterfaceGenSource
			!insertmacro projectfiles "xlwDotNet\Template_Projects\VS12"
			!insertmacro sourcefiles  "xlwDotNet\Template_Projects\VS12"
			${If} VS2012PRO_CSharp_INST != ""  
				!insertmacro projectfiles "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS12_PRO"
				!insertmacro sourcefiles  "xlwDotNet\Template_Projects\Hybrid_Cpp_CSharp_XLLs\VS12_PRO"
			${EndIf}
		SectionEnd

	SectionGroupEnd
SubSectionEnd



;----------------------------------------------------------------------------------------------------------------------
;----------------------------------------------------------------------------------------------------------------------
;Section Descriptions

LangString DESC_Libraries ${LANG_ENGLISH} "The static xlw libraries & Tools."

LangString DESC_VS2003 ${LANG_ENGLISH} "VS2003  xll C++ build enviroment for Visual Studio 2003 (VS7.1)."
LangString DESC_VS2005 ${LANG_ENGLISH} "VS2005  xll C++ build enviroment for Visual Studio 2005 (VS8)."
LangString DESC_VS2008 ${LANG_ENGLISH} "VS2008  xll C++ build enviroment for Visual Studio 2008 (VS9)."
LangString DESC_VS2010 ${LANG_ENGLISH} "VS2010  xll C++ build enviroment for Visual Studio 2010 (VS10)."
LangString DESC_VS2012 ${LANG_ENGLISH} "VS2012  xll C++ build enviroment for Visual Studio 2012 (VS11)."
LangString DESC_VS2013 ${LANG_ENGLISH} "VS2013  xll C++ build enviroment for Visual Studio 2013 (VS12)."
LangString DESC_CODEBLOCKS ${LANG_ENGLISH} "Code::Blocks xll C++ build enviroment Code::Blocks ( MinGW only )."
LangString DESC_GCCMAKE ${LANG_ENGLISH} "gcc/make xll C++ build enviroment with support of GNU-MAKE. This uses makefiles"

LangString DESC_Source ${LANG_ENGLISH} "You can install the source code for the xlw libraries including all appropriates project files."

LangString DESC_xlwExamples ${LANG_ENGLISH} "xlw Examples"

LangString DESC_VS2003_SRC ${LANG_ENGLISH} "Source code and Visual Studio 2003 (VS7.1) project files for building the xlw libraries & Tools."
LangString DESC_VS2005_SRC ${LANG_ENGLISH} "Source code and Visual Studio 2005 (VS8) project files for building the xlw libraries & Tools.."
LangString DESC_VS2008_SRC ${LANG_ENGLISH} "Source code and Visual Studio 2008 (VS9) project files for building the xlw libraries & Tools.."
LangString DESC_VS2010_SRC ${LANG_ENGLISH} "Source code and Visual Studio 2010 (VS10) project files for building the xlw libraries & Tools.."
LangString DESC_VS2012_SRC ${LANG_ENGLISH} "Source code and Visual Studio 2012 (VS11) project files for building the xlw libraries & Tools.."
LangString DESC_VS2013_SRC ${LANG_ENGLISH} "Source code and Visual Studio 2013 (VS12) project files for building the xlw libraries & Tools.."

LangString DESC_CODEBLOCKS_SRC ${LANG_ENGLISH} "Source code and Code::Blocks  project files for building the xlw libraries & Tools."
LangString DESC_GCCMAKE_SRC ${LANG_ENGLISH} "Source code and and gnu-make makefiles for building the xlw libraries & Tools."

LangString DESC_xlwDotNetLibraries ${LANG_ENGLISH} "The xlwDotNet .NET Assemblies & Tools. xlls reference these assemblies when they are built. The Assemblies are built for CLR 2 supporting .NET Frameworks 2.0, 3.0 & 3.5 "

LangString DESC_VS2005DotNet ${LANG_ENGLISH} "xlwDotNet .NET Assemblies  & Tools to build for xlls with Visual Studio 2005 (VS8)"
LangString DESC_VS2008DotNet ${LANG_ENGLISH} "xlwDotNet .NET Assemblies  & Tools to build for xlls with Visual Studio 2008 (VS9)"
LangString DESC_VS2010DotNet ${LANG_ENGLISH} "xlwDotNet .NET Assemblies  & Tools to build for xlls with Visual Studio 2010 (VS10)"
LangString DESC_VS2012DotNet ${LANG_ENGLISH} "xlwDotNet .NET Assemblies  & Tools to build for xlls with Visual Studio 2012 (VS11)"
LangString DESC_VS2013DotNet ${LANG_ENGLISH} "xlwDotNet .NET Assemblies  & Tools to build for xlls with Visual Studio 2013 (VS12)"


LangString DESC_DotNetSource ${LANG_ENGLISH} "You can install the source code for the xlwDotNet libraries & Tools including all appropriates project files."

LangString DESC_VS2005DotNet_SRC ${LANG_ENGLISH} "Source code and Visual Studio 2005 (VS8) project files for building the xlwDotNet Assemblies & Tools."
LangString DESC_VS2008DotNet_SRC ${LANG_ENGLISH} "Source code and Visual Studio 2008 (VS9) project files for building the xlwDotNet Assemblies & Tools."
LangString DESC_VS2010DotNet_SRC ${LANG_ENGLISH} "Source code and Visual Studio 2010 (VS10) project files for building the xlwDotNet Assemblies & Tools."
LangString DESC_VS2012DotNet_SRC ${LANG_ENGLISH} "Source code and Visual Studio 2012 (VS11) project files for building the xlwDotNet Assemblies & Tools."
LangString DESC_VS2013DotNet_SRC ${LANG_ENGLISH} "Source code and Visual Studio 2013 (VS12) project files for building the xlwDotNet Assemblies & Tools."



  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
	
	!insertmacro MUI_DESCRIPTION_TEXT ${Libraries} $(DESC_Libraries)
  
    !insertmacro MUI_DESCRIPTION_TEXT ${VS2003} $(DESC_VS2003)
    !insertmacro MUI_DESCRIPTION_TEXT ${VS2005} $(DESC_VS2005)
    !insertmacro MUI_DESCRIPTION_TEXT ${VS2008} $(DESC_VS2008)
	!insertmacro MUI_DESCRIPTION_TEXT ${VS2010} $(DESC_VS2010)
	!insertmacro MUI_DESCRIPTION_TEXT ${VS2012} $(DESC_VS2012)
	!insertmacro MUI_DESCRIPTION_TEXT ${VS2013} $(DESC_VS2013)
    !insertmacro MUI_DESCRIPTION_TEXT ${CODEBLOCKS} $(DESC_CODEBLOCKS)
    !insertmacro MUI_DESCRIPTION_TEXT ${GCCMAKE} $(DESC_GCCMAKE)
	
	!insertmacro MUI_DESCRIPTION_TEXT ${Source} $(DESC_Source)
	
	!insertmacro MUI_DESCRIPTION_TEXT  ${xlwExamples} $(DESC_xlwExamples)
	
	
	!insertmacro MUI_DESCRIPTION_TEXT ${VS2003_SRC} $(DESC_VS2003_SRC)
    !insertmacro MUI_DESCRIPTION_TEXT ${VS2005_SRC} $(DESC_VS2005_SRC)
    !insertmacro MUI_DESCRIPTION_TEXT ${VS2008_SRC} $(DESC_VS2008_SRC)
	!insertmacro MUI_DESCRIPTION_TEXT ${VS2010_SRC} $(DESC_VS2010_SRC)
    !insertmacro MUI_DESCRIPTION_TEXT ${VS2012_SRC} $(DESC_VS2012_SRC)
    !insertmacro MUI_DESCRIPTION_TEXT ${VS2013_SRC} $(DESC_VS2013_SRC)
    !insertmacro MUI_DESCRIPTION_TEXT ${CODEBLOCKS_SRC} $(DESC_CODEBLOCKS_SRC)
    !insertmacro MUI_DESCRIPTION_TEXT ${GCCMAKE_SRC} $(DESC_GCCMAKE_SRC)
	
	!insertmacro MUI_DESCRIPTION_TEXT ${xlwDotNetLibraries} $(DESC_xlwDotNetLibraries)
	
	!insertmacro MUI_DESCRIPTION_TEXT ${VS2005DotNet} $(DESC_VS2005DotNet)
    !insertmacro MUI_DESCRIPTION_TEXT ${VS2008DotNet} $(DESC_VS2008DotNet)
    !insertmacro MUI_DESCRIPTION_TEXT ${VS2010DotNet} $(DESC_VS2010DotNet)
    !insertmacro MUI_DESCRIPTION_TEXT ${VS2012DotNet} $(DESC_VS2012DotNet)
    !insertmacro MUI_DESCRIPTION_TEXT ${VS2013DotNet} $(DESC_VS2013DotNet)
	
	!insertmacro MUI_DESCRIPTION_TEXT ${DotNetSource} $(DESC_DotNetSource)
	
	!insertmacro MUI_DESCRIPTION_TEXT ${VS2005DotNet_SRC} $(DESC_VS2005DotNet_SRC)
    !insertmacro MUI_DESCRIPTION_TEXT ${VS2008DotNet_SRC} $(DESC_VS2008DotNet_SRC)
    !insertmacro MUI_DESCRIPTION_TEXT ${VS2010DotNet_SRC} $(DESC_VS2010DotNet_SRC)
    !insertmacro MUI_DESCRIPTION_TEXT ${VS2012DotNet_SRC} $(DESC_VS2012DotNet_SRC)
    !insertmacro MUI_DESCRIPTION_TEXT ${VS2013DotNet_SRC} $(DESC_VS2013DotNet_SRC)
	
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


Function .onSelChange

	SectionGetFlags ${VS2003} $0 
	StrCmp $0 1 ThereIs1
	SectionGetFlags ${VS2005} $0 
    StrCmp $0 1 ThereIs1
    SectionGetFlags ${VS2008} $0 
    StrCmp $0 1 ThereIs1
	SectionGetFlags ${VS2010} $0 
    StrCmp $0 1 ThereIs1
	SectionGetFlags ${CODEBLOCKS} $0 
    StrCmp $0 1 ThereIs1
	SectionGetFlags ${GCCMAKE} $0 
    StrCmp $0 1 ThereIs1
	
    Call ReloadSections

	Goto End
	
ThereIs1: 
	SectionGetFlags ${VS2005DotNet} $0 
	${If} $0 == "1"
		SectionSetFlags ${VS2005} 1 
	${EndIf}
	SectionGetFlags ${VS2008DotNet} $0 
    ${If} $0 == "1"
		SectionSetFlags ${VS2008} 1 
	${EndIf}
	
	SectionGetFlags ${VS2010DotNet} $0 
    ${If} $0 == "1"
		SectionSetFlags ${VS2010} 1 
	${EndIf}
	
	

	Call SaveSections 
	
End:
FunctionEnd



Function SaveSections 
    SectionGetFlags ${VS2003}  $VS2003_Saved 
	SectionGetFlags ${VS2005}  $VS2005_Saved 
	SectionGetFlags ${VS2008}  $VS2008_Saved 
	SectionGetFlags ${VS2010}  $VS2010_Saved 
	SectionGetFlags ${CODEBLOCKS}  $CODEBLOCKS_Saved 
	SectionGetFlags ${GCCMAKE}  $GCCMAKE_Saved 
FunctionEnd

Function ReloadSections 
    
    SectionSetFlags ${VS2003} $VS2003_Saved 
	SectionSetFlags ${VS2005} $VS2005_Saved 
	SectionSetFlags ${VS2008} $VS2008_Saved 
	SectionSetFlags ${VS2010} $VS2010_Saved 
	SectionSetFlags ${CODEBLOCKS} $CODEBLOCKS_Saved 
	SectionSetFlags ${GCCMAKE} $GCCMAKE_Saved 
FunctionEnd


!macro GetPlatformSDKs
	${NSD_LB_AddString} $ListBox_right " Checking for Platform SDK required for Visual Studio Express 2005" 
	StrCpy $0 0
	StrCpy $2 ""
	loop:
	  EnumRegKey $1 HKLM "SOFTWARE\Microsoft\Microsoft SDKs\Windows" $0
	  StrCmp $1 "" done
	  StrCpy $2 $1
	  IntOp $0 $0 + 1
	  ${NSD_LB_AddString} $ListBox " ... Detected Microsoft Platform SDK $2 " 
	  Goto loop
	done:
	${NSD_LB_AddString} $ListBox "" 
	Push $2
!macroend



Function DevEnvironFinder

	Push $0
	Push $1
	Push $2
	Push $3
	Push $4
	Push $5

	StrCpy $PSDK  ""
    nsDialogs::Create 1018
	Pop $Dialog

	${If} $Dialog == error
		Abort
	${EndIf}

	${NSD_CreateLabel} 0 0 100% 12u "Installed Development Enviroments"
	Pop $Label

	${NSD_CreateListBox} 2u 10u 100% 100% " "
	Pop $ListBox
	
	!insertmacro insertline
	# Visual Studio 2003
 	
	!insertmacro FINDENV HKLM "Software\Microsoft\VisualStudio\7.1\InstalledProducts\VisualC++" "Package"  "Visual Studio 2003 C++"
	Pop $VS2003PRO_CPP_INST

	# Visual Studio 2005
	
	!insertmacro FINDENV HKLM "Software\Microsoft\VisualStudio\8.0\InstalledProducts\Microsoft Visual C++" "Package"  "Visual Studio 2005 C++"
	Pop $VS2005PRO_CPP_INST
	
	!insertmacro FINDENV HKLM "Software\Microsoft\VisualStudio\8.0\InstalledProducts\Microsoft Visual C#" "Package"  "Visual Studio 2005 C#"
	Pop $VS2005PRO_CSharp_INST
	
	!insertmacro FINDENV HKLM "Software\Microsoft\VisualStudio\8.0\InstalledProducts\Microsoft Visual Basic" "Package"  "Visual Studio 2005 VisualBasic"
	Pop $VS2005PRO_VisualBasic_INST
	
	
	# Visual Studio 2008
	
	!insertmacro FINDENV HKLM "Software\Microsoft\VisualStudio\9.0\InstalledProducts\Microsoft Visual C++" "Package"  "Visual Studio 2008 C++"
	Pop $VS2008PRO_CPP_INST
	
	!insertmacro FINDENV HKLM "Software\Microsoft\VisualStudio\9.0\InstalledProducts\Microsoft Visual C#" "Package"  "Visual Studio 2008 C#"
	Pop $VS2008PRO_CSharp_INST
	
	!insertmacro FINDENV HKLM "Software\Microsoft\VisualStudio\9.0\InstalledProducts\Microsoft Visual Basic" "Package"  "Visual Studio 2008 VisualBasic"
	Pop $VS2008PRO_VisualBasic_INST
	

	# Visual Studio 2010
	
	!insertmacro FINDENV HKLM "Software\Microsoft\VisualStudio\10.0\InstalledProducts\Microsoft Visual C++" "Package"  "Visual Studio 2010 C++"
	Pop $VS2010PRO_CPP_INST
	
	!insertmacro FINDENV HKLM "Software\Microsoft\VisualStudio\10.0\InstalledProducts\Microsoft Visual C#" "Package"  "Visual Studio 2010 C#"
	Pop $VS2010PRO_CSharp_INST
	
	!insertmacro FINDENV HKLM "Software\Microsoft\VisualStudio\10.0\InstalledProducts\Microsoft Visual Basic" "Package"  "Visual Studio 2010 VisualBasic"
	Pop $VS2010PRO_VisualBasic_INST
	
	
	# Visual Studio Express 2005 
	
	!insertmacro FINDENV HKLM "Software\Microsoft\VCExpress\8.0\InstalledProducts\Microsoft Visual C++" "Package"  "Visual Studio Express 2005 C++"
	Pop $VS2005EXP_CPP_INST
	
	!insertmacro FINDENV HKLM "Software\Microsoft\VCSExpress\8.0\InstalledProducts\Microsoft Visual C#" "Package"  "Visual Studio Express 2005 C#"
	Pop $VS2005EXP_CSharp_INST
	
	${If} $VS2005EXP_CPP_INST != ""
		!insertmacro GetPlatformSDKs
		Pop $PSDK
	${EndIf}
	
	!insertmacro FINDENV HKLM "SOFTWARE\Microsoft\VBExpress\8.0\InstalledProducts\Microsoft Visual Basic" "Package"  "Visual Studio Express 2005 VisualBasic"
	Pop $VS2005EXP_VisualBasic_INST
	
	# Visual Studio Express 2008 
	
	!insertmacro FINDENV HKLM "Software\Microsoft\VCExpress\9.0\InstalledProducts\Microsoft Visual C++" "Package"  "Visual Studio Express 2008 C++"
	Pop $VS2008EXP_CPP_INST
	
	!insertmacro FINDENV HKLM "Software\Microsoft\VCSExpress\9.0\InstalledProducts\Microsoft Visual C#" "Package"  "Visual Studio Express 2008 C#"
	Pop $VS2008EXP_CSharp_INST
	
	!insertmacro FINDENV HKLM "Software\Microsoft\VBExpress\9.0\InstalledProducts\Microsoft Visual Basic" "Package"  "Visual Studio Express 2008 VisualBasic"
	Pop $VS2008EXP_VisualBasic_INST
	
	
	# Visual Studio Express 2010
	
	!insertmacro FINDENV HKLM "Software\Microsoft\VCExpress\10.0\InstalledProducts\Microsoft Visual C++" "Package"  "Visual Studio Express 2010 C++"
	Pop $VS2010EXP_CPP_INST
	
	!insertmacro FINDENV HKLM "Software\Microsoft\VCSExpress\10.0\InstalledProducts\Microsoft Visual C#" "Package"  "Visual Studio Express 2010 C#"
	Pop $VS2010EXP_CSharp_INST
	
	!insertmacro FINDENV HKLM "Software\Microsoft\VBExpress\10.0\InstalledProducts\Microsoft Visual Basic" "Package"  "Visual Studio Express 2010 VisualBasic"
	Pop $VS2010EXP_VisualBasic_INST
	
	# Visual Studio 2012
	ReadEnvStr $VS2012_INST  "VS110COMNTOOLS"  
	${If} $VS2012_INST != ""
		${NSD_LB_AddString} $ListBox_right "Detected Visual Studio 2012"
		!insertmacro insertline
	${EndIf}

	ReadEnvStr $VS2013_INST  "VS120COMNTOOLS"  
	${If} $VS2013_INST != ""
		${NSD_LB_AddString} $ListBox_right "Detected Visual Studio 2013"
		!insertmacro insertline
	${EndIf}
	
	# gcc
	
	ReadRegStr $CodeBlocks_FRMWK  HKCU "Software\CodeBlocks" "Path"  
	${If} $CodeBlocks_FRMWK != ""
		${NSD_LB_AddString} $ListBox_right "Detected Code::Blocks"
		ReadRegStr $CodeBlocks_INST  HKCU "Software\CodeBlocks\Components"  "MinGW Compiler Suite" 
		${If} $CodeBlocks_INST != ""
			${NSD_LB_AddString} $ListBox_right "...... Detected MinGW Compiler Suite for Code::Blocks"
			${NSD_LB_AddString} $ListBox_right "...... XLW requires MinGW with GCC4.5.2 Your Code::Blocks"
			${NSD_LB_AddString} $ListBox_right "...... may have been installed with an older version of GCC."
			${NSD_LB_AddString} $ListBox_right "...... You should install the required version of MinGW "
            ${NSD_LB_AddString} $ListBox_right "...... and update the settings in your Code::Blocks environment."
		${Else}
			${NSD_LB_AddString} $ListBox_right "     - With Code::Blocks, MinGW/GCC 4.5.2 will be required. You"
			${NSD_LB_AddString} $ListBox_right "       will need to install it if not already installed."
		${EndIf}
		!insertmacro insertline
	${EndIf}
	

	nsDialogs::Show
	
	
	Pop $5
	Pop $4
	Pop $3
	Pop $2
	Pop $1
	Pop $0


FunctionEnd

Function SetUpInfo

	Push $0
	Push $1
	Push $3

	SectionSetFlags ${VS2003_SRC} 0
	SectionSetFlags ${VS2005_SRC} 0
	SectionSetFlags ${VS2008_SRC} 0
	SectionSetFlags ${VS2010_SRC} 0
	SectionSetFlags ${VS2012_SRC} 0
	SectionSetFlags ${VS2013_SRC} 0
	SectionSetFlags ${CODEBLOCKS_SRC} 0
	SectionSetFlags ${GCCMAKE_SRC} 0
	
	SectionSetFlags ${VS2005DotNet_SRC} 0
	SectionSetFlags ${VS2008DotNet_SRC} 0
	SectionSetFlags ${VS2010DotNet_SRC} 0
	SectionSetFlags ${VS2012DotNet_SRC} 0
	SectionSetFlags ${VS2013DotNet_SRC} 0
	
	SectionSetFlags ${VS2003} 0
	SectionSetFlags ${VS2005} 0
	SectionSetFlags ${VS2008} 0
	SectionSetFlags ${VS2010} 0	
	SectionSetFlags ${VS2012} 0	
	SectionSetFlags ${VS2013} 0	
	SectionSetFlags ${CODEBLOCKS} 0
	SectionSetFlags ${GCCMAKE} 0
	
	SectionSetFlags ${VS2005DotNet} 1
	SectionSetFlags ${VS2008DotNet} 1
	SectionSetFlags ${VS2010DotNet} 1
	SectionSetFlags ${VS2012DotNet} 1
	SectionSetFlags ${VS2013DotNet} 1
	
	SectionSetFlags ${xlwExamples} 0
	SectionSetFlags ${sandcastle} 0

	
	${If} $VS2013_INST != "" 
		StrCpy $CPP_DETECTED  "1"
		SectionSetFlags ${VS2013} 1
	${EndIf}
	
	${If} $VS2012_INST != "" 
		StrCpy $CPP_DETECTED  "1"
		SectionSetFlags ${VS2012} 1
	${EndIf}
	
	${If} $VS2010PRO_CPP_INST != ""  
		SectionSetFlags ${VS2010} 1
		StrCpy $CPP_DETECTED  "1"
	${EndIf}

	${If} $VS2010EXP_CPP_INST != ""  
		SectionSetFlags ${VS2010} 1
		StrCpy $CPP_DETECTED  "1"
	${EndIf}
	
	
	${If} $VS2008PRO_CPP_INST != "" 
		StrCpy $CPP_DETECTED  "1"
		SectionSetFlags ${VS2008} 1
	${EndIf}
	
	${If} $VS2008EXP_CPP_INST != ""  
		SectionSetFlags ${VS2008} 1
		StrCpy $CPP_DETECTED  "1"
	${EndIf}
	
	${If} $VS2005PRO_CPP_INST != "" 
		SectionSetFlags ${VS2005} 1
		StrCpy $CPP_DETECTED  "1"
	${EndIf}
	
	${If} $VS2005EXP_CPP_INST != "" 
		SectionSetFlags ${VS2005} 1
		StrCpy $CPP_DETECTED  "1"
	${EndIf}
	
	${If} $VS2003PRO_CPP_INST != "" 
		SectionSetFlags ${VS2003} 1
		StrCpy $CPP_DETECTED  "1"
	${EndIf}
	
	${If} $CodeBlocks_FRMWK != "" 
		SectionSetFlags ${CODEBLOCKS} 1
		StrCpy $CPP_DETECTED  "1"
	${EndIf}
	
	
	${If} $VS2013_INST == "" 
		SectionSetFlags ${VS2013DotNet} 0
	${EndIf}

	${If} $VS2012_INST == "" 
		SectionSetFlags ${VS2012DotNet} 0
	${EndIf}
	
	${If} $VS2010PRO_CSharp_INST == "" 
		${If} $VS2010EXP_CSharp_INST == ""  
			${If} $VS2010PRO_VisualBasic_INST == "" 
				${If} $VS2010EXP_VisualBasic_INST == ""  
					SectionSetFlags ${VS2010DotNet} 0
				${EndIf}
			${EndIf}
		${EndIf}
	${EndIf}
	
	${If} $VS2008PRO_CSharp_INST == "" 
		${If} $VS2008EXP_CSharp_INST == ""  
			${If} $VS2008PRO_VisualBasic_INST == "" 
				${If} $VS2008EXP_VisualBasic_INST == ""  
					SectionSetFlags ${VS2008DotNet} 0
				${EndIf}
			${EndIf}
		${EndIf}
	${EndIf}
	

	${If} $VS2005PRO_CSharp_INST == "" 
		${If} $VS2005EXP_CSharp_INST == ""  
			${If} $VS2005PRO_VisualBasic_INST == "" 
				${If} $VS2005EXP_VisualBasic_INST == ""  
					SectionSetFlags ${VS2005DotNet} 0
				${EndIf}
			${EndIf}
		${EndIf}
	${EndIf}

	${If} $VS2010PRO_CPP_INST == "" 
		${If} $VS2010EXP_CPP_INST == ""  
			SectionSetFlags ${VS2010} 0
			SectionSetFlags ${VS2010DotNet} 0
		${EndIf}
	${EndIf}
	
	${If} $VS2008PRO_CPP_INST == "" 
		${If} $VS2008EXP_CPP_INST == ""  
			SectionSetFlags ${VS2008} 0
			SectionSetFlags ${VS2008DotNet} 0
		${EndIf}
	${EndIf}
	
	${If} $VS2005PRO_CPP_INST == "" 
		${If} $VS2005EXP_CPP_INST == ""  
			SectionSetFlags ${VS2005} 0
			SectionSetFlags ${VS2005DotNet} 0
		${EndIf}
	${EndIf}
	
	${If}  $CPP_DETECTED ==  "1"
		SectionSetFlags ${xlwExamples} 1
		SectionSetFlags ${sandcastle} 1
	${EndIf}
	
	
	StrCpy $PSDK  ""
	
	Call SaveSections 

	Pop $3
	Pop $1
    Pop $0


FunctionEnd 


Function PlatformSDK

	Push $0
	Push $1
	Push $3
	
	StrCpy $1 ""
	Call  SetUpInfo
	
	

	${If} $CPP_DETECTED == ""
			StrCpy $1  "$1$\r$\nA C++ build environment not detected but required for xlw$\r$\n"
			StrCpy $3 "1"
	${EndIf}

	
	${If} $VS2005EXP_CSharp_INST == "1"
		${If} PSDK == ""
		StrCpy $3 "1"
		StrCpy $1 "$1$\r$\nVisual C++ Express 2005 detected but the installer could not detect the"
		StrCpy $1 "$1$\r$\nMicrosoft Platform SDK which is a pre-requisite for xlw under Visual C++ Express 2005$\r$\n"
		${Endif}
	${Endif}
	

	${If} $3 == "1"
		StrCpy $1 "$1$\r$\n$\r$\nTo ABORT installation and install pre-requisites press CANCEL"
		StrCpy $1 "$1$\r$\nTo CONTINUE installation and install  pre-requisites later press NEXT"
		SendMessage $0 ${WM_SETTEXT} 0 "STR:$1"
		
		
		nsDialogs::Create /NOUNLOAD 1018
		Pop $0
		nsDialogs::CreateControl /NOUNLOAD ${__NSD_Text_CLASS} ${DEFAULT_STYLES}|\
		${WS_TABSTOP}|${ES_AUTOHSCROLL}|${ES_MULTILINE}|${WS_VSCROLL} ${__NSD_Text_EXSTYLE} \
		0 13u 100% -13u
		Pop $0
		nsDialogs::Show
	${EndIF}

	
	Pop $3
	Pop $1
    Pop $0


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


















;------------------------------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------------------------------
;Include Modern UI

    !include "MUI2.nsh"
	!include "LogicLib.nsh"
	!include "winmessages.nsh"
	!include "EnvVarUpdate.nsh"
	!include "mingwFileList.nsh"
	
	
	
	Name "MinGW"
    OutFile "xlw-MinGW-Installer.exe"
	
	
     InstallDir C:\GNU

; Request application privileges for Windows Vista
    RequestExecutionLevel admin


    !define MUI_ABORTWARNING
	!define MUI_ICON "xlw_32x32.ico"
    !define MUI_UNICON "xlw_32x32.ico"
	!define MUI_HEADERIMAGE

   	!define MUI_HEADERIMAGE_BITMAP "logo.bmp"
	!define MUI_WELCOMEFINISHPAGE_BITMAP   "header.bmp"
	!define MUI_WELCOMEPAGE_TITLE "xlw Installer for MinGW"
	


;------------------------------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------------------------------
;Pages
    ;!insertmacro MUI_PAGE_WELCOME     
    !insertmacro MUI_PAGE_DIRECTORY
	Page custom GetMirror
    !insertmacro MUI_PAGE_INSTFILES


;------------------------------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------------------------------
;Languages

    !insertmacro MUI_LANGUAGE "English"
	
	!macro SPLIT_STRING INPUT PART
			Push $R0
			Push $R1
			 
			 StrCpy $R0 0
			 StrCmp ${PART} 1 getpart1_loop_${PART}
			 StrCmp ${PART} 2 getpart2_top_${PART}
			Goto error_${PART}
			 
			getpart1_loop_${PART}:
			 IntOp $R0 $R0 - 1
			 StrCpy $R1 ${INPUT} 1 $R0
			  StrCmp $R1 "" error_${PART}
			  StrCmp $R1 "|" 0 getpart1_loop_${PART}
			 
			 IntOp $R0 $R0 + 1
			 StrCpy $R0 ${INPUT} "" $R0
			Goto done_${PART}
			 
			getpart2_top_${PART}:
			 StrLen $R0 ${INPUT}
			getpart2_loop_${PART}:
			 IntOp $R0 $R0 - 1
			 StrCpy $R1 ${INPUT} 1 -$R0
			  StrCmp $R1 "" error_${PART}
			  StrCmp $R1 "|" 0 getpart2_loop_${PART}
			 
			 StrCpy $R0 ${INPUT} -$R0
			Goto done_${PART}
			 
			error_${PART}:
			 StrCpy $R0 error
			 
			done_${PART}:
			 
			Pop $R1
			Exch $R0
!macroend

!macro  Extract DLFile
	   untgz::extract  -d "$INSTDIR\MinGW" "$INSTDIR\Download\$Mirror\${DLFile}"
!macroend

!macro Download DLFile 
	 NSISdl::download "http://downloads.sourceforge.net/mingw/${DLFile}?use_mirror=$Mirror" "$INSTDIR\Download\$Mirror\${DLFile}"
	 DetailPrint "Downloading ${DLFile}"
     Pop $R0 ;Get the return value
       StrCmp $R0 "success" +3
       MessageBox MB_OK "Download failed: $R0"
       Quit

!macroend 


	Var Dialog
	Var Label
	Var DropList
	Var Mirror
	
	
	
	
	
Function GetMirror

	Push $0
	Push $1
	Push $2
	Push $3
	Push $4
	Push $5

    nsDialogs::Create 1018
	Pop $Dialog

	${If} $Dialog == error
		Abort
	${EndIf}

	${NSD_CreateLabel} 50 0 120% 12u "Select the Sourceforge Mirror for download"
	Pop $Label

	StrCpy $Mirror kent
	
	${NSD_CreateDropList} 50 40 80% 10000 ""
    Pop $DropList
	${NSD_OnChange} $DropList onchange

	
	${NSD_CB_AddString} $DropList "ASIA,Australia|optusnet" 
	${NSD_CB_AddString} $DropList "ASIA,Japan|jaist"
	${NSD_CB_AddString} $DropList "ASIA,Taiwan|nchc" 
    ${NSD_CB_AddString} $DropList "EUROPE,Germany|mesh"
	${NSD_CB_AddString} $DropList "EUROPE,Germany|dfn"
	${NSD_CB_AddString} $DropList "EUROPE,Ireland|heanet" 
	${NSD_CB_AddString} $DropList "EUROPE,Italy|garr" 
	${NSD_CB_AddString} $DropList "EUROPE,Netherlands|surfnet"
	${NSD_CB_AddString} $DropList "EUROPE,Switzerland|puzzle"
	${NSD_CB_AddString} $DropList "EUROPE,Switzerland|switch"
	${NSD_CB_AddString} $DropList "EUROPE,UK|kent"
	${NSD_CB_AddString} $DropList "NORTH AMERICA,US|superb-west"
	${NSD_CB_AddString} $DropList "NORTH AMERICA,US|superb-east"
	${NSD_CB_AddString} $DropList "NORTH AMERICA,US|internap"
	${NSD_CB_AddString} $DropList "SOUTH AMERICA,Brazil|ufpr"

	${NSD_CB_SelectString} $DropList "EUROPE,UK|kent"
	nsDialogs::Show
			
	Pop $5
	Pop $4
	Pop $3
	Pop $2
	Pop $1
	Pop $0
	

FunctionEnd


Function onchange 
    Pop $1 

    SendMessage $1 ${CB_GETCURSEL} 0 0 $0 
	
	System::Call 'user32::SendMessage(i r1, i ${CB_GETLBTEXT}, i r0, t .r3) i .r4'
	
	!insertmacro SPLIT_STRING $3 1
	Pop $2   
	;MessageBox MB_OK $2
    StrCpy $Mirror $2
FunctionEnd


	
	; CORE_BIN   CORE_DLL MINGW_MAKE   MINGW_RUNTIME MPFR PTHREADS  GMP   W32API     GPP_BIN   GPP_DLL  BINUTILS
Section 
	   SetOutPath "$INSTDIR\Download\$Mirror"
       !insertmacro Download ${CORE_BIN}
       !insertmacro Download ${CORE_DLL}   
       !insertmacro Download ${MINGW_MAKE}
       !insertmacro Download ${MINGW_RUNTIME_DEV}
	   !insertmacro Download ${MINGW_RUNTIME_DLL}
       !insertmacro Download ${MPFR}
       !insertmacro Download ${PTHREADS} 
       !insertmacro Download ${GMP} 
       !insertmacro Download ${W32API} 	   
       !insertmacro Download ${GPP_BIN} 
       !insertmacro Download ${GPP_DLL} 
       !insertmacro Download ${BINUTILS} 
       !insertmacro Download ${LIBICONV_DEV}
       !insertmacro Download ${LIBICONV_DLL}
       !insertmacro Download ${LIBICONV_BIN}
       !insertmacro Download ${MSYS}
	   
	   	SetOutPath "$INSTDIR\MinGW"
	   !insertmacro Extract ${CORE_BIN}
       !insertmacro Extract ${CORE_DLL}   
       !insertmacro Extract ${MINGW_MAKE}
       !insertmacro Extract ${MINGW_RUNTIME_DLL}
       !insertmacro Extract ${MINGW_RUNTIME_DEV}
       !insertmacro Extract ${MPFR}
       !insertmacro Extract ${PTHREADS} 
       !insertmacro Extract ${GMP} 
       !insertmacro Extract ${W32API} 	   
       !insertmacro Extract ${GPP_BIN} 
       !insertmacro Extract ${GPP_DLL} 
       !insertmacro Extract ${BINUTILS} 
       !insertmacro Extract ${LIBICONV_DLL}
       !insertmacro Extract ${LIBICONV_BIN}
       !insertmacro Extract ${LIBICONV_DEV}
	   
	   SetOutPath "$INSTDIR\MSYS"
       untgz::extract  -d "$INSTDIR\MSYS" "$INSTDIR\Download\$Mirror\${MSYS}"
	   
	   
SectionEnd


Function .OnInstSuccess

   ${EnvVarUpdate} $0 "PATH" "A" "HKLM" "$INSTDIR\MinGW\bin" 
   ${EnvVarUpdate} $0 "PATH" "A" "HKLM" "$INSTDIR\MSYS\bin" 
   ;WriteRegExpandStr HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment" "MINGW" $INSTDIR
   ; make sure windows knows about the change
   SendMessage ${HWND_BROADCAST} ${WM_WININICHANGE} 0 "STR:Environment" /TIMEOUT=5000
   ;MessageBox MB_OK $0

FunctionEnd


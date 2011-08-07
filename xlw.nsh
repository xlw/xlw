!macro XLW_SET_DEFINE SYMBOL CONTENT

  !ifndef "${SYMBOL}"
    !define "${SYMBOL}" "${CONTENT}"
  !endif

!macroend

; uncomment on release version comment for dev builds
!define RELEASE_VERSION 1

var DEV_OR_RELEASE
var RELEASE_SHORT
!ifndef RELEASE_VERSION
!define /date LONG_REL_DATE "%d-%b-%Y"
!define /date SHORT_REL_DATE "%d%b%Y"
!define DEV_OR_RELEASE "- This is a Development Snapshot ${LONG_REL_DATE}"
!define RELEASE_SHORT "${XLW_VERSION}-${SHORT_REL_DATE}"
!else
; uncomment on release version comment for dev builds
!define DEV_OR_RELEASE ""
!define RELEASE_SHORT "${XLW_VERSION}"
!endif

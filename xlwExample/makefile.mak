
#
# makefile for xlwExample.cpp under Borland C++
#
# $Id$

.autodepend
.silent

# Debug version
!ifdef DEBUG
    _D = d
!endif

# Directories
XLW_INCLUDE_DIR = "$(XLW_DIR)"
XLW_LIB_DIR     = "$(XLW_DIR)\lib\Win32\Borland"
BCC_INCLUDE     = $(MAKEDIR)\..\include
BCC_LIBS        = $(MAKEDIR)\..\lib

#Warning W8026 :
#Warning W8027 :
#Warning W8012 :
#Warning W8057 : Parameter 'argc' is never used in function main(int,char * *)

# Options
#    -w-8026 -w-8027 -w-8012 -w-8057 \
CC_OPTS = -vi- \
    -I$(XLW_INCLUDE_DIR) \
    -I$(BCC_INCLUDE)
!ifdef DEBUG
CC_OPTS = $(CC_OPTS) -v -DXLW_DEBUG
!endif

# Primary target:
xlwExample$(_D).xll: xlwExample.cpp
    bcc32 $(CC_OPTS) -L$(XLW_LIB_DIR) -L$(BCC_LIBS) -tWD -oxlwExample$(_D).obj -exll\Win32\Borland\xlwExample$(_D).xll xlwExample.cpp xlw$(_D).lib

# Clean up
clean::
    if exist *.obj   del /q *.obj
    if exist *.tds   del /q *.tds
    if exist *.xll   del /q *.xll

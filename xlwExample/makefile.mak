
#
# makefile for xlwExample.cpp under Borland C++
#

.autodepend
#.silent

# Debug version
!ifdef DEBUG
    _D = d
!endif

# Directories
XLW_INCLUDE_DIR = "$(XLW_DIR)"
XLW_LIB_DIR     = "$(XLW_DIR)\lib"
BCC_INCLUDE     = $(MAKEDIR)\..\include
BCC_LIBS        = $(MAKEDIR)\..\lib

CC_OPTS = -vi- \
    -I$(XLW_INCLUDE_DIR) \
    -I$(BCC_INCLUDE)
!ifdef DEBUG
CC_OPTS = $(CC_OPTS) -v -DXLW_DEBUG
!endif

# Primary target:
xlwExample-bcb$(_D).xll: xlwExample.cpp
    bcc32 $(CC_OPTS) -L$(XLW_LIB_DIR) -L$(BCC_LIBS) -tWD \
        -oxlwExample-bcb$(_D).obj -e"xll\xlwExample-bcb$(_D).xll" \
        xlwExample.cpp xlw$(_D).lib

# Clean up
clean::
    if exist *.obj   del /q *.obj
    if exist *.tds   del /q *.tds
    if exist *.xll   del /q *.xll


# makefile for xlwExample.cpp under Borland C++

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
XLL_DIR         = .\xll

# Object files
EXAMPLE_FILES = \
    "xlwExample.obj$(_mt)$(_D)" \
    "Win32StreamBuf.obj$(_mt)$(_D)" \

# Tools to be used
CC        = bcc32

# Options
CC_OPTS = -vi- -I$(XLW_INCLUDE_DIR) -I$(BCC_INCLUDE)

!ifdef DEBUG
    CC_OPTS = $(CC_OPTS) -v -DXLW_DEBUG
!endif

# Generic rules
.cpp.obj:
    $(CC) -c -q $(CC_OPTS) $<
.cpp.obj$(_mt)$(_D):
    $(CC) -c -q $(CC_OPTS) -o$@ $<

# Primary target:
$(XLL_DIR)\xlwExample-bcb$(_D)-1_2_3.xll: $(XLL_DIR) $(EXAMPLE_FILES)
    if exist $(XLL_DIR)\xlwExample-bcb$(_mt)$(_D)-1_2_3.xll \
         del $(XLL_DIR)\xlwExample-bcb$(_mt)$(_D)-1_2_3.xll
    $(CC) $(CC_OPTS) -L$(XLW_LIB_DIR) -L$(BCC_LIBS) -tWD \
        -e"$(XLL_DIR)\xlwExample-bcb$(_D).xll" \
        $(EXAMPLE_FILES) xlw-bcb-1_2_3$(_D).lib

$(XLL_DIR):
    if not exist .\xll md .\xll

# Clean up
clean::
    if exist *.obj                   del /q *.obj
    if exist $(XLL_DIR)\*-bcb*.tds   del /q $(XLL_DIR)\*-bcb*.tds
    if exist $(XLL_DIR)\*-bcb*.xll   del /q $(XLL_DIR)\*-bcb*.xll

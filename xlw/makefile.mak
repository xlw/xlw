
# $Id $

.autodepend
.silent

# Debug version
!ifdef DEBUG
    _D = d
!endif

# Directories
INCLUDE_DIR    = ..
BCC_INCLUDE    = $(MAKEDIR)\..\include
BCC_LIBS       = $(MAKEDIR)\..\lib
OUTPUT_DIR     = ..\lib\Win32\Borland

# Object files
CORE_OBJS = \
    excel32.obj$(_D) \
    XlfAbstractCmdDesc.obj$(_D) \
    XlfArgDesc.obj$(_D) \
    XlfArgDescList.obj$(_D) \
    XlfCmdDesc.obj$(_D) \
    XlfExcel.obj$(_D) \
    XlfException.obj$(_D) \
    XlfFuncDesc.obj$(_D) \
    XlfOper.obj$(_D) \
    XlfRef.obj$(_D)

# Tools to be used
CC        = bcc32
TLIB      = tlib
!ifdef DEBUG
    MAKE = $(MAKE) -DDEBUG
!endif

# Options
CC_OPTS        = -vi- -q -c -tWM \
    -w-8008 -w-8017 \
    -I$(INCLUDE_DIR) \
    -I$(BCC_INCLUDE) \
    -DXLW_NOIMPORTEXPORT
!ifdef DEBUG
CC_OPTS = $(CC_OPTS) -v -DQL_DEBUG
!endif
!ifdef SAFE
CC_OPTS = $(CC_OPTS) -DSAFE_CHECKS
!endif

TLIB_OPTS    = /P32
!ifdef DEBUG
TLIB_OPTS    = /P64
!endif

# Generic rules
.cpp.obj:
    $(CC) $(CC_OPTS) $<
.cpp.obj_d:
    $(CC) $(CC_OPTS) -o$@ $<

# Primary target:
# XLW library
$(OUTPUT_DIR)\xlw$(_D).lib:: $(CORE_OBJS)
    if exist $(OUTPUT_DIR)\xlw$(_D).lib del $(OUTPUT_DIR)\xlw$(_D).lib
    $(TLIB) $(TLIB_OPTS) $(OUTPUT_DIR)\xlw$(_D).lib /a $(CORE_OBJS)



# Clean up
clean::
    if exist *.obj      del /q *.obj
    if exist *.obj_d    del /q *.obj
    if exist $(OUTPUT_DIR)\*.lib  del /q $(OUTPUT_DIR)\*.lib


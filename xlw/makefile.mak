
.autodepend
#.silent

# Debug version
!ifdef DEBUG
    _D = d
!endif

# Directories
INCLUDE_DIR    = ..
BCC_INCLUDE    = $(MAKEDIR)\..\include
OUTPUT_DIR     = ..\lib

# Object files
CORE_OBJS = \
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
    -I$(INCLUDE_DIR) \
    -I$(BCC_INCLUDE)
!ifdef DEBUG
CC_OPTS = $(CC_OPTS) -v -DXLW_DEBUG
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
.cpp.obj$(_D):
    $(CC) $(CC_OPTS) -o$@ $<

# Primary target:
# XLW library
$(OUTPUT_DIR)\xlw-bcb$(_D)-1_2_3.lib:: $(CORE_OBJS)
    if exist "$(OUTPUT_DIR)\xlw-bcb$(_D)-1_2_3.lib" \
         del "$(OUTPUT_DIR)\xlw-bcb$(_D)-1_2_3.lib"
    $(TLIB) $(TLIB_OPTS) "$(OUTPUT_DIR)\xlw-bcb$(_D)-1_2_3.lib" /a $(CORE_OBJS)



# Clean up
clean::
    if exist *.obj                     del /q *.obj
    if exist *.obj$(_D)                del /q *.obj
    if exist $(OUTPUT_DIR)\*-bcb*.lib  del /q $(OUTPUT_DIR)\*-bcb*.lib

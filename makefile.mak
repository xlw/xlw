
# main makefile for XLW under Borland C++
#
# $Id $


.autodepend
#.silent

# Options
!ifdef DEBUG
    MAKE = $(MAKE) -DDEBUG
!endif

# Primary target:
# xlw library
xlw::
    cd xlw
    $(MAKE)
    cd ..\xlwExample
    $(MAKE) -DXLW_DIR=".."
    cd ..

# the installation directive requires the XLW_DIR environment variable to
# point to the installed version of XLW
inst::
    if exist "$(XLW_DIR)\xlw" rmdir /S /Q "$(XLW_DIR)\xlw"
    xcopy xlw\*.h* "$(XLW_DIR)\xlw" /S /I
    xcopy xlw\*.inl "$(XLW_DIR)\xlw" /S /I

    if exist "$(XLW_DIR)\lib\Win32\VisualStudio" rmdir /S /Q "$(XLW_DIR)\lib\Win32\VisualStudio"
    xcopy lib\Win32\VisualStudio\*.lib "$(XLW_DIR)\lib\Win32\VisualStudio" /S /I
    xcopy lib\Win32\VisualStudio\*.pdb "$(XLW_DIR)\lib\Win32\VisualStudio" /S /I

    if exist "$(XLW_DIR)\lib\Win32\Borland" rmdir /S /Q "$(XLW_DIR)\lib\Win32\Borland"
    xcopy lib\Win32\Borland\*.lib "$(XLW_DIR)\lib\Win32\Borland" /S /I


# Documentation
docs-all:
    cd Docs
    $(MAKE) all
    cd ..

docs-html:
    cd Docs
    $(MAKE) html
    cd ..

docs-winhelp:
    cd Docs
    $(MAKE) winhelp
    cd ..

docs-html-online:
    cd Docs
    $(MAKE) html-online
    cd ..

docs-pdf:
    cd Docs
    $(MAKE) pdf
    cd ..

docs-ps:
    cd Docs
    $(MAKE) ps
    cd ..


# Clean up
clean::
    cd xlw
    $(MAKE) clean
    cd ..\xlwExample
    $(MAKE) clean
    cd ..\Docs
    $(MAKE) clean
    cd ..

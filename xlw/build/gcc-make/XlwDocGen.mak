
PROGRAM = XlwDocGen

ifeq ($(PLATFORM), x64)
INSTALL_DIR = ../../bin64
else
INSTALL_DIR = ../../bin
endif

INCLUDE_DIR = ../../XlwDocGen

SRC_DIR = ../../XlwDocGen
PRGSRC = XlwDocGen.cpp
		 
MAKEDIR = ../../make
include $(MAKEDIR)/make.rules
include $(MAKEDIR)/make.targets

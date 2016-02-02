include ./XLWVERSION.mak

LIBRARY = xlcall32

INSTALL_DIR = ../../bin


LIBTYPE=SHARE

INCLUDE_DIR = ../../include
CXXFLAGS = -fexceptions
LDEXTRAFLAGS=--enable-stdcall-fixup

SRC_DIR = ../../xlcall32stub
DEFFILE=../../xlcall32stub/xlcall32gcc.def
LIBSRC = xlcall32.cpp
	 

MAKEDIR = ../../make
include $(MAKEDIR)/make.rules
include $(MAKEDIR)/make.targets

#Describes the xll 
BUILD=DEBUG
LIBRARY =Template
LIBTYPE=SHARE
LIBPREFIX=
EXT_SHARE=xll

#Describes the Linker details
LIBDIRS = "$(XLW)\xlw\lib"
ifeq ($(BUILD),DEBUG)
LIBS=xlw-gcc-s-gd-4_0_0alpha2
else
LIBS=xlw-gcc-s-4_0_0alpha2
endif 

#Describes the Compiler details
INCLUDE_DIR =source  "$(XLW)\xlw\include"
CXXFLAGS = -DBUILDING_DLL=1  -fexceptions 


#The source
SRC_DIR=source
LIBSRC = source.cpp \
         xlwWrapper.cpp
		
MAKEDIR = "$(XLW)\xlw\make"
include $(MAKEDIR)/make.rules
include $(MAKEDIR)/make.targets
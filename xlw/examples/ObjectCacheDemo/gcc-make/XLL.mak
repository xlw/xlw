#Describes the xll 
BUILD=DEBUG
LIBRARY = ObjectCacheDemo
LIBTYPE=SHARE
LIBPREFIX=
EXT_SHARE=xll

#Describes the Linker details
ifeq ($(PLATFORM), x64)
LIBDIRS = $(XLW)/xlw/lib/x64
else
LIBDIRS = $(XLW)/xlw/lib
endif

ifeq ($(BUILD),DEBUG)
LIBS=xlw-gcc-s-gd-6_0_0f0
else
LIBS=xlw-gcc-s-6_0_0f0
endif 

#Describes the Compiler details
INCLUDE_DIR =../common_source ../Objects $(XLW)/xlw/include
CXXFLAGS = 


#The source
SRC_DIR=../common_source
LIBSRC = source.cpp \
		 DiscountCurve.cpp \
		 xlwWrapper.cpp 
		
MAKEDIR = $(XLW)/xlw/make
include $(MAKEDIR)/make.rules
include $(MAKEDIR)/make.targets
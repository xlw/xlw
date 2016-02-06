#Describes the xll 
LIBRARY = ObjectCacheDemo
LIBTYPE=SHARE
LIBPREFIX=
EXT_SHARE=xll

#Describes the Compiler details
INCLUDE_DIR =../common_source ../Objects
CXXFLAGS = 

#The source
SRC_DIR=../common_source
LIBSRC = source.cpp \
		 DiscountCurve.cpp \
		 xlwWrapper.cpp  \
		 xlwLibrary.cpp
		
MAKEDIR = $(XLW)/xlw/make
include $(MAKEDIR)/make.rules
include $(MAKEDIR)/make.targets
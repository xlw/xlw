#Describes the xll 
LIBRARY = TypeRegDemo
LIBTYPE=SHARE
LIBPREFIX=
EXT_SHARE=xll

#Describes the Compiler details
INCLUDE_DIR =../common_source 
CXXFLAGS = 

#The source
SRC_DIR=../common_source
LIBSRC = Test.cpp \
         type_conversions.cpp \
		 xlwTest.cpp  \
		 xlwLibrary.cpp
		
MAKEDIR = $(XLW)/xlw/make
include $(MAKEDIR)/make.rules
include $(MAKEDIR)/make.targets
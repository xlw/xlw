#Describes the xll 
LIBRARY = ExampleHandwritten
LIBTYPE=SHARE
LIBPREFIX=
EXT_SHARE=xll

#Describes the Compiler details
INCLUDE_DIR =../common_source
CXXFLAGS = 

#The source
SRC_DIR=../common_source
LIBSRC = xlwAsynchExample.cpp \
	xlwCommands.cpp \
	xlwExample.cpp \
	xlwMatrixTest.cpp \
	xlwXlmMacros.cpp \
	xlwLibrary.cpp
  
		
MAKEDIR = $(XLW)/xlw/make
include $(MAKEDIR)/make.rules
include $(MAKEDIR)/make.targets
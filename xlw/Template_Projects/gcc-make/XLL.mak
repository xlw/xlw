#Describes the xll 
LIBRARY =Template
BUILD=DEBUG
LIBTYPE=SHARE
LIBPREFIX=
EXT_SHARE=xll


#Describes the Compiler details
INCLUDE_DIR =source  
CXXFLAGS =      

LIBDIRS =
LIBS = 


#The source
SRC_DIR= source
LIBSRC = source.cpp \
         xlwWrapper.cpp
		

MAKEDIR = $(XLW)/xlw/make
include $(MAKEDIR)/make.rules
include $(MAKEDIR)/make.targets




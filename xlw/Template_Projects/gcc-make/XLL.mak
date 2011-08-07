#Describes the xll 


BUILD=DEBUG
LIBRARY =Template


#Describes the Compiler details
INCLUDE_DIR =source  
CXXFLAGS =      

LIBDIRS =
LIBS = 


#The source
SRC_DIR= source
LIBSRC = source.cpp \
         xlwWrapper.cpp
		

include make/rules.mak



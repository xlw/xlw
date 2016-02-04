#Describes the xll 
LIBRARY = Payoff
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
INCLUDE_DIR =../common_source 
CXXFLAGS = 


#The source
SRC_DIR=../common_source
LIBSRC = PayOff.cpp \
		 PayOffConcrete.cpp \
		 PayOffRegistration.cpp \
		 Test.cpp \
		 xlwTest.cpp  \
		 xlwLibrary.cpp
		
MAKEDIR = $(XLW)/xlw/make
include $(MAKEDIR)/make.rules
include $(MAKEDIR)/make.targets
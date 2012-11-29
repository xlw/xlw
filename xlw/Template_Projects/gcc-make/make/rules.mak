
#	Copyright (C) 2009 Narinder S Claire
#
#	This file is part of XLW, a free-software/open-source C++ wrapper of the
#	Excel C API - http://xlw.sourceforge.net/
#
#	XLW is free software: you can redistribute it and/or modify it under the
#	terms of the XLW license.  You should have received a copy of the
#	license along with this program; if not, please email xlw-users@lists.sf.net
#
#	This program is distributed in the hope that it will be useful, but WITHOUT
#	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
#	FOR A PARTICULAR PURPOSE.  See the license for more details.



ifndef BUILD
export BUILD=DEBUG
endif

ifeq ($(PLATFORM), x64)
BUILD_SUFFIX= _x64
CROSS_PREFIX= x86_64-w64-mingw32-
CCFLAGS64= -m64 -DWIN64
LIB_SUBDIR = /x64
else
BUILD_SUFFIX=
CROSS_PREFIX=
LIB_SUBDIR = 
CCFLAGS64=
endif


LIBLINK=SHARE
LIBTYPE=SHARE

ifndef SRC_DIR
SRC_DIR=.
endif

SEP:=$(strip \)

INSTALL_DLL = $(BUILD)/XLL$(BUILD_SUFFIX)
INSTALL_OBJ = $(INSTALL_DLL)/OBJECTS

########################################################
#	C++ language section.
########################################################



CXX= $(CROSS_PREFIX)g++


CPPFLAGSINC := $(INCLUDE_DIR:%=-I%)

ifeq ($(BUILD),DEBUG)
CPPFLAGS= $(CPPFLAGSINC) $(CCFLAGS64) -g3 -Wall -D_DEBUG
STRIP=
endif 
ifeq ($(BUILD),RELEASE)
CPPFLAGS= $(CPPFLAGSINC) $(CCFLAGS64) -O3 -Wall -DNDEBUG
STRIP=-s
endif 


COMPILE= $(CXX)  $(CXXFLAGS) $(CPPFLAGS) -c

.cpp:
	$(LINK) -o $@ $< $(LDLIBS) -L"$(XLW)/xlw/lib$(LIB_SUBDIR)"
.cpp.o:
	$(COMPILE) -o $@ $< -I"$(XLW)/xlw/include"
	

$(INSTALL_OBJ)/%.o:$(SRC_DIR)/%.cpp
	$(COMPILE)  $(CXXPIC)  $< -o $@  -I"$(XLW)/xlw/include"

########################################################
#	Linker section.
########################################################


ifeq ($(BUILD),DEBUG)
XLWLIBS=-lxlw-gcc-s-gd-5_0_0f0
else
XLWLIBS=-lxlw-gcc-s-5_0_0f0
endif 

ifndef LDLIBS
LDLIBS=
endif 

ifdef LIBDIRS
LDLIBS+=$(LIBDIRS:%=-L%)
endif

ifdef LIBS
LDLIBS+=$(LIBS:%=-l%)
endif

LDFLAGS= $(LDL) $(LDLIBS) $(XLWLIBS)
#############################################################
#############################################################
######### BUILDER ##########################################

BUILD_TARGETS =  directories  install

build :: $(BUILD_TARGETS)

REBUILD_TARGETS = clean  directories  install
rebuild ::$(REBUILD_TARGETS)


install:: $(INSTALL_DLL)/$(LIBPREFIX)$(LIBRARY).xll 
	  
LIBOBJ := $(LIBSRC:%.cpp=$(INSTALL_OBJ)/%.o)
TARGET = $(INSTALL_DLL)/$(LIBPREFIX)$(LIBRARY).xll 


$(TARGET)::$(LIBOBJ)
	@-$(RM) $@	
	$(CXX) -shared $(CXXPIC) $(STRIP) -o  $@ \
   	-Wl,"$(XLW)/xlw/include/xlw/xlw.def" \
        -Wl,-static \
        -static-libgcc \
	$(LIBOBJ) \
   	$(LDFLAGS) -L"$(XLW)/xlw/lib$(LIB_SUBDIR)"



##############################################################
################## GERNERIC Section #########################
##############################################################


directories :: $(BUILD) $(INSTALL_DLL) $(INSTALL_OBJ) 


clean:: clean_target clean_objects 


clean_objects::
	@echo Removing $(notdir $(OBJECTS))
	@$(RM) $(OBJECTS)

clean_target::
	@echo Removing $(notdir $(TARGET))
	@$(RM) $(TARGET)

$(BUILD):
	@echo Creating $@ .....
	@-mkdir  $(subst /,$(SEP)$(SEP),$(BUILD))
		

$(INSTALL_DLL):
	@echo Creating $@ .....
	@-mkdir  $(subst /,$(SEP)$(SEP),$(INSTALL_DLL))

	
$(INSTALL_OBJ):
	@echo Creating $@ .....
	@-mkdir  $(subst /,$(SEP)$(SEP),$(INSTALL_OBJ)) 


	



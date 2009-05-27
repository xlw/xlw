
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

LIBLINK=SHARE
LIBTYPE=SHARE

ifndef SRC_DIR
SRC_DIR=.
endif

SEP:=$(strip \)

INSTALL_DLL = $(BUILD)/XLL
INSTALL_OBJ = $(INSTALL_DLL)/OBJECTS

########################################################
#	C++ language section.
########################################################

CXX= g++


CPPFLAGSINC := $(INCLUDE_DIR:%=-I%)

ifeq ($(BUILD),DEBUG)
CPPFLAGS= $(CPPFLAGSINC)  -g3
endif 
ifeq ($(BUILD),RELEASE)

CPPFLAGS= $(CPPFLAGSINC)  -O3
endif 


COMPILE= $(CXX)  $(CXXFLAGS) $(CPPFLAGS) -DBUILDING_DLL=1  -fexceptions -c

.cpp:
	$(LINK) -o $@ $< $(LDLIBS) -L"$(XLW)/xlw/lib"
.cpp.o:
	$(COMPILE) -o $@ $< -I"$(XLW)/xlw/include"
	

$(INSTALL_OBJ)/%.o:$(SRC_DIR)/%.cpp
	$(COMPILE)  $(CXXPIC)  $< -o $@  -I"$(XLW)/xlw/include"

########################################################
#	Linker section.
########################################################


ifeq ($(BUILD),DEBUG)
XLWLIBS=-lxlw-gcc-s-gd-4_0_0alpha7
else
XLWLIBS=-lxlw-gcc-s-4_0_0alpha7
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
	$(CXX) -fPIC -shared  -o  $@ \
    -Wl,--out-implib=$(INSTALL_DLL)/$(LIBPREFIX)$(LIBRARY).lib \
   	-Wl,--export-all-symbols \
   	-Wl,--enable-auto-import \
	 $(LIBOBJ)\
   	-Wl,--no-whole-archive $(LDFLAGS) -L"$(XLW)/xlw/lib" $(LDFLAGS)



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


	



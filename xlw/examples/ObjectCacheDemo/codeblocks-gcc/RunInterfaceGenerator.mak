
ifndef BUILD
BUILD=Debug
endif

ifeq ($(PLATFORM), x64)
TOOLS_DIR = $(XLW)/xlw/bin64
else
TOOLS_DIR = $(XLW)/xlw/bin
endif

.PHONY : clean

all: ../common_source/xlwWrapper.cpp

../common_source/xlwWrapper.cpp : ../common_source/cppinterface.h
		"$(TOOLS_DIR)/InterfaceGenerator" ../common_source/cppinterface.h ../common_source/xlwWrapper.cpp
		@echo OK > build_$(BUILD)

clean :
		@$(RM) ../common_source/xlwWrapper.cpp
		@$(RM) build_$(BUILD)

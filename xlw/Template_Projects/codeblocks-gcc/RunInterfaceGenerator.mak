
ifndef BUILD
BUILD=DEBUG
endif

ifeq ($(PLATFORM), x64)
TOOLS_DIR = $(XLW)/xlw/bin64
else
TOOLS_DIR = $(XLW)/xlw/bin
endif

.PHONY : clean


all: source/xlwWrapper.cpp

source/xlwWrapper.cpp : source/cppinterface.h
		"$(TOOLS_DIR)/InterfaceGenerator" source/cppinterface.h source/xlwWrapper.cpp
		@echo OK > build_$(BUILD)

clean :
		@$(RM) source/xlwWrapper.cpp
		@$(RM) build_$(BUILD)


ifndef BUILD
BUILD=DEBUG
endif

TOOLS_DIR = $(XLW)/xlw/bin

.PHONY : clean


all: source/xlwWrapper.cpp

source/xlwWrapper.cpp : source/cppinterface.h
		"$(TOOLS_DIR)/InterfaceGenerator" source/cppinterface.h source/xlwWrapper.cpp
		@echo OK > build_$(BUILD)

clean :
		@$(RM) source/xlwWrapper.cpp
		@$(RM) build_$(BUILD)


ifndef BUILD
BUILD=Debug
endif

TOOLS_DIR = $(XLW)/xlw/bin

.PHONY : clean

all: ../common_source/xlwWrapper.cpp

../common_source/xlwWrapper.cpp : ../common_source/cppinterface.h
		"$(TOOLS_DIR)/InterfaceGenerator" ../common_source/cppinterface.h ../common_source/xlwWrapper.cpp
		@echo OK > build_$(BUILD)

clean :
		@$(RM) ../common_source/xlwWrapper.cpp
		@$(RM) build_$(BUILD)

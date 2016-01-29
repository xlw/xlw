
ifndef BUILD
BUILD=Debug
endif

ifeq ($(PLATFORM), x64)
TOOLS_DIR = $(XLW)/xlw/bin64
else
TOOLS_DIR = $(XLW)/xlw/bin
endif

.PHONY : clean

all: ../common_source/xlwTest.cpp

../common_source/xlwTest.cpp : ../common_source/Test.h
		"$(TOOLS_DIR)/InterfaceGenerator" ../common_source/Test.h ../common_source/xlwTest.cpp
		@echo OK > build_$(BUILD)

clean :
		@$(RM) ../common_source/xlwTest.cpp
		@$(RM) build_$(BUILD)

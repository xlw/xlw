
ifndef BUILD
BUILD=Debug
endif

TOOLS_DIR = $(XLW)/xlw/bin

.PHONY : clean


all: ../common_source/xlwTest.cpp

../common_source/xlwTest.cpp : ../common_source/Test.h
		"$(TOOLS_DIR)/InterfaceGenerator" ../common_source/Test.h ../common_source/xlwTest.cpp
		@echo OK > build_$(BUILD)

clean :
		@$(RM) ../common_source/xlwTest.cpp
		@$(RM) build_$(BUILD)

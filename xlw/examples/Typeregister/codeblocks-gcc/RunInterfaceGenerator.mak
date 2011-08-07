
ifndef BUILD
BUILD=Debug
endif

.PHONY : clean


all: ../common_source/xlwTest.cpp

../common_source/xlwTest.cpp : ../common_source/Test.h
		../../../build/codeblocks-gcc/bin/$(BUILD)/InterfaceGenerator.exe ../common_source/Test.h ../common_source/xlwTest.cpp
		@echo OK > build_$(BUILD)

clean :
		@$(RM) ../common_source/xlwTest.cpp
		@$(RM) build_$(BUILD)

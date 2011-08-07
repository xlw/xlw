
ifndef BUILD
BUILD=Debug
endif

.PHONY : clean


all: ../common_source/xlwWrapper.cpp

../common_source/xlwWrapper.cpp : ../common_source/cppinterface.h
		../../../build/codeblocks-gcc/bin/$(BUILD)/InterfaceGenerator.exe ../common_source/cppinterface.h ../common_source/xlwWrapper.cpp
		@echo OK > build_$(BUILD)

clean :
		@$(RM) ../common_source/xlwWrapper.cpp
		@$(RM) build_$(BUILD)

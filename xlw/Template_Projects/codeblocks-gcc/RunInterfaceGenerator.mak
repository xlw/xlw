
ifndef BUILD
BUILD=DEBUG
endif

.PHONY : clean


all: source/xlwWrapper.cpp

source/xlwWrapper.cpp : source/cppinterface.h
		"$(subst $(strip \),/,$(XLW))/xlw/build/codeblocks-gcc/bin/$(BUILD)/InterfaceGenerator.exe" source/cppinterface.h source/xlwWrapper.cpp
		@echo OK > build_$(BUILD)

clean :
		@$(RM) source/xlwWrapper.cpp
		@$(RM) build_$(BUILD)

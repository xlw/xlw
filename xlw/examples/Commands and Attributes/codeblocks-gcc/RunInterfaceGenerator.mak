
ifndef BUILD
BUILD=Debug
endif

.PHONY : clean


all: Commands Attributes

clean:
	@echo Removing ../common_source/xlwAttributes.cpp
	@echo Removing ../common_source/xlwCommands.cpp
	@$(RM) ../common_source/xlwAttributes.cpp
	@$(RM) ../common_source/xlwCommands.cpp
	@$(RM) build_$(BUILD)	
	
Commands :../common_source/xlwCommands.cpp 
Attributes :../common_source/xlwAttributes.cpp 

../common_source/xlwCommands.cpp:  ../common_source/Commands.h
	../../../build/gcc-make/$(BUILD)/BIN/InterfaceGenerator  ../common_source/Commands.h ../common_source/xlwCommands.cpp
	@echo OK > build_$(BUILD)
		
../common_source/xlwAttributes.cpp:  ../common_source/Attributes.h
	../../../build/gcc-make/$(BUILD)/BIN/InterfaceGenerator  ../common_source/Attributes.h ../common_source/xlwAttributes.cpp
	@echo OK > build_$(BUILD)
	
	
rebuild: clean all


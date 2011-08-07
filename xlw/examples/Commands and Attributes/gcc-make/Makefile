BUILD=DEBUG
PLATFORM=WIN32

all: Commands Attributes
	$(MAKE) -f ./XLL.mak BUILD=$(BUILD) PLATFORM=$(PLATFORM)
	
clean:
	$(MAKE) -f ./XLL.mak BUILD=$(BUILD) PLATFORM=$(PLATFORM) clean
	@echo Removing ../common_source/xlwAttributes.cpp
	@echo Removing ../common_source/xlwCommands.cpp
	@$(RM) ../common_source/xlwAttributes.cpp
	@$(RM) ../common_source/xlwCommands.cpp
	
	
Commands :../common_source/xlwCommands.cpp 
Attributes :../common_source/xlwAttributes.cpp 

../common_source/xlwCommands.cpp:  ../common_source/Commands.h
	../../../build/gcc-make/$(BUILD)/BIN/InterfaceGenerator  ../common_source/Commands.h ../common_source/xlwCommands.cpp
		
../common_source/xlwAttributes.cpp:  ../common_source/Attributes.h
	../../../build/gcc-make/$(BUILD)/BIN/InterfaceGenerator  ../common_source/Attributes.h ../common_source/xlwAttributes.cpp
	
rebuild: clean all
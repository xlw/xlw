BUILD=RELEASE
PLATFORM=WIN32

all:
ifeq ($(PLATFORM), WIN32)
	$(MAKE) -f InterfaceGenerator.mak BUILD=$(BUILD) PLATFORM=$(PLATFORM)
	$(MAKE) -f xlcall32stub.mak BUILD=$(BUILD) PLATFORM=$(PLATFORM)
	$(MAKE) -f XlwDocGen.mak BUILD=$(BUILD) PLATFORM=$(PLATFORM)
endif
	
clean:
ifeq ($(PLATFORM), WIN32)
	$(MAKE) -f InterfaceGenerator.mak  BUILD=$(BUILD) PLATFORM=$(PLATFORM) clean
	$(MAKE) -f xlcall32stub.mak BUILD=$(BUILD) PLATFORM=$(PLATFORM) clean
	$(MAKE) -f XlwDocGen.mak BUILD=$(BUILD) PLATFORM=$(PLATFORM) clean
endif
	
rebuild: clean all


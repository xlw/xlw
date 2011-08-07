BUILD=DEBUG
PLATFORM=WIN32

all:
	$(MAKE) -f InterfaceGenerator.mak BUILD=$(BUILD) PLATFORM=$(PLATFORM)
	$(MAKE) -f XLW.mak BUILD=$(BUILD) PLATFORM=$(PLATFORM)
	$(MAKE) -f xlcall32stub.mak BUILD=$(BUILD) PLATFORM=$(PLATFORM)
	$(MAKE) -f XlwDocGen.mak BUILD=$(BUILD) PLATFORM=$(PLATFORM)
	
clean:
	$(MAKE) -f InterfaceGenerator.mak  BUILD=$(BUILD) PLATFORM=$(PLATFORM) clean
	$(MAKE) -f XLW.mak BUILD=$(BUILD)  PLATFORM=$(PLATFORM) clean
	$(MAKE) -f xlcall32stub.mak BUILD=$(BUILD) PLATFORM=$(PLATFORM) clean
	$(MAKE) -f XlwDocGen.mak BUILD=$(BUILD) PLATFORM=$(PLATFORM) clean
	
rebuild: clean all


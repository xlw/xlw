
ifndef BUILD
BUILD=DEBUG
endif

ifeq ($(BUILD),DEBUG)
CXXFLAGS=-g3
GD=-gd
else
CXXFLAGS=-O3
GD=
endif

all:
	$(MAKE) -f InterfaceGenerator.mak   BUILD=$(BUILD)
	$(MAKE) -f XLW.mak BUILD=$(BUILD)
	
clean:
	$(MAKE) -f InterfaceGenerator.mak  BUILD=$(BUILD) clean
	$(MAKE) -f XLW.mak BUILD=$(BUILD) clean
	
rebuild: clean all


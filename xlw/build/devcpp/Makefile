
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

all:XlOpenClose
	$(MAKE) -f InterfaceGenerator.mak   BUILD=$(BUILD)
	$(MAKE) -f XLW.mak BUILD=$(BUILD)
	
clean:
	$(MAKE) -f InterfaceGenerator.mak  BUILD=$(BUILD) clean
	$(MAKE) -f XLW.mak BUILD=$(BUILD) clean
	@$(RM) ../../lib/XlOpenClose$(GD).o
	
rebuild: clean all

XlOpenClose: ../../src/XlOpenClose.cpp
	g++ -c ../../src/XlOpenClose.cpp $(CXXFLAGS) -I../../include -o  ../../lib/XlOpenClose$(GD).o
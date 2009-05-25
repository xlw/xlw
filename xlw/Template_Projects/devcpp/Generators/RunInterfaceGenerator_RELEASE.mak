
XLWNEW=$(XLW)

all-before : 
		"$(subst "\","/",$(XLWNEW))/xlw/build/devcpp/RELEASE/BIN/InterfaceGenerator.exe"  source/cppinterface.h source/xlwWrapper.cpp
		$(CPP) -c source/xlwWrapper.cpp $(CXXFLAGS)  -o ./Release/Objects/xlwWrapper.o 
		
		
		

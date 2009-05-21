


all-before : 
		"$(XLW)\xlw\build\devcpp\DEBUG\BIN\InterfaceGenerator.exe"  source\cppinterface.h source\xlwWrapper.cpp
		$(CPP) -c source\xlwWrapper.cpp $(CXXFLAGS)  -o .\Debug\Objects\xlwWrapper.o 

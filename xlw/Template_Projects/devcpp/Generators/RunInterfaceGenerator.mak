


all-before : 
		$(XLW)\xlw\build\devcpp\DEBUG\BIN\InterfaceGenerator  source\cppinterface.h source\xlwWrapper.cpp
		$(CPP) -c source\xlwWrapper.cpp $(CXXFLAGS)  -o .\Debug\Objects\xlwWrapper.o 
		$(CPP) -c $(XLW)\xlw\src\XlOpenClose.cpp $(CXXFLAGS)  -o .\Debug\Objects\XlOpenClose.o 



all-before : 
		$(XLW)\xlw\build\devcpp\RELEASE\BIN\InterfaceGenerator  source\cppinterface.h source\xlwWrapper.cpp
		$(CPP) -c source\xlwWrapper.cpp $(CXXFLAGS)  -o .\Release\Objects\xlwWrapper.o 
		$(CPP) -c $(XLW)\xlw\src\XlOpenClose.cpp $(CXXFLAGS)  -o .\Release\Objects\XlOpenClose.o 
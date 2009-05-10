

all-before : ../common_source/xlwTest.cpp 

../common_source/xlwTest.cpp: ../common_source/Test.h
							../../../build/devcpp/DEBUG/BIN/InterfaceGenerator  ../common_source/Test.h ../common_source/xlwTest.cpp
							

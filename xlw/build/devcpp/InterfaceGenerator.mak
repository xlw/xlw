



PROGRAM = InterfaceGenerator

INCLUDE_DIR = ../../InterfaceGenerator


SRC_DIR = ../../InterfaceGenerator
PRGSRC = FunctionModel.cpp \
         FunctionType.cpp \
         Functionizer.cpp \
         IncludeRegister.cpp \
         Outputter.cpp \
         ParserData.cpp \
         Strip.cpp \
         Tokenizer.cpp \
         TypeRegister.cpp \
         TypeRegistrations.cpp \
         main.cpp \

		 
MAKEDIR = ../../make
include $(MAKEDIR)/make.rules
include $(MAKEDIR)/make.targets

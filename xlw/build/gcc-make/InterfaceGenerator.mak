PROGRAM = InterfaceGenerator

ifeq ($(PLATFORM), x64)
INSTALL_DIR = ../../bin64
else
INSTALL_DIR = ../../bin
endif

INCLUDE_DIR = ../../InterfaceGenerator

SRC_DIR = ../../InterfaceGenerator
PRGSRC = FunctionModel.cpp \
         Functionizer.cpp \
         Outputter.cpp \
         ParserData.cpp \
         Strip.cpp \
         Tokenizer.cpp \
         TypeRegister.cpp \
         TypeRegistrations.cpp \
		 ManagedOutputter.cpp\
		 OutputterHelper.cpp\
         main.cpp \

		 
MAKEDIR = ../../make
include $(MAKEDIR)/make.rules
include $(MAKEDIR)/make.targets

include .\XLWVERSION.mak


ifeq ($(BUILD),DEBUG)
LIBRARY = xlw-devcpp-gcc-s-gd-$(XLWVERSION)
endif
ifeq ($(BUILD),RELEASE)
LIBRARY = xlw-devcpp-gcc-s-$(XLWVERSION)
endif


INSTALL_DIR = ..\..\lib



LIBTYPE=STATIC



INCLUDE_DIR = ..\..\include
CXXFLAGS = -DBUILDING_DLL=1  -fexceptions


SRC_DIR = ..\..\src
LIBSRC = ArgList.cpp \
         CellMatrix.cpp \
         Dispatcher.cpp \
         DoubleOrNothing.cpp \
         FileConverter.cpp \
         MJmatrices.cpp \
         MyContainers.cpp \
         Win32StreamBuf.cpp \
         XlFunctionRegistration.cpp \
         XlfAbstractCmdDesc.cpp \
         XlfArgDesc.cpp \
         XlfArgDescList.cpp \
         XlfCmdDesc.cpp \
         XlfExcel.cpp \
         XlfException.cpp \
         XlfFuncDesc.cpp \
         XlfOper.cpp \
         XlfOper12.cpp \
         XlfOper4.cpp \
         XlfOperImpl.cpp \
         XlfOperImpl12.cpp \
         XlfOperImpl4.cpp \
         XlfRef.cpp \
         XlfStr.cpp \
         xlarray.cpp \
         xlcall.cpp
         #XlOpenClose.cpp   This gets included in the user code

MAKEDIR = ..\..\make
include $(MAKEDIR)/make.rules
include $(MAKEDIR)/make.targets

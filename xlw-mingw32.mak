# Makefile - xlw.dsp

ifndef CFG
CFG=xlw - Win32 Debug
endif
CC=i386-mingw32msvc-gcc
CFLAGS=
CXX=i386-mingw32msvc-g++
CXXFLAGS=$(CFLAGS)
RC=i386-mingw32msvc-windres -O COFF
ifeq "$(CFG)"  "xlw - Win32 Release"
CFLAGS+=-W -fexceptions -O2 -I. -DNDEBUG -DWIN32 -D_MBCS -D_LIB
AR=i386-mingw32msvc-ar
TARGET=lib/Win32/Mingw32/libxlw.a
ARFLAGS=rus
else
ifeq "$(CFG)"  "xlw - Win32 Debug"
CFLAGS+=-W -fexceptions -g -O0 -I. -DXLW_DEBUG -D_DEBUG -DWIN32 -D_MBCS -D_LIB
AR=i386-mingw32msvc-ar
TARGET=lib/Win32/Mingw32/libxlwd.a
ARFLAGS=rus
else
ifeq "$(CFG)"  "xlw - Win32 OnTheEdgeDebug"
CFLAGS+=-W -fexceptions -g -O0 -I. -DXLW_DEBUG -D_DEBUG -DWIN32 -D_MBCS -D_LIB
AR=i386-mingw32msvc-ar
TARGET=lib/Win32/Mingw32/libxlwd.a
ARFLAGS=rus
else
ifeq "$(CFG)"  "xlw - Win32 OnTheEdgeRelease"
CFLAGS+=-W -fexceptions -O2 -I. -DNDEBUG -DWIN32 -D_MBCS -D_LIB
AR=i386-mingw32msvc-ar
TARGET=lib/Win32/Mingw32/libxlw.a
ARFLAGS=rus
endif
endif
endif
endif

ifndef TARGET
TARGET=libxlw.a
endif

.PHONY: all
all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

%.res: %.rc
	$(RC) $(CPPFLAGS) -o $@ -i $<

INCLUDE= \
	xlw/config.bcc.h \
	xlw/config.msvc.h \
	xlw/ERR_Macros.h \
	xlw/EXCEL32_API.h \
	xlw/macros.h \
	xlw/port.h \
	xlw/pragmas.h \
	xlw/xlcall32.h \
	xlw/XlfAbstractCmdDesc.h \
	xlw/XlfArgDesc.h \
	xlw/XlfArgDescList.h \
	xlw/XlfCmdDesc.h \
	xlw/XlfExcel.h \
	xlw/XlfException.h \
	xlw/XlfFuncDesc.h \
	xlw/XlfOper.h \
	xlw/XlfRef.h \
	xlw/xlw.h

SOURCE= \
	xlw/excel32.cpp \
	xlw/XlfAbstractCmdDesc.cpp \
	xlw/XlfArgDesc.cpp \
	xlw/XlfArgDescList.cpp \
	xlw/XlfCmdDesc.cpp \
	xlw/XlfExcel.cpp \
	xlw/XlfException.cpp \
	xlw/XlfFuncDesc.cpp \
	xlw/XlfOper.cpp \
	xlw/XlfRef.cpp

INLINE= \
	xlw/XlfAbstractCmdDesc.inl \
	xlw/XlfExcel.inl \
	xlw/XlfException.inl \
	xlw/XlfOper.inl \
	xlw/XlfRef.inl

DOC= \
	Docs/pages/bibliography.txt \
	Docs/pages/copyright.txt \
	Docs/pages/download.txt \
	Docs/pages/faq.txt \
	Docs/pages/gettingStarted.txt \
	Docs/pages/history.txt \
	Docs/pages/index.txt \
	Docs/pages/install.txt \
	Docs/pages/knownbugs.txt \
	Docs/pages/misc.txt \
	Docs/pages/platforms.txt \
	Docs/pages/projects.txt \
	Docs/pages/usage.txt

SRCS=$(INCLUDE) $(SOURCE) $(INLINE) $(DOC)  \
	Docs/xlw.doxy

OBJS=$(patsubst %.rc,%.res,$(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(filter %.c %.cpp %.rc,$(SRCS)))))

$(TARGET): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET) xlw.dep

.PHONY: depends
depends:
	-$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MM $(filter %.c %.cpp,$(SRCS)) > xlw.dep

-include xlw.dep


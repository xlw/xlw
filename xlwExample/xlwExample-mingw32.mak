# Makefile - xlwExample.dsp

ifndef CFG
CFG=xlwExample - Win32 OnTheEdgeDebug
endif
CC=gcc
CFLAGS=
CXX=g++
CXXFLAGS=$(CFLAGS)
RC=windres -O COFF
ifeq "$(CFG)"  "xlwExample - Win32 Release"
CFLAGS+=-W -fexceptions -O2 -I$(XLW_DIR) -DNDEBUG -DWIN32 -D_WINDOWS -D_MBCS -D_USRDLL
LD=dllwrap
LDFLAGS=
TARGET=
LDFLAGS+=-L../lib/Win32/Mingw32
LIBS+=-lxlw -lstdc++
else
ifeq "$(CFG)"  "xlwExample - Win32 Debug"
CFLAGS+=-W -fexceptions -g -O0 -I$(XLW_DIR) -DXLW_DEBUG -D_DEBUG -DTEST_EXPORTS -DWIN32 -D_WINDOWS -D_MBCS -D_USRDLL
LD=dllwrap
LDFLAGS=
TARGET=
LDFLAGS+=-L../lib/Win32/Mingw32
LIBS+=-lxlwd -lstdc++
else
ifeq "$(CFG)"  "xlwExample - Win32 OnTheEdgeDebug"
CFLAGS+=-W -fexceptions -g -O0 -I.. -DXLW_DEBUG -D_DEBUG -DTEST_EXPORTS -DWIN32 -D_WINDOWS -D_MBCS -D_USRDLL
LD=dllwrap
LDFLAGS=
TARGET=
LDFLAGS+=-L../lib/Win32/Mingw32
LIBS+=-lxlwd -lstdc++
else
ifeq "$(CFG)"  "xlwExample - Win32 OnTheEdgeRelease"
CFLAGS+=-W -fexceptions -O2 -I.. -DNDEBUG -DWIN32 -D_WINDOWS -D_MBCS -D_USRDLL
LD=dllwrap
LDFLAGS=
TARGET=
LDFLAGS+=-L../lib/Win32/Mingw32
LIBS+=-lxlw -lstdc++
endif
endif
endif
endif

ifndef TARGET
TARGET=xll/Win32/Mingw32/xlwExample.xll
endif

.PHONY: all
all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

%.res: %.rc
	$(RC) $(CPPFLAGS) -o $@ -i $<

SRCS= \
	xlwExample.cpp

OBJS=$(patsubst %.rc,%.res,$(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(filter %.c %.cpp %.rc,$(SRCS)))))

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET) xlwExample.dep

.PHONY: depends
depends:
	-$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MM $(filter %.c %.cpp,$(SRCS)) > xlwExample.dep

-include xlwExample.dep


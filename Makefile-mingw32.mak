# Makefile - xlw.dsw

.PHONY: all
all: \
	xlw \
	xlwExample

.PHONY: xlw
xlw:
	$(MAKE) -f xlw-mingw32.mak

.PHONY: xlwExample
xlwExample:
	$(MAKE) -C xlwExample -f xlwExample-mingw32.mak

.PHONY: clean
clean:
	$(MAKE) -f xlw-mingw32.mak clean
	$(MAKE) -C xlwExample -f xlwExample-mingw32.mak clean

.PHONY: depends
depends:
	$(MAKE) -f xlw-mingw32.mak depends
	$(MAKE) -C xlwExample -f xlwExample-mingw32.mak depends


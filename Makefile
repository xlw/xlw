# Makefile - xlw.dsw

.PHONY: all
all: \
	xlw \
	xlwExample

.PHONY: xlw
xlw:
	$(MAKE) -f xlw.mak

.PHONY: xlwExample
xlwExample:
	$(MAKE) -C xlwExample -f xlwExample.mak

.PHONY: clean
clean:
	$(MAKE) -f xlw.mak clean
	$(MAKE) -C xlwExample -f xlwExample.mak clean

.PHONY: depends
depends:
	$(MAKE) -f xlw.mak depends
	$(MAKE) -C xlwExample -f xlwExample.mak depends


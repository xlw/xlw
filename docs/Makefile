
DOXY_FILE = xlw.linux.doxy
HTML_FILES := $(wildcard *.html)
HTML_DIR=html
IMAGES=html/sflogo.png html/logo_small.jpg
PAGES := $(wildcard pages/*.txt)
SOURCES := $(wildcard ../src/*.cpp)
HEADERS := $(wildcard ../include/xlw/*.h)
INLINES := $(wildcard ../include/xlw/*.inl)
INPUTS = $(SOURCES) $(HEADERS) $(INLINES)

all : refman

$(HTML_DIR) :
	mkdir html

$(IMAGES) :
	cp -f images/sflogo.png html/sflogo.png
	cp -f images/logo_small.jpg html/logo_small.jpg
	cp -f images/nazcatech.jpg html/nazcatech.jpg

refman : $(DOXY_FILE) $(HTML_FILES) $(HTML_DIR) $(IMAGES) $(INPUTS)
	doxygen $(DOXY_FILE)

#dist : all
#	tar zcfv html-singlepage.tgz html-singlepage
#	tar zcfv html-multipage.tgz html-multipage

clean :
	rm -rf html



# makefile for XLW documentation under Borland C++
#
# $Id $

.autodepend
#.silent

# Tools to be used
SED       = sed
DOXYGEN   = doxygen
LATEX     = latex
PDFLATEX  = pdflatex
MAKEINDEX = makeindex
DVIPS     = dvips

# Options
#TEX_OPTS = --quiet --pool-size=1000000
TEX_OPTS = --pool-size=1000000

# Primary target:
# all docs
all:: html
    cd latex
    $(PDFLATEX) $(TEX_OPTS) refman
    $(MAKEINDEX) refman.idx
    $(PDFLATEX) $(TEX_OPTS) refman
    $(LATEX) $(TEX_OPTS) refman
    $(DVIPS) refman
    cd ..

# HTML documentation only
html: html-offline

html-offline::
    $(DOXYGEN) xlw.doxy
    copy images\*.png html

html-online::
    $(SED) -e "s/xlwfooter.html/xlwfooteronline.html/" \
           xlw.doxy > xlw.doxy.temp
    $(DOXYGEN) xlw.doxy.temp
    del /Q xlw.doxy.temp
    copy images\*.png html

# PDF documentation
pdf:: html
    cd latex
    $(PDFLATEX) $(TEX_OPTS) refman
    $(MAKEINDEX) refman.idx
    $(PDFLATEX) $(TEX_OPTS) refman
    cd ..

# PostScript documentation
ps:: html
    cd latex
    $(LATEX) $(TEX_OPTS) refman
    $(MAKEINDEX) refman.idx
    $(LATEX) $(TEX_OPTS) refman
    $(DVIPS) refman
    cd ..

# Clean up
clean::
    if exist html  rmdir /S /Q html
    if exist latex rmdir /S /Q latex


# makefile for XLW documentation under Borland C++
#
# $Id $

.autodepend
.silent

# Tools to be used
SED       = sed
DOXYGEN   = doxygen
LATEX     = latex
PDFLATEX  = pdflatex
MAKEINDEX = makeindex
DVIPS     = dvips
HHC       = hhc

# Options
TEX_OPTS = --quiet --pool-size=1000000
#TEX_OPTS = --pool-size=1000000

# Primary target:
# all docs
all:: tex-files
    cd latex
    $(PDFLATEX) $(TEX_OPTS) refman
    $(MAKEINDEX) refman.idx
    $(PDFLATEX) $(TEX_OPTS) refman
    $(LATEX) $(TEX_OPTS) refman
    $(DVIPS) refman
    cd ..

# HTML documentation only
html: html-offline

winhelp:: html
    cd html
    $(HHC) index.hhp
    cd ..

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
pdf:: tex-files
    cd latex
    $(PDFLATEX) $(TEX_OPTS) refman
    $(MAKEINDEX) refman.idx
    $(PDFLATEX) $(TEX_OPTS) refman
    cd ..

# PostScript documentation
ps:: tex-files
    cd latex
    $(LATEX) $(TEX_OPTS) refman
    $(MAKEINDEX) refman.idx
    $(LATEX) $(TEX_OPTS) refman
    $(DVIPS) refman
    cd ..

# Correct LaTeX files to get the right layout
tex-files:: html
    copy userman.tex latex
    cd latex
    ren refman.tex oldrefman.tex
    $(SED) -e "/Page Index/d" \
           -e "/input{pages}/d" \
           -e "/Page Documentation/d" \
           -e "/input{bibliography}/d" \
           -e "/include{download}/d" \
           -e "/include{faq}/d" \
           -e "/include{gettingstarted}/d" \
           -e "/include{history}/d" \
           -e "/include{main}/d" \
           -e "/include{install}/d" \
           -e "/include{knownbugs}/d" \
           -e "/include{copyright}/d" \
           -e "/include{misc}/d" \
           -e "/include{platforms}/d" \
           -e "/include{projects}/d" \
           -e "/include{todo}/d" \
           -e "/include{usage}/d" \
           -e "s/ple Documentation}/ple Documentation}\\\\label{exchap}/" \
           oldrefman.tex > refman.tex
    del oldrefman.tex
    cd ..

# Clean up
clean::
    if exist html  rmdir /S /Q html
    if exist latex rmdir /S /Q latex

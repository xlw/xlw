
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

# Options
TEX_OPTS = --quiet --pool-size=1000000

# Primary target:
# all docs
all:: tex-files pdf-figures
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
pdf:: tex-files pdf-figures
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
           -e "/input{group}/d" \
           -e "/include{coreclasses}/d" \
           -e "/include{currencies}/d" \
           -e "/include{datetime}/d" \
           -e "/include{findiff}/d" \
           -e "/include{fixedincome}/d" \
           -e "/include{history}/d" \
           -e "/include{index}/d" \
           -e "/include{install}/d" \
           -e "/include{instruments}/d" \
           -e "/include{license}/d" \
           -e "/include{math}/d" \
           -e "/include{mcarlo}/d" \
           -e "/include{overview}/d" \
           -e "/include{patterns}/d" \
           -e "/include{platforms}/d" \
           -e "/include{resources}/d" \
           -e "/include{termstructures}/d" \
           -e "/include{usage}/d" \
           -e "/include{utilities}/d" \
           -e "/include{where}/d" \
           -e "/include{todo}/d" \
           -e "s/ple Documentation}/ple Documentation}\\\\label{exchap}/" \
           oldrefman.tex > refman.tex
    del oldrefman.tex
    cd ..

# some uncharted combination of dot and epstopdf leads to cropped pdf figures.
# removing the %%BoundingBox line and rerunning epstopdf fixes them.
pdf-figures:: html
    cd latex
    FOR /F %i IN ('dir /B a0*.eps') DO @( copy %i %i.bak > NUL & sed -e "/%%BoundingBox/d" %i.bak > %i &  epstopdf %i 2> NUL & copy %i.bak %i > NUL & del %i.bak)
    cd ..

# Clean up
clean::
    if exist html  rmdir /S /Q html
    if exist latex rmdir /S /Q latex

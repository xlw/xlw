
$Id: README.txt 545 2008-05-21 13:30:50Z ericehlers $

The doxygen utility is used to generate the documentation based on comments extracted from the source code.  The current configuration relies on doxygen version 1.5.5.

To build the documentation under Linux, do 'make'.  This uses configuration xlw.linux.doxy and writes the docs in html format to the html subdirectory.

To build the documentation under Windows, use the DOS batch file run_doxygen.bat.  This uses configuration xlw.windows.doxy, in addition to html a chm file is produced.  In xlw.windows.doxy, HAVE_DOT = NO, this spares you the hassle of installing graphviz etc. but yields inferior diagrams.

The html directory should be kept in synch with the refman directory on the website.

Refer to the xlwplus2 subdirectory for documentation relating to the InterfaceGenerator utility and other features.

Below are some older comments which remain largely relevant.

============================================================

The documentation is automatically extracted from the source code using
DoxyGen (http://www.stack.nl/~dimitri/doxygen/).
The current version we're using is 1.2.11.1

The basic requirement to produce html documentation are:
1) DoxyGen (latest release at
   http://www.stack.nl/~dimitri/doxygen/download.html#latestsrc)
2) Graphviz (http://www.research.att.com/sw/tools/graphviz/)
3) Aladdin Ghostscript (http://www.cs.wisc.edu/~ghost/)

If you want to produce PDF and/or PS documentation you will need also:
4) TeX/LaTeX
5) LaTeX Fancy Header (http://toocool.calpoly.edu/latex/fancy_header.html)
6) epstopdf. It's available as Perl script (you will also need Perl, of
   course), C source to be compiled or Windows executable.
   http://www.tex.ac.uk/tex-archive/help/Catalogue/entries/epstopdf.html
   or http://www.ctan.org/tex-archive/support/epstopdf/



*********
* Win32 *
*********

To produce HTML documentation:
1) Install Doxygen. You will also need to add to your PATH doxygen-x.x.x\bin.
2) Install Graphviz. Add to your PATH Graphviz\bin
3) Install Ghostscript. Add to your path gs\gsx.xx\bin
4) a) Borland user: type 'make html' in the Docs directory
   b) VC user: go to the Docs directory and type:
      doxygen xlw.doxy

If you want to produce TeX/PDF/PS documentation:
5) install MiKTeX 2 or higher from http://www.miktex.org
   Choose to create your "Local TEXMF Tree".
   Add miktex\bin (where latex.exe is) to your PATH.
6) under your "Local TEXMF Tree" create a folder \tex\latex\fancyhdr
   that includes fancyhdr.sty, extramarks.sty and fixmarks.sty (the 3 files
   can be downloaded from http://toocool.calpoly.edu/latex/fancy_header.html)
7) download http://www.tex.ac.uk/tex-archive/support/epstopdf/epstopdf.exe
   and copy it into a directory on your path
8) Open MikTeX Options panel from "Programs/MiKTeX 2" list and click on the
   "Refresh Now" button in the "General" folder.
9) a) Borland users: type 'make ps' or 'make pdf' from the Docs
      directory
   b) VC user: go to the Docs\latex directory and type:
        latex refman
        makeindex refman.idx
        latex refman
      for PostScript output or
        pdflatex refman
        makeindex refman.idx
        pdflatex refman
      for PDF output.
   Just ignore TeX/LaTeX warning/error.

If you want to compile the HTML documentation into Microsoft Help format:
10) download and install the HTML Help Workshop from
    msdn.microsoft.com/library/default.asp?url=/library/en-us/htmlhelp/html/vsconhh1start.asp
    and add to your path the directory created by the installer
11) type 'hhc index.hhp' from the Docs\html directory. The file
    index.chm will be created.


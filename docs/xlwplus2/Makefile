
TEX_FILE=xlwplus2.tex

all : html-singlepage html-multipage pdf

html-singlepage : $(TEX_FILE)
	latex2html $(TEX_FILE) -init_file latex2html-init-singlepage

html-multipage : $(TEX_FILE)
	latex2html $(TEX_FILE) -init_file latex2html-init-multipage

pdf : $(TEX_FILE)
	pdflatex $(TEX_FILE)

dist : all
	tar zcfv html-singlepage.tgz html-singlepage
	tar zcfv html-multipage.tgz html-multipage

clean :
	rm -rf html-singlepage html-multipage
	rm -f root.* *.tgz
	find root -name "*.aux" -exec rm {} \;


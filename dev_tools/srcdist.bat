
cd ..\..\
if exist del xlw-*.zip
cd xlw
zip -r -v ..\xlw-1.1.0a1-cvs.zip . -i *.cpp *.h *.hpp *.inl *.mak *.nsi *.dsp *.dsw *.txt *.doxy xlwfooter*.html *.png *.xls
cd xlw/dev_tools

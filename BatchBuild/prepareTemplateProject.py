

import os
import shutil


shutil.rmtree("C:/Temp/xlwTemplate Projects",True)
shutil.copytree('../xlw/Template_Projects','C:/Temp/xlwTemplate Projects',ignore=shutil.ignore_patterns('*.xls', '.svn'))



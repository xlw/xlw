

import os
import shutil


shutil.rmtree("C:/Temp/xlwTemplate_Projects",True)
shutil.copytree('../xlw/Template_Projects','C:/Temp/xlwTemplate_Projects',ignore=shutil.ignore_patterns('*.xls', '.svn'))





import os
import shutil


shutil.rmtree("C:/Temp/xlwDotNetTemplate_Projects",True)
shutil.copytree('../xlwDotNet/Template_Projects','C:/Temp/xlwDotNetTemplate_Projects',ignore=shutil.ignore_patterns('*.xls', '.svn'))

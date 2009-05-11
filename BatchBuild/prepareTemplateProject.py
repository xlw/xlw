

import os
import shutil


shutil.rmtree("C:/Temp/xlwTemplateProjects",True)
shutil.copytree('../xlw/Template_Projects','C:/Temp/xlwTemplateProjects',ignore=shutil.ignore_patterns('*.xls', '.svn'))



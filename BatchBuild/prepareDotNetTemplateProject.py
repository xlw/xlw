

import os
import shutil


shutil.rmtree("C:/Temp/xlwDotNetTemplateProjects",True)
shutil.copytree('../xlwDotNet/Template_Projects','C:/Temp/xlwDotNetTemplateProjects',ignore=shutil.ignore_patterns('*.xls', '.svn'))

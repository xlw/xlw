

import os
import shutil


shutil.rmtree("C:/Temp/xlwDotNetTemplate Projects",True)
shutil.copytree('../xlwDotNet/Template_Projects','C:/Temp/xlwDotNetTemplate Projects',ignore=shutil.ignore_patterns('Debug','Release','x64_Debug','x64_Release','bin','obj','*.xls', '.svn'))


#    Copyright (C) 2016 John Adcock
#
#    This file is part of XLW, a free-software/open-source C++ wrapper of the
#    Excel C API - http://xlw.sourceforge.net/
#
#    XLW is free software: you can redistribute it and/or modify it under the
#    terms of the XLW license.  You should have received a copy of the
#    license along with this program; if not, please email xlw-users@lists.sf.net
#
#    This program is distributed in the hope that it will be useful, but WITHOUT
#    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
#    FOR A PARTICULAR PURPOSE.  See the license for more details.


import os
import shutil

destinationPaths = ['../xlw'
                   ]

oldProject = 'vc12'
newProject = 'vc14'
solutionOld = '# Visual C++ Express 2012'
solutionNew = '# Visual Studio 14\r\nVisualStudioVersion = 14.0.23107.0\r\nMinimumVisualStudioVersion = 10.0.40219.1'
solutionOld2 = '# Visual Studio 2013\r\nVisualStudioVersion = 12.0.30501.0'
solutionNew2 = '# Visual Studio 14\r\nVisualStudioVersion = 14.0.23107.0'
projOld = 'v120'
projNew = 'v140'

def dirwalk(dir):
    for f in os.listdir(dir):
        fullpath = os.path.join(dir,f)
            
        if os.path.isdir(fullpath) and not os.path.islink(fullpath) and not f==".svn":
            yield fullpath
            for x in dirwalk(fullpath):  # recurse into subdir
                yield x

def replaceinPlace(filename, oldString, newString):
  with open(filename) as f:
    newText=f.read().replace(oldString, newString)

  with open(filename, "w") as f:
    f.write(newText)
                
def updateSolution(dir, fileext, oldString, newString):
    for f in os.listdir(dir):
        if fileext == os.path.splitext(f)[1]:
            replaceinPlace(os.path.join(dir, f), oldString, newString)

def createProject(dir):
    newdir = os.path.join(dir, newProject)
    shutil.copytree(os.path.join(dir, oldProject), newdir, ignore=shutil.ignore_patterns('Debug','Release','x64_Debug','x64_Release','bin','obj','*.xls', '.svn'))
    updateSolution(newdir, '.sln', solutionOld, solutionNew)
    updateSolution(newdir, '.sln', solutionOld2, solutionNew2)
    updateSolution(newdir, '.vcxproj', projOld, projNew)
    os.system('svn add "' + newdir + '"')    

for dir in destinationPaths:
    dirs = dirwalk(dir)
    for f in dirs:
        if(os.path.exists(os.path.join(f, oldProject)) and not os.path.exists(os.path.join(f, newProject))):
            createProject(f)
    

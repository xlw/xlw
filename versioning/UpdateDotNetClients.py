
#   Copyright (C) 2009 2012 Narinder S Claire
#   Copyright (C) 2011 John Adcock
#
#   This file is part of XLW, a free-software/open-source C++ wrapper of the
#   Excel C API - http://xlw.sourceforge.net/
#
#   XLW is free software: you can redistribute it and/or modify it under the
#   terms of the XLW license.  You should have received a copy of the
#   license along with this program; if not, please email xlw-users@lists.sf.net
#
#   This program is distributed in the hope that it will be useful, but WITHOUT
#   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
#   FOR A PARTICULAR PURPOSE.  See the license for more details.


import re
import sys
import os

destinationPaths = [
                    '../xlwDotNet/Build/VS8/DotNetInterfaceGenerator',
                    '../xlwDotNet/Build/VS9/DotNetInterfaceGenerator',
                    '../xlwDotNet/Build/VS10/DotNetInterfaceGenerator',
					'../xlwDotNet/Build/VS11/DotNetInterfaceGenerator',
					'../xlwDotNet/Build/VS12/DotNetInterfaceGenerator',
                    '../xlwDotNet/UserContrib',
                    '../xlwDotNet/Template_Projects',
                    '../xlwDotNet/Examples'
                   ]

affectedFiles = ['.vcproj','.vcxproj']
affectedFiles2 = ['.csproj','.fsproj','.vbproj','.csxproj','.vbxproj']

with open("./XLWVERSION",'r') as versionfile:
    xlwversion = versionfile.readlines()
xlwversion=xlwversion[0].strip().replace('.','_').replace('-','_')


def dirwalk(dir, fileTypes):
    print "Searching ",os.path.abspath(dir)
    for f in os.listdir(dir):
        fullpath = os.path.join(dir,f)
        if os.path.isdir(fullpath) and not os.path.islink(fullpath):
            for x in dirwalk(fullpath, fileTypes):  # recurse into subdir
                yield x
        else:
            if fileTypes.count(os.path.splitext(fullpath)[1])>0 :
                yield os.path.abspath(fullpath)

def processFile(f, reObject, theLogFile, splitChar, xlwversion):
    print "processing file  ",f
    with open(f,'r') as theFile:
        theContent = theFile.readlines()
        i=0
        for line in theContent:
                pattern = re.search(reObject,line)
                if pattern!=None:
#                        print "pattern  ",pattern.group(0)
                        theFound=pattern.group(0)
                        theParts = theFound.split(splitChar)
                        theParts[-1] = xlwversion 
                        replacement = splitChar.join(theParts)
                        theLogFile.write(f +  " "+str(i)+ " "+ pattern.group(0)+ " changing to "+ replacement +'\n')
                        theContent[i]= reObject.sub(replacement ,line)
                i=i+1
        with open(f,'w') as theFile:
                theFile.writelines(theContent)

allfiles = []
allfiles2 = []
for dir in destinationPaths:
    allfiles = allfiles + [f for f in dirwalk(dir, affectedFiles)]
    allfiles2 = allfiles2 + [f for f in dirwalk(dir, affectedFiles2)]
    
reObject = re.compile('xlwDotNet-vc[0-9]{2,3}-mt-.*?(?=\.dll)|xlwDotNet-vc[0-9]{2,3}-mt-gd-.*?(?=\.dll)|'
                      'xlwDotNet-vc[0-9]{2,3}-mt\$\(gdconfig\)-.*?(?=\.dll)')
reObject2 = re.compile('xlwversion\>.*?(?=\<\/xlw)') # .*?(?=\<xlw)

with open("UpdateDotNetClients.log",'w') as theLogFile:
    for  f in allfiles:
            processFile(f, reObject, theLogFile, '-', xlwversion)
    for  f in allfiles2:
            processFile(f, reObject2, theLogFile, '>', xlwversion)



	
	

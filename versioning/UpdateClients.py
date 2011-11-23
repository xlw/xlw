
#	Copyright (C) 2009 Narinder S Claire
#	Copyright (C) 2011 John Adcock
#
#	This file is part of XLW, a free-software/open-source C++ wrapper of the
#	Excel C API - http://xlw.sourceforge.net/
#
#	XLW is free software: you can redistribute it and/or modify it under the
#	terms of the XLW license.  You should have received a copy of the
#	license along with this program; if not, please email xlw-users@lists.sf.net
#
#	This program is distributed in the hope that it will be useful, but WITHOUT
#	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
#	FOR A PARTICULAR PURPOSE.  See the license for more details.


import re
import sys
import os

destinationPaths = ['../xlw/examples',
					'../xlw/Template_Projects',
					'../xlw/usercontrib',
					'../xlwDotNet/UserContrib',
					'../xlwDotNet/Template_Projects',
					'../xlwDotNet/Examples'
				   ]

effectedFiles = ['.vcproj','.vcxproj','.mak','.cbp']

with open("./XLWVERSION",'r') as versionfile:
	xlwversion = versionfile.readlines()
xlwversion=xlwversion[0].strip().replace('.','_').replace('-','_')


def dirwalk(dir):
    print "Searching ",os.path.abspath(dir)
    for f in os.listdir(dir):
        fullpath = os.path.join(dir,f)
        if os.path.isdir(fullpath) and not os.path.islink(fullpath):
            for x in dirwalk(fullpath):  # recurse into subdir
                yield x
        else:
			if effectedFiles.count(os.path.splitext(fullpath)[1])>0 or os.path.basename(fullpath).lower()=="makefile" or os.path.basename(fullpath).lower()=="makefile.win":
				yield os.path.abspath(fullpath)


allfiles = []
for dir in destinationPaths:
	allfiles = allfiles + [f for f in dirwalk(dir)]
	
reObject = re.compile('xlw-[a-zA-Z0-9_]*?-gcc-s-[a-zA-Z0-9,_]*?(?=_@@_)|xlw-.*?-gcc-s-gd-[a-zA-Z0-9_]*?(?=_@@_)|'
				                    'xlw-[a-zA-Z0-9_]*?-gcc-s-[a-zA-Z0-9,_]*?(?=\s)|xlw-.*?-gcc-s-gd-[a-zA-Z0-9_]*?(?=\s)|'
									'xlw-[a-zA-Z0-9_]*?-gcc-s-[a-zA-Z0-9,_]*?(?=\.a)|xlw-.*?-gcc-s-gd-[a-zA-Z0-9_]*?(?=\.a)|'
									'xlw-gcc-s-[a-zA-Z0-9,_]*?(?=_@@_)|xlw-gcc-s-gd-[a-zA-Z0-9_]*?(?=_@@_)|'
				                    'xlw-gcc-s-[a-zA-Z0-9,_]*?(?=\s)|xlw-gcc-s-gd-[a-zA-Z0-9_]*?(?=\s)|'
									'xlw-gcc-s-[a-zA-Z0-9,_]*?(?=\.a)|xlw-gcc-s-gd-[a-zA-Z0-9_]*?(?=\.a)|'
									'xlw-vc[0-9]{2,3}-mt.*?(?=\.lib)')# stupid devcpp with the _@@_

with open("UpdateClients.log",'w') as theLogFile:
	for  f in allfiles:
		with open(f,'r') as theFile:
			theContent = theFile.readlines()
		i=0
		for line in theContent:
			pattern = re.search(reObject,line)
			if pattern!=None:
				theFound=pattern.group(0)
				theParts = theFound.split('-')
				theParts[-1] = xlwversion 
				replacement = '-'.join(theParts)
				theLogFile.write(f +  " "+str(i)+ " "+ pattern.group(0)+ " changing to "+ replacement +'\n')
				theContent[i]= reObject.sub(replacement ,line)
			i=i+1
		with open(f,'w') as theFile:
			theFile.writelines(theContent)



	
	

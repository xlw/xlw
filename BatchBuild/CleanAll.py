
#	Copyright (C) 2009 2010 2011 Narinder S Claire
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


import os

destinationPaths = ['../xlw',
					'../xlwDotNet'
				   ]

effectedFiles = ['.obj','.o','.exe','.dll',
                 '.lib','.obj','.pdb','.a',
				 '.xll','.idb','.pch','.manifest',
				 '.ncb','.ilk'
				]


def dirwalk(dir):
    print "Searching ",os.path.abspath(dir)
    for f in os.listdir(dir):
        fullpath = os.path.join(dir,f)
        if os.path.isdir(fullpath) and not os.path.islink(fullpath) and not f==".svn":
            for x in dirwalk(fullpath):  # recurse into subdir
                yield x
        else:
			if effectedFiles.count(os.path.splitext(fullpath)[1])>0  :
				yield os.path.abspath(fullpath)
			if os.path.basename(fullpath)=="BuildLog.htm":
				yield os.path.abspath(fullpath)
			if os.path.basename(fullpath).endswith(".dll.embed.manifest.res"):
				yield os.path.abspath(fullpath)
			if os.path.basename(fullpath).endswith(".suo"):
				yield os.path.abspath(fullpath)
			if os.path.basename(fullpath).endswith(".sln.cache"):
				yield os.path.abspath(fullpath)
			if os.path.basename(fullpath)=='ResolveAssemblyReference.cache':
				yield os.path.abspath(fullpath)
			
		


allfiles = []
for dir in destinationPaths:
	for f in dirwalk(dir):
		print "Deleting ",os.path.abspath(f)
		os.remove(os.path.abspath(f))
	

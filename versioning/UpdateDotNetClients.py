

import re
import sys
import os

destinationPaths = [
					'../xlwDotNet/Build/VS8/DotNetInterfaceGenerator',
					'../xlwDotNet/Build/VS9/DotNetInterfaceGenerator',
					'../xlwDotNet/XtraExamples',
					'../xlwDotNet/Template Projects',
					'../xlwDotNet/Example'
				   ]

effectedFiles = ['.vcproj','.csproj']

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
			if effectedFiles.count(os.path.splitext(fullpath)[1])>0 :
				yield os.path.abspath(fullpath)


allfiles = []
for dir in destinationPaths:
	allfiles = allfiles + [f for f in dirwalk(dir)]
	
reObject = re.compile('xlwDotNet-vc[8-9][0-9]-mt-.*?(?=.dll)|xlwDotNet-vc[8-9][0-9]-mt-gd-.*?(?=.dll)|'
                      'xlwDotNet-vc[8-9][0-9]-mt\$\(gdconfig\)-.*?(?=.dll)')

with open("UpdateDotNetClients.log",'w') as theLogFile:
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



	
	

#       Copyright (C) 2009 2010 2011 Narinder S Claire
#       Copyright (C) 2011 John Adcock
#
#       This file is part of XLW, a free-software/open-source C++ wrapper of the
#       Excel C API - http://xlw.sourceforge.net/
#
#       XLW is free software: you can redistribute it and/or modify it under the
#       terms of the XLW license.  You should have received a copy of the
#       license along with this program; if not, please email xlw-users@lists.sf.net
#
#       This program is distributed in the hope that it will be useful, but WITHOUT
#       ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
#       FOR A PARTICULAR PURPOSE.  See the license for more details.


import os
import sys
from xml.dom import minidom

vcprojects = ['../xlw/build/vc7/xlw.vcproj',
                          '../xlw/build/vc8/xlw.vcproj',
                          '../xlw/build/vc9/xlw.vcproj',
                          '../xlwDotNet/Build/VS8/xlwDotNet/xlwDotNet.vcproj',
                          '../xlwDotNet/Build/VS9/xlwDotNet/xlwDotNet.vcproj',
                          ]

vcxprojects = ['../xlw/build/vc10/xlw.vcxproj',
               '../xlwDotNet/Build/VS10/xlwDotNet/xlwDotNet.vcxproj',
			   '../xlw/build/vc11/xlw.vcxproj',
               '../xlwDotNet/Build/VS11/xlwDotNet/xlwDotNet.vcxproj',
			   '../xlw/build/vc12/xlw.vcxproj',
               '../xlwDotNet/Build/VS12/xlwDotNet/xlwDotNet.vcxproj',
                          ]
                
cbprojects = ['../xlw/build/codeblocks-gcc/xlw.cbp']

makefiles = ['../xlw/build/gcc-make/XLWVERSION.mak']


def writeVS7project(f,theRoot,indent):
        f.write('\n'+indent+"<" + theRoot.nodeName)

        theAttributes = theRoot.attributes.keys()
        if theAttributes.count(u'Name')!=0:
                f.write('\n'+indent+'\t\tName="'+theRoot.attributes['Name'].value +'"')
                theAttributes.remove(u'Name')
        for att in theAttributes:
                f.write('\n'+indent+'\t\t'+att+'="'+theRoot.attributes[att].value +'"' )

        children = []
        for child in theRoot.childNodes:
                if child.nodeName!="#text":
                        children.append(child)
                        
        if len(children)> 0 :
                f.write('>')    
                for child in children:
                        writeVS7project(f,child,indent+'\t')
                f.write('\n'+indent+'</'+theRoot.nodeName+">" )
        else :
                f.write('/>')   
        
def     overwrite(vcproj,modName):
        oldfname = vcproj+".bak"
        if os.path.isfile(oldfname):
                        if os.path.isfile(oldfname+'.10'):
                                os.remove(oldfname+'.10')
                        i = 2
                        while i<=10:
                                if os.path.isfile(oldfname+"."+str(i))==0:
                                        oldfname=oldfname+"."+str(i)
                                        i=10
                                i=i+1          
        os.rename(vcproj,oldfname)
        os.rename(modName,vcproj)

with  open("XLWVERSION",'r') as versionFile:
        xlwversion = versionFile.readlines()
xlwversionString = xlwversion[0].strip().replace('.','_').replace('-','_')

# All Visual Studio project files <= VS9
for vcproj in vcprojects:
        pd = minidom.parse(vcproj)
        theRoot = pd.firstChild
        theMains = theRoot.childNodes
        nameList = [e.nodeName for e in theMains]
        projectName = theRoot.attributes["Name"].value
        theRoot.attributes["Name"].value = xlwversionString
        print "Changed version in " + vcproj + " from " + projectName + " to " + xlwversionString       
        path = os.path.split(vcproj)[0]
        withoutExtension = os.path.splitext(os.path.split(vcproj)[1])[0]
        modName = os.path.join(path,withoutExtension+".mod")

        with open(modName,'w') as f:
                f.write('<?xml version="1.0" encoding="Windows-1252"?>')
                writeVS7project(f,theRoot,"\t")
    
        overwrite(vcproj,modName)

# All Visual Studio project files > VS10
for vcxproj in vcxprojects:
        pd = minidom.parse(vcxproj)
        theRoot = pd.firstChild

        globalsList = [e for e in theRoot.childNodes
                                        if e.nodeName=='PropertyGroup'
                                                and e.attributes.keys().count(u'Label')>0
                                                        and e.attributes['Label'].value=='Globals']

        nameList = [e for e in globalsList[0].childNodes
                                        if e.nodeName=='ProjectName']

        projectName = nameList[0].firstChild.data
        nameList[0].firstChild.data = xlwversionString
        
        print "Changed version in " + vcxproj + " from " + projectName + " to " + xlwversionString      
        path = os.path.split(vcxproj)[0]
        withoutExtension = os.path.splitext(os.path.split(vcxproj)[1])[0]
        modName = os.path.join(path,withoutExtension+".mod")

        with open(modName,'w') as f:
                f.write( pd.toxml())

        overwrite(vcxproj,modName)
        
# Code::Blocks project files
for cbproj in cbprojects:
        pd = minidom.parse(cbproj)
        CodeBlocks_project_file = pd.firstChild
        firstGen = CodeBlocks_project_file.childNodes
        nameList = [e.nodeName for e in firstGen]
        projectIndex = nameList.index("Project")
        projectNode = firstGen[projectIndex]
        
        optionList = [e for e in projectNode.childNodes 
                                        if e.nodeName=='Option' 
                                                and e.attributes.keys().count(u'title')>0]
        oldVersion = optionList[0].attributes["title"].value
        optionList[0].attributes["title"].value = xlwversionString
        
        path = os.path.split(cbproj)[0]
        withoutExtension = os.path.splitext(os.path.split(cbproj)[1])[0]
        modName = os.path.join(path,withoutExtension+".mod")
        
        with open(modName,'w') as f:
                f.write( pd.toxml())
                
        overwrite(cbproj,modName)
        print "Changed version in " + cbproj + " from " + oldVersion + " to " + xlwversionString        
        
        
# for makefile
theLines = ["# Do not edit this file\n",
                        "# It is  automaticaly generated by UpdateVersion.py\n",
                        "XLWVERSION="+xlwversionString+'\n']

for makefile in makefiles:
        with open(makefile,'w') as f:
                        f.writelines(theLines)
        print "Changed version in " + makefile +" from " + oldVersion + " to " + xlwversionString

        
#for the packaging NSIS script
with open('../version.nsh','w') as versionFile:
        versionFile.write('!define XLW_VERSION "' + xlwversion[0].strip() +'"')
        
        
        
        
        
        
        
        
        
        
        
        
        

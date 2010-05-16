You need to install IronPython from 
   http://ironpython.codeplex.com/Release/ProjectReleases.aspx?ReleaseId=12481

Then you need to make sure the Ironpython asemblies are referenced correctly in your DotNet project.
By default they will be refernced from 
          C:\Program Files\IronPython 2.0.1

But if you installed your IronPython elswwhere or you have a differnt version you need to re-refernce them. 
In your DotNet project in Visual STudio you will see 'References', thats where you need to do it.



Will follow up this example with more documentation


















 Copyright (C) 2008 2009  Narinder S Claire

 This file is part of XLWDOTNET, a free-software/open-source C# wrapper of the
 Excel C API - http://xlw.sourceforge.net/
 
 XLWDOTNET is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/
 
 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net
 
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
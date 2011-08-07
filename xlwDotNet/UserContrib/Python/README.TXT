You need to install IronPython from 
   http://ironpython.codeplex.com/




Then you need to make sure the Ironpython asemblies are referenced correctly in your DotNet project.
In this example 
	VS2005 & VS2008 require IronPython 2.6.2 targeting .NET2.0
        VS2010          requires IronPython 2.7  targeting .NET4.0

By default they will be refernced from 
          C:\Program Files\IronPython 2.x.x

These dependecies should be changeable by the user.

If you installed your IronPython elswwhere or you have a differnt version you need to re-refernce them. 
In your DotNet project in Visual STudio you will see 'References', thats where you need to do it.







 Copyright (C) 2008 2009 2011 Narinder S Claire

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
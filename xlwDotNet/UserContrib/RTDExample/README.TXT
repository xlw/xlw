



Q. What is an RTD Server ?

A. http://support.microsoft.com/kb/289150
   

On how to set up a basic RTD Server 
see 

  http://weblogs.asp.net/kennykerr/archive/2008/11/13/Rtd3.aspx


To build this demo, you need to make sure that the DotNet project
references 
 Microsoft.Office.Core ( Microsoft 1x.x Object Library) found under COM in the references 
&
 Microsoft.Office.Interop.Excel (Microsoft.Office.Interop.Excel under .NET references )


You may need to remove my references in the project as I may have different versions to you and
 re-add your own




PS THIS WILL NOT WORK WITH TWO INSTANCES OF EXCEL.
   If you open a second instance of excel, this 
   addin will only work on the first one. This 
   is NOT a bug, its a limitation. Maybe someone can 
   remove this limitation.









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

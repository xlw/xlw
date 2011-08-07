

HYBRID TEMPLATE
===============

These Templates are for the Visual Studio Professional Editions ( 2005,2008 & 2010).
They let you build C++,C# hybrid XLLs all in one Visual Studio Solution.

In the Solution you will find a project called DotNet and a project called Native.
The source files for the project XLL are generated automatically and you shouldn't
edit these. To build the excel just build the project XLL, it will automatically 
initiate the building of the other projects in the correct order. Do not edit the
auto-generated source files in this project.

You can add your C++ functions to Native. See the documentation for xlw to see how to do this.
But briefly to the C++ function foo to excel, implement th function in any source file (.cpp)
in the Native project. You must decorate the function with the macro XLLEXPORT.

std::string XLLEXPORT foo(std::string name)
{
	return std::string("Hello ") + name + ", how are you ?"
}

Then add a declaration of this function to the header file native.h
with appropriate decorators ( function & parameter descriptions)

std::string // This C++ function just says hello

foo (
      std::string name // This parameter is the users name
    );


To add a C# function just add the C# function to the DotNet project

[ExcelExport("This C# function just says hello")]
public static string foo(
          [Parameter("This parameter is the users name")] string name
      )
       {
            return "Hello " + name + ", how are you ";
       }

And thats it.

All exported functions (C++ & C# ) appear as excel functions in the same way. 
The user will not  be able to tell whteher the function is implemented in C++ 
or C#.
This is very useful if you have an older C++ xll library and you want to extend it
with C# but not have to drop the old library.
Also you may find that you want to implement some functions in C# and others in
C++ depending on their purpose. For example you may decide to implement a monte
carlo pricing engine in C++ but decided that the function to obtain the market data
from a database are better implemented in C#.

Anyway enjoy and have fun. 



-----------------------------------------------------------------------------

 Copyright (C) 2008 2009 2010 2011  Narinder S Claire

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

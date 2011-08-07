//
//
//
//                                        TypeRegistrations.cpp
//
/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2011 Narinder S Claire

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include "TypeRegister.h"

namespace
{
// fundamental types
TypeRegistry<native>::Helper voidReg("void", // New type
               "void",          // Old type
               "",              // Converter name, we just pass into the constructor as a declaration
               false,           // Is a method
               false,           // Takes identifier
               "#ERR"           // Type code
               );

TypeRegistry<native>::Helper XlfOperReg("XlfOper", // New type
               "LPXLFOPER",     // Old type
               "",              // Converter name, we just pass into the constructor as a declaration
               false,           // Is a method
               false,           // Takes identifier
               "XLF_OPER"       // Type code
               );

TypeRegistry<native>::Helper doubleFundamentalReg("double", // New type
               "double",        // Old type, EXCEL understands doubles so this is simply a copy
               "",              // Converter name, we just pass into the constructor as a declaration
               false,           // Is a method
               false,           // Takes identifier
               "B"              // Type code
               );

TypeRegistry<native>::Helper arrayFundamentalReg("NEMatrix", // New type
               "LPXLARRAY",     // Old type
               "GetMatrix",     // Converter name, we just pass into the constructor as a declaration
               false,           // Is a method
               false,           // Takes identifier
               "XLW_FP",        // Type code
               "<xlw/xlarray.h>"// Include file
               );

TypeRegistry<native>::Helper shortreg("short", // New type
               "XlfOper",       // Old type
               "AsShort",       // Converter name
               true,            // Is a method
               true,            // Takes identifier
               "XLF_OPER"       // Type code
               );

TypeRegistry<native>::Helper arrayreg("MyArray", // New type
               "XlfOper",       // Old type
               "AsArray",       // Converter name
               true,            // Is a method
               true,            // Takes identifier
               "XLF_OPER"       // Type code
               );

TypeRegistry<native>::Helper matrixreg("MyMatrix", // New type
               "XlfOper",       // Old type
               "AsMatrix",      // Converter name
               true,            // Is a method
               true,            // Takes identifier
               "XLF_OPER"       // Type code
               );

TypeRegistry<native>::Helper cellsreg("CellMatrix", // New type
               "XlfOper",       // Old type
               "AsCellMatrix",  // Converter name
               true,            // Is a method
               true,            // Takes identifier
               "XLF_OPER"       // Type code
               );

TypeRegistry<native>::Helper stringreg("string", // New type
               "XlfOper",       // Old type
               "AsString",      // Converter name
               true,            // Is a method
               true,            // Takes identifier
               "XLF_OPER"       // Type code
               );

TypeRegistry<native>::Helper sstringreg("std::string", // New type
               "XlfOper",       // Old type
               "AsString",      // Converter name
               true,            // Is a method
               true,            // Takes identifier
               "XLF_OPER"       // Type code
               );

TypeRegistry<native>::Helper boolreg("bool", // New type
               "XlfOper",       // Old type
               "AsBool",        // Converter name
               true,            // Is a method
               true,            // Takes identifier
               "XLF_OPER"       // Type code
               );

// Usually XlfOper is registered as type XLF_OPER   which equates to either P (OPER)   or Q (OPER12)
// Here    XlfOper is registered as type XLF_XLOPER which equates to either R (XLOPER) or U (XLOPER12)
TypeRegistry<native>::Helper RefTestReg("reftest", // New type
               "LPXLFOPER",     // Old type
               "",              // Converter name, we just pass into the constructor as a declaration
               false,           // Is a method
               false,           // Takes identifier
               "XLF_XLOPER"     // Type code
               );

// extended types

TypeRegistry<native>::Helper ULreg("unsigned long", // New type
               "double",        // Old type
               "static_cast<unsigned long>", // Converter name
               false,           // Is a method
               false            // Takes identifier
               );

TypeRegistry<native>::Helper intreg("int", // New type
               "double",        // Old type
               "static_cast<int>", // Converter name
               false,           // Is a method
               false            // Takes identifier
               );

// Special processing of std::wstring depending on Excel version
TypeRegistry<native>::Helper wstrreg("std::wstring", // New type
               "XlfOper",       // Old type
               "AsWstring",      // Converter name
               true,            // Is a method
               true,            // Takes identifier
               "XLF_OPER");

TypeRegistry<native>::Helper DONreg("DoubleOrNothing", // New type
               "CellMatrix",    // Old type
               "DoubleOrNothing", // Converter name
               false,           // Is a method
               true             // Takes identifier
               );

TypeRegistry<native>::Helper arglistreg("ArgumentList", // New type
               "CellMatrix",    // Old type
               "ArgumentList",  // Converter name
               false,           // Is a method
               true,            // Takes identifier
               "",              // No key
               "<xlw/ArgList.h>"// Include file
               );



///////////////////////////////////////////////////////////////////////////////////////////
///////////////    Managed Types
namespace Managed
{
TypeRegistry<managed>::Helper datetimereg("DateTime", // New type
               "double",    // Old type
               "DateTime::FromOADate",// Converter name
               false,        // Is a method
               false,        // Takes identifier
               ""           // No key
               "",        // "<xlw/ArgList.h>"// Include file,
			   "System" // .NET namespace 
               );


}
}

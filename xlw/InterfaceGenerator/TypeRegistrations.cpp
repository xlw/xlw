//
//
//
//                                        TypeRegistrations.cpp
//
/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2007, 2008 Eric Ehlers
 
 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/
 
 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net
 
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/
#ifdef _MSC_VER
#if _MSC_VER < 1250
#pragma warning(disable:4786)
#pragma warning(disable:4503)
#endif
#endif
#include "TypeRegister.h"

namespace
{
// fundamental types

TypeRegistry::Helper XlfOperReg("XlfOper", // New type
               "LPXLFOPER",     // Old type
               "",              // Converter name, we just pass into the constructor as a declaration
               false,           // Is a method
               false,           // Takes identifier
               "XLF_OPER"       // Type code
               );

TypeRegistry::Helper doubleFundamentalReg("double", // New type
               "double",        // Old type, EXCEL understands doubles so this is simply a copy
               "",              // Converter name, we just pass into the constructor as a declaration
               false,           // Is a method
               false,           // Takes identifier
               "B"              // Type code
               );

TypeRegistry::Helper arrayFundamentalReg("NEMatrix", // New type
               "LPXLARRAY",     // Old type
               "GetMatrix",     // Converter name, we just pass into the constructor as a declaration
               false,           // Is a method
               false,           // Takes identifier
               "K",             // Type code
               "<xlw/xlarray.h>"// Include file
               );

TypeRegistry::Helper shortreg("short", // New type
               "XlfOper",       // Old type
               "AsShort",       // Converter name
               true,            // Is a method
               true,            // Takes identifier
               "XLF_OPER"       // Type code
               );

TypeRegistry::Helper arrayreg("MyArray", // New type
               "XlfOper",       // Old type
               "AsArray",       // Converter name
               true,            // Is a method
               true,            // Takes identifier
               "XLF_OPER"       // Type code
               );

TypeRegistry::Helper matrixreg("MyMatrix", // New type
               "XlfOper",       // Old type
               "AsMatrix",      // Converter name
               true,            // Is a method
               true,            // Takes identifier
               "XLF_OPER"       // Type code
               );

TypeRegistry::Helper cellsreg("CellMatrix", // New type
               "XlfOper",       // Old type
               "AsCellMatrix",  // Converter name
               true,            // Is a method
               true,            // Takes identifier
               "XLF_OPER"       // Type code
               );

TypeRegistry::Helper stringreg("string", // New type
               "XlfOper",       // Old type
               "AsString",      // Converter name
               true,            // Is a method
               true,            // Takes identifier
               "XLF_OPER"       // Type code
               );

TypeRegistry::Helper sstringreg("std::string", // New type
               "XlfOper",       // Old type
               "AsString",      // Converter name
               true,            // Is a method
               true,            // Takes identifier
               "XLF_OPER"       // Type code
               );

// Special processing of std::wstring depending on Excel version
TypeRegistry::Helper swstringreg("XLWSTR", // New type - a typedef to void*
               "XLWSTR",        // Old type
               "",              // Converter name
               false,           // Is a method
               false,           // Takes identifier
               "XLW_WSTR"       // Type code
               );

TypeRegistry::Helper boolreg("bool", // New type
               "XlfOper",       // Old type
               "AsBool",        // Converter name
               true,            // Is a method
               true,            // Takes identifier
               "XLF_OPER"       // Type code
               );

// Usually XlfOper is registered as type XLF_OPER   which equates to either P (OPER)   or Q (OPER12)
// Here    XlfOper is registered as type XLF_XLOPER which equates to either R (XLOPER) or U (XLOPER12)
TypeRegistry::Helper RefTestReg("reftest", // New type
               "LPXLFOPER",     // Old type
               "",              // Converter name, we just pass into the constructor as a declaration
               false,           // Is a method
               false,           // Takes identifier
               "XLF_XLOPER"     // Type code
               );

// extended types

TypeRegistry::Helper ULreg("unsigned long", // New type
               "double",        // Old type
               "static_cast<unsigned long>", // Converter name
               false,           // Is a method
               false            // Takes identifier
               );

TypeRegistry::Helper intreg("int", // New type
               "double",        // Old type
               "static_cast<int>", // Converter name
               false,           // Is a method
               false            // Takes identifier
               );

// Special processing of std::wstring depending on Excel version
TypeRegistry::Helper wstrreg("std::wstring", // New type
               "XLWSTR",        // Old type
               "voidToWstr",    // Converter name
               false,           // Is a method
               false            // Takes identifier
               );

TypeRegistry::Helper DONreg("DoubleOrNothing", // New type
               "CellMatrix",    // Old type
               "DoubleOrNothing", // Converter name
               false,           // Is a method
               true             // Takes identifier 
               );

TypeRegistry::Helper arglistreg("ArgumentList", // New type
               "CellMatrix",    // Old type
               "ArgumentList",  // Converter name
               false,           // Is a method
               true,            // Takes identifier 
               "",              // No key
               "<xlw/ArgList.h>"// Include file
               );

TypeRegistry::Helper payoffreg("Wrapper<PayOff>", // New type
               "ArgumentList",  // Old type
               "GetFromFactory<PayOff>", // Converter name
               false,           // Is a method
               false,           // Takes identifier 
               "" ,             // No key
              "<xlw/ArgListFactory.h>" // Include file
               );

}

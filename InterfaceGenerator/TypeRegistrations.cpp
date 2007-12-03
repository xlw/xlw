//
//
//
//										TypeRegistrations.cpp
//
/*
 Copyright (C) 2006 Mark Joshi
 
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

TypeRegistry::Helper XlfOperReg("XlfOper", // new type
			   //"LPXLOPER", // old type
			   "LPXLFOPER", // old type
			   "", // converter name, we just pass into the constructor as a declaration
			   false, // is a method
			   false // takes identifier
			   );

TypeRegistry::Helper doubleFundamentalReg("double", // new type
			   "double", // old type, EXCEL understands doubles so this is simply a copy
			   "", // converter name, we just pass into the constructor as a declaration
			   false, // is a method
			   false, // takes identifier
			   "B"
			   );

TypeRegistry::Helper arrayFundamentalReg("NEMatrix", // new type
			   "LPXLARRAY", // old type, EXCEL understands doubles so this is simply a copy
			   "GetMatrix", // converter name, we just pass into the constructor as a declaration
			   false, // is a method
			   false, // takes identifier
			   "K",
			   "<xlw/xlarray.h>"
			   );

TypeRegistry::Helper shortreg("short", // new type
			   "XlfOper", // old type
			   "AsShort", // converter name
			   true, // is a method
			   true, // takes identifier
			   //"R" // should be empty unless OldType is XlfOper
			   "P" // should be empty unless OldType is XlfOper // Excel12 changes
			   );

/* we are passing doubles now directly rather than via LPXLOPERs
TypeRegistry::Helper doublereg("double", // new type
			   "XlfOper", // old type
			   "AsDouble", // converter name
			   true, // is a method
			   true, // takes identifier
			   "R" // should be empty unless OldType is XlfOper
			   );
*/

TypeRegistry::Helper arrayreg("MyArray", // new type
			   "XlfOper", // old type
			   "AsArray", // converter name
			   true, // is a method
			   true, // takes identifier
			   //"R" // should be empty unless OldType is XlfOper
			   "P" // should be empty unless OldType is XlfOper // Excel12 changes
			   );


TypeRegistry::Helper matrixreg("MyMatrix", // new type
			   "XlfOper", // old type
			   "AsMatrix", // converter name
			   true, // is a method
			   true, // takes identifier
			   "P" // should be empty unless OldType is XlfOper
			   );

TypeRegistry::Helper cellsreg("CellMatrix", // new type
			   "XlfOper", // old type
			   "AsCellMatrix", // converter name
			   true, // is a method
			   true, // takes identifier
			   "P" // should be empty unless OldType is XlfOper
			   );

TypeRegistry::Helper stringreg("string", // new type
			   "XlfOper", // old type
			   "AsString", // converter name
			   true, // is a method
			   true, // takes identifier
			   //"R" // should be empty unless OldType is XlfOper
			   "P" // should be empty unless OldType is XlfOper // Excel12 changes
			   );

TypeRegistry::Helper sstringreg("std::string", // new type
			   "XlfOper", // old type
			   "AsString", // converter name
			   true, // is a method
			   true, // takes identifier
			   //"R" // should be empty unless OldType is XlfOper
			   "P" // should be empty unless OldType is XlfOper // Excel12 changes
			   );


TypeRegistry::Helper boolreg("bool", // new type
			   "XlfOper", // old type
			   "AsBool", // converter name
			   true, // is a method
			   true, // takes identifier
			   //"R" // should be empty unless OldType is XlfOper
			   "P" // should be empty unless OldType is XlfOper // Excel12 changes
			   );

// extended types

TypeRegistry::Helper ULreg("unsigned long", // new type
			   "double", // old type
			   "static_cast<unsigned long>", // converter name
			   false, // is a method
			   false 
			   );


TypeRegistry::Helper intreg("int", // new type
			   "double", // old type
			   "static_cast<int>", // converter name
			   false, // is a method
			   false 
			   );


TypeRegistry::Helper DONreg("DoubleOrNothing", // new type
			   "CellMatrix", // old type
			   "DoubleOrNothing", // converter name
			   false, // is a method
			   true // takes identifier 
			   );


TypeRegistry::Helper arglistreg("ArgumentList", // new type
			   "CellMatrix", // old type
			   "ArgumentList", // converter name
			   false, // is a method
			   true, // takes identifier 
			   "", // no key
			   "<xlw/ArgList.h>"
			   );

TypeRegistry::Helper payoffreg("Wrapper<PayOff>", // new type
			   "ArgumentList", // old type
			   "GetFromFactory<PayOff>", // converter name
			   false, // is a method
			   false, // takes identifier 
			   "" , // no key
			  "<xlw/ArgListFactory.h>"
			   );


}

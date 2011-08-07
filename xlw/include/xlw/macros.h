/*
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 Jérôme Lecomte
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2009 Narinder S Claire

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef INC_macros_H
#define INC_macros_H

/*!
\file macros.h
\brief Some macros to consolidate XLW code.
*/

// $Id$

#include <xlw/XlfException.h>
#include <xlw/XlfExcel.h>
#include <xlw/CellMatrix.h>
#include <xlw/TempMemory.h>

#if defined(_MSC_VER)
#pragma once
#endif

//! Export flag.
/*!
Export macro that tells the compiler that the function is to be exported.
*/
#define EXCEL_EXPORT __declspec(dllexport)

//! Initialization macro
/*!
Use this macro at the beginning of each user defined function implemented in
the addin.

If necessary, frees the internal buffer maintained by XlfExcel for heap memory
that is returned to Excel.
\sa XlfExcel
*/
#define EXCEL_BEGIN \
try \
{ \
    UsesTempMemory whileInScopeUseTempMemory;

/*! \defgroup cleanup_macros Cleanup Macros
Use a cleanup macro at the end of each user defined function implemented in the
addin.  Choose the variation of EXCEL_END* which corresponds to the data type
of the function's return value.

The cleanup macros catch any exception that was thrown during execution of the
user defined addin function.

The catch clause adheres to the following standards:
- Test first for exceptions which require the framework to return to excel
  immediately (namely coerce, uncalculated cell, and abort). If caught, returns
  zero which is interpreted by Excel as \#NULL!.
- Catch runtime errors and return string to Excel
- Catch strings and echo them
- Catch const char * values and echo them
- Catch cell matrix and echo it, useful for complicated errors
- Catch any exception of unknown type. Return \#VALUE! error.

You can add your own exceptions here.  Note that changes to this file trigger a
full recompilation of all addin code.

\warning Excel-specific functions such as xlAutoOpen(), xlAddInManagerInfo(),
etc. must not be wrapped in EXCEL_BEGIN/EXCEL_END.  EXCEL_END is capable of
generating return values which Excel does not expect to receive from such
functions.  EXCEL_BEGIN/EXCEL_END are for use only in user defined addin
functions.
*/
//@{
//! Cleanup macro for function with return type XlfOper
#define EXCEL_END \
} catch (XlfException&) { \
    return 0; \
} catch (std::exception& error){\
    return XlfOper(error.what());\
} catch (std::string& error){\
    return XlfOper(error);\
} catch (const char* error){\
    return XlfOper(error);\
} catch (const CellMatrix& error){\
    return XlfOper(error);\
} catch (...) { \
    return XlfOper::Error(xlerrValue); \
}
//! Cleanup macro for function with return type XlfOper4
#define EXCEL_END_4 \
} catch (XlfException&) { \
    return 0; \
} catch (std::exception& error){\
    return XlfOper4(error.what());\
} catch (std::string& error){\
    return XlfOper4(error);\
} catch (const char* error){\
    return XlfOper4(error);\
} catch (const CellMatrix& error){\
    return XlfOper4(error);\
} catch (...) { \
    return XlfOper4::Error(xlerrValue); \
}
//! Cleanup macro for function with return type XlfOper12
#define EXCEL_END_12 \
} catch (XlfException&) { \
    return 0; \
} catch (std::exception& error){\
    return XlfOper12(error.what());\
} catch (std::string& error){\
    return XlfOper12(error);\
} catch (const char* error){\
    return XlfOper12(error);\
} catch (const CellMatrix& error){\
    return XlfOper12(error);\
} catch (...) { \
    return XlfOper12::Error(xlerrValue); \
}
//! Cleanup macro for command with return type int
#define EXCEL_END_CMD \
} catch (XlfException&) { \
    return 0; \
} catch (std::exception&){\
    return 0;\
} catch (std::string&){\
    return 0;\
} catch (const char*){\
    return 0;\
} catch (const CellMatrix&){\
    return 0;\
} catch (...) { \
    return 0; \
} \
return 1;

//! Cleanup macro for command with return type LPXLARRAY
#define EXCEL_END_ARRAY \
} catch (XlfException&) { \
    return 0; \
} catch (std::exception&){\
    return 0;\
} catch (std::string&){\
    return 0;\
} catch (const char*){\
    return 0;\
} catch (const CellMatrix&){\
    return 0;\
} catch (...) { \
    return 0; \
} \

//@}
#endif


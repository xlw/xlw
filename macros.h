// Copyright (c) 1998-2001
// Jerome Lecomte
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation. This software is freely provided "as is" 
// without express or implied warranty.

#ifndef INC_macros_H
#define INC_macros_H

/*!
\file macros.h
\brief I am not a big fan of macros, but these make life easier.
*/

#include "XlfException.h"
#include "XlfExcel.h"

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
Macros to be inserted at the begining and end of *each* C function
to be exported to excel.
 
Frees the internal buffer if needed of XlfExcel used to return 
heap allocated data to Excel.
\sa XlfExcel
*/
#define EXCEL_BEGIN XlfExcel::Instance().FreeMemory(); \
try \
{

//! Clean up macro
/*!
Macro to be inserted at the end of *each* C function to be exported
to excel.
 
Catch exception in C function calls
Catching rules are as follow :
- try first to catch excel exception that need the framework to return to excel
asap (namely coerce, uncalculated cell, and abort). If catched, returns #NULL!.
- catch all other kind of exception. Return #VALUE! error if possible otherwise 
returns #NULL!.

You could easily add your own exception here. Note that it causes all your
interface to recompile though.
*/
#define EXCEL_END } catch (XlfException&) \
{ return 0; } \
// catch (.../* or your base exception here */) \
// { \
//   try \
//   { \
//     return XlfException::Value(); \
//   } \
// }

#endif
// Copyright (c) 1998-2001
// Jerome Lecomte
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation. This software is freely provided "as is" 
// without express or implied warranty.

#ifndef INC_EXCEL32_API_H
#define INC_EXCEL32_API_H

/*!
\file EXCEL32_API.h
\brief Defines the EXCEL32_API macro that flags exported classes of the framework.
*/

#include "port.h"

#if defined(_MSC_VER)
#pragma once
#endif

#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif

#ifdef _DLL
#ifdef EXCEL32_EXPORTS
#define EXCEL32_API PORT_EXPORT_SYMBOL
#else
#define EXCEL32_API PORT_IMPORT_SYMBOL
#endif
#else
#define EXCEL32_API
#endif

#endif
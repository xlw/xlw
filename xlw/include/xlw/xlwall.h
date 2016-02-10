/*
 Copyright (C) 2016 John Adcock

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

// $Id: xlwall.h 1280 2011-08-07 11:33:52Z adcockj $

#ifndef INC_XLWALL_H
#define INC_XLWALL_H

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "../../src/ArgList.cpp"
#include "../../src/DoubleOrNothing.cpp"
#include "../../src/HiResTimer.cpp"
#include "../../src/MJCellMatrix.cpp"
#include "../../src/NCmatrices.cpp"
#include "../../src/PascalStringConversions.cpp"
#include "../../src/PathUpdater.cpp"
#include "../../src/TempMemory.cpp"
#include "../../src/Win32StreamBuf.cpp"
#include "../../src/xlcall.cpp"
#include "../../src/XlfAbstractCmdDesc.cpp"
#include "../../src/XlfArgDesc.cpp"
#include "../../src/XlfArgDescList.cpp"
#include "../../src/XlfCmdDesc.cpp"
#include "../../src/XlfExcel.cpp"
#include "../../src/XlfFuncDesc.cpp"
#include "../../src/XlfOperImpl.cpp"
#include "../../src/XlfOperProperties.cpp"
#include "../../src/XlfRef.cpp"
#include "../../src/XlfServices.cpp"
#include "../../src/XlFunctionRegistration.cpp"
#include "../../src/XlOpenClose.cpp"

#endif
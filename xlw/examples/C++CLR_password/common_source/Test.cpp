/*

 Copyright (C) 2009 2011 Narinder S Claire

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include "cppinterface.h"
using namespace System;


bool IsAuthenticated();
void authenticate();

void checkAuthenticated()
{
	if(!IsAuthenticated())
	{
		throw("NOT AUTHENTICATED TO USE THIS XLL");
	}
}

double // Echoes Date
EchoDate(
		 DateTime date // the Date
		 )
{
	checkAuthenticated();

	return date.ToOADate();
}


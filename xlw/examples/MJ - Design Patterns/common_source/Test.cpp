
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

#include "Test.h"
#include <ctime>
#include <windows.h>
#include<xlw/XlfExcel.h>
#include<xlw/XlOpenClose.h>
#include<xlw/XlfServices.h>

double // evaluate pay--off
PayOffEvaluation(const Wrapper<PayOff>& OptionPayOff // table for payoff
               , double Spot // point for evaluation
            )
{
    return (*OptionPayOff)(Spot);
}

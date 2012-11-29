/*
 Copyright (C) 2011 Mark P Owen

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

using System;
using System.Collections.Generic;
using ReflectionFactory;
using ReflectionFactory.NET.PayOff;
using xlwDotNet;
using xlwDotNet.xlwTypes;

namespace TypeRegDemo
{
    public class Class1
    {
        [ExcelExport("Evaluate Pay-Off")]
        public static double PayOffEvaluation(
            [Parameter("PayOff")] ArgumentList payOff,
            [Parameter("Point for evaluation")] double spot)
        {
            PayOffBase payOffBase = Factory.GetInstance<PayOffBase>(payOff);
            // Note: In the above line there is an implicit conversion of payOff
            // from type ArgumentList to type Dictionary<String, Object>.
            // We could write this conversion explicitly in two steps:
            // Dictionary<String, Object> payOffDictionary = payOff;
            // PayOffBase payOffBase = Factory.GetInstance<PayOffBase>(payOffDictionary);
            return payOffBase.Payoff(spot);
        }

    }
}


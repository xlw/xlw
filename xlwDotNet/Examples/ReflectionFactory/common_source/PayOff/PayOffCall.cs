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

namespace ReflectionFactory.NET.PayOff
{
    [RegisterClass("Call")]
    class PayOffCall : PayOffBase
    {

        private readonly double _strike;

        [RegisterConstructor]
        public PayOffCall([FactoryParameter("Strike")] double strike)
        {
            _strike = strike;
        }

        public override double Payoff(double spot)
        {
            return spot - _strike > 0.0 ? spot - _strike : 0.0;
        }
    }
}

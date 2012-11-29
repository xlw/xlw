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
    [RegisterClass("Spread")]
    class PayOffSpread : PayOffBase
    {

        private readonly PayOffBase _payOff1, _payOff2;
        private readonly double _volume1, _volume2;

        [RegisterConstructor]
        public PayOffSpread(
            [FactoryParameter("Option1")] PayOffBase payOff1,
            [FactoryParameter("Volume1")] double volume1,
            [FactoryParameter("Option2")] PayOffBase payOff2,
            [FactoryParameter("Volume2")] double volume2)
        {
            _payOff1 = payOff1;
            _volume1 = volume1;
            _payOff2 = payOff2;
            _volume2 = volume2;
        }

        public override double Payoff(double spot)
        {
            return _volume1*_payOff1.Payoff(spot) + _volume2*_payOff2.Payoff(spot);
        }
    }
}

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

namespace ReflectionFactory
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct)]
    public class RegisterClassAttribute : Attribute
    {
        private string _registeredName;

        public string RegisteredName
        {
            private set
            {
                _registeredName = value.ToLower();
            }
            get
            {
                return _registeredName;
            }
        }

        public RegisterClassAttribute(string registeredName)
        {
            RegisteredName = registeredName;
        }

        public override string ToString()
        {
            return RegisteredName;
        }
    }
}

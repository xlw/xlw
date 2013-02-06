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
using System.Linq;
using System.Reflection;

namespace ReflectionFactory
{
    class Constructor
    {
        private readonly ConstructorInfo _constructorInfo;
        private readonly List<string> _parameterNames;
        private readonly List<Type> _parameterTypes;
        private readonly object[] _parameterValues;
        private readonly bool _match;
        private readonly bool _usedAllParameters;

        public bool Match
        {
            get { return _match; }
        }

        public bool UsedAllParameters
        {
            get { return _usedAllParameters; }
        }

        public Constructor(ConstructorInfo constructorInfo, Dictionary<string, object> parameterDictionary)
        {
            _constructorInfo = constructorInfo;
            _parameterNames = new List<string>();
            _parameterTypes = new List<Type>();
            _match = true;
            _usedAllParameters = true;

            // look through the constructor attributes for a RegisterConstructorAttribute
            // if this attribute exists, the factory is allowed to use the constructor.
            var registerConstructorAttributes = (RegisterConstructorAttribute[])_constructorInfo.GetCustomAttributes(typeof(RegisterConstructorAttribute), false);
            if (registerConstructorAttributes.Length == 0)
            {
                _match = false;
                _usedAllParameters = false;
                return;
            }

            // populate _parameterNames and _parameterTypes from _constructorInfo
            ParameterInfo[] parameterInfos = _constructorInfo.GetParameters();
            foreach (ParameterInfo parameterInfo in parameterInfos)
            {
                var factoryParameterAttributes = (FactoryParameterAttribute[])parameterInfo.GetCustomAttributes(typeof(FactoryParameterAttribute),false);

                
                string parameterName = parameterInfo.Name.ToLower(); // use raw parameter name
                if (factoryParameterAttributes.Length == 1) parameterName = factoryParameterAttributes[0].RegisteredName; // replace with friendly name for the parameter.
                else if (factoryParameterAttributes.Length > 1) throw new Exception("Parameter can have at most one FactoryParameterAttribute");
                _parameterNames.Add(parameterName);
                _parameterTypes.Add(parameterInfo.ParameterType);
            }

            // populate _parameterValues from parameterDictionary
            _parameterValues = new object[_parameterNames.Count];
            for (int i = 0; i < _parameterNames.Count; ++i)
            {
                string parameterName = _parameterNames[i].ToLower();
                Type parameterType = _parameterTypes[i];
                object parameterValue;
                if (parameterDictionary.ContainsKey(parameterName))
                {
                    parameterValue = parameterDictionary[parameterName];
                    if (!parameterType.IsInstanceOfType(parameterValue)) // Parameter parameterName has the wrong type
                    {
                        if (parameterValue.GetType() == typeof(Dictionary<string, object>))
                        {
                            var dictionary = (Dictionary<string, object>) parameterValue;
                            MethodInfo factoryGetInstanceMethod = typeof(Factory).GetMethod("GetInstance").MakeGenericMethod(parameterType);
                            try
                            {
                                parameterValue = factoryGetInstanceMethod.Invoke(null, new object[] { dictionary });
                            }
                            catch (TargetInvocationException e)
                            {
                                throw new Exception(e.InnerException.Message);
                            }
                        }
                        else
                            _match = false;
                    }
                }
                else // Can't find parameter parameterName in parameterDictionary
                {   
                    _match = false;
                    parameterValue = new object();
                }
                _parameterValues[i] = parameterValue;
            }

            // check to see whether all parameters in parameterDictionary have been used up
            foreach (KeyValuePair<string, object> entry in parameterDictionary.Where(entry => entry.Key != "name" && !_parameterNames.Contains(entry.Key)))
                _usedAllParameters = false;
        }

        public object GetInstance()
        {
            object instance;
            try
            {
                Type type = _constructorInfo.ReflectedType;
                instance = Activator.CreateInstance(type, _parameterValues);
            }
            catch (TargetInvocationException e)
            {
                throw new Exception(e.InnerException.Message);
            }
            return instance;
        }

        public bool Extends(Constructor constructor)
        {
            bool result = true;
            foreach (string name in constructor._parameterNames.Where(name => !_parameterNames.Contains(name)))
                result = false;
            return result;
        }
    }
}

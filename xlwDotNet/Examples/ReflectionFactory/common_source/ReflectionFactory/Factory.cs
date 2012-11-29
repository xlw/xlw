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
    /// <summary>
    /// A factory which uses lazy instantiation to produce registered objects at runtime.
    /// </summary>
    public static class Factory
    {
        /// <summary>
        /// Returns an instance of a derived class of the base class <!--typeparamref name="T" /-->.
        /// Constructor parameters for the derived class should be stored in the <paramref name="parameterDictionary"/>.
        /// </summary>
        /// <param name="parameterDictionary">
        /// A dictionary of parameters to be passed to subclass constructors, which are registered using <see cref="RegisterConstructorAttribute"/>.
        /// Keys should be named in accordance with the <see cref="FactoryParameterAttribute"/>.
        /// </param>
        /// <returns></returns>
        public static T GetInstance<T>(Dictionary<string, object> parameterDictionary)
        {
            var name = (string)parameterDictionary["name"];
            Assembly assembly = Assembly.GetAssembly(typeof(T));

            // loop through all the types in the assembly
            Type[] types = assembly.GetTypes();
            bool foundRegisteredClass = false;
            Type matchingType = null;
            foreach (Type type in types)
            {
                // type should be derived from base class T, or should implement interface T.
                if (!typeof(T).IsAssignableFrom(type)) continue;

                var registerClassAttributes = (RegisterClassAttribute[])type.GetCustomAttributes(typeof(RegisterClassAttribute),false);
                if (registerClassAttributes.Any(registerClassAttribute => registerClassAttribute.RegisteredName == name))
                    foundRegisteredClass = true;

                if (!foundRegisteredClass) continue;
                matchingType = type;
                break;
            }

            if (matchingType == null)
                throw new Exception("Factory can't find a class with the registered name " + name + " in the assembly " + assembly.GetName() + ".");

            // look through the class's constructors
            ConstructorInfo[] constructorInfos = matchingType.GetConstructors();
            var matchingConstructors = new List<Constructor>();
            Constructor constructor;
            foreach (ConstructorInfo constructorInfo in constructorInfos)
            {
                constructor = new Constructor(constructorInfo, parameterDictionary);
                if (!constructor.Match)
                    continue;
                bool addConstructor = true;
                foreach (Constructor matchingConstructor in matchingConstructors)
                {
                    if (matchingConstructor.Extends(constructor))
                    {
                        addConstructor = false; // we already have a better constructor
                        break;
                    }
                    if (constructor.Extends(matchingConstructor)) matchingConstructors.Remove(matchingConstructor); // matchingConstructor is superceded by constructor
                }
                if (addConstructor)
                    matchingConstructors.Add(constructor);
            }

#if strict
            if (!constructor.UsedAllParameters)
                throw new Exception("Not used all parameters");
#endif

            if (matchingConstructors.Count == 0)
                throw new Exception("Couldn't find a constructor which matches the given parameters");
            if (matchingConstructors.Count > 1)
                throw new Exception("More than one constructor matches the given parameters");
            
            constructor = matchingConstructors[0];
            
            return (T)constructor.GetInstance();
        }

    }
}

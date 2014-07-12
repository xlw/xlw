 
/*
 Copyright (C) 2008 2009 2010 2011 Narinder S Claire

 This file is part of XLWDOTNET, a free-software/open-source C# wrapper of the
 Excel C API - http://xlw.sourceforge.net/
 
 XLWDOTNET is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/
 
 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net
 
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

        using namespace System;
        using namespace System::Reflection;
        using namespace System::IO;

        ref class AssemblyFinder
        {
        public:

           static Assembly^ MyResolveEventHandler( Object^ sender, ResolveEventArgs^ args )
           {
	         Assembly^ thisAssembly = Assembly::GetExecutingAssembly();
	         String^ thisPath = thisAssembly->Location;    
	         String^ directory = Path::GetDirectoryName(thisPath); 
	         String^ pathToManagedAssembly = Path::Combine(directory, args->Name->Split(',')[0]+".dll");    
	         if (File::Exists(pathToManagedAssembly)) 
             {
                Assembly^ newAssembly = Assembly::LoadFile(pathToManagedAssembly);   
	            return newAssembly;
             }
             return nullptr;
           }
        };

        struct AssembleyFinderInitialiser {

            AssembleyFinderInitialiser()
	        {
	            AppDomain^ currentDomain = AppDomain::CurrentDomain;
                currentDomain->AssemblyResolve += gcnew ResolveEventHandler( AssemblyFinder::MyResolveEventHandler ); 
	        }
        };
        namespace 
        {
          AssembleyFinderInitialiser theFinder;
        }
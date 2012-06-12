/*
 Copyright (C) 2008 2009 2012 Narinder S Claire

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


#ifndef  XLW_TYPE_BASE_CLASS_H
#define XLW_TYPE_BASE_CLASS_H


using namespace System;
namespace xlwDotNet
{
    namespace xlwTypes
    {
        template<class T>
        public ref class xlwTypebaseClass
        {
        public :
            xlwTypebaseClass(IntPtr theManagedPointer, bool owned_):
                theInner((T *)(theManagedPointer.ToPointer())),owned(owned_){}


            xlwTypebaseClass(const T * theObject, bool owned_):
                theInner((T *)(theObject)),owned(owned_){}

            property void * inner
            {
                void * get()
                {
                    return (void *)theInner;
                }
            }
			~xlwTypebaseClass()
            {
				this->!xlwTypebaseClass();
			}

			// This is the FINALIZER !!! The GC calls THIS NOT the destructor
			// trying to clean up in the destructor will lead to momeory leaks

            !xlwTypebaseClass()
            {
                if(owned)
				{
				 
					delete theInner;
				}
                theInner = 0;owned = false;
            }
            T * theInner;
            bool owned;



        };
    }
}

#endif 
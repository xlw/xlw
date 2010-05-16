/*
 Copyright (C) 2008 2009  Narinder S Claire

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

#ifndef XLW_DOT_NET_MYARRAY_H
#define XLW_DOT_NET_MYARRAY_H 


using namespace System;
#include<xlw/MyContainers.h>
#include"xlwTypeBaseClass.h"
namespace xlwDotNet 
{
	namespace xlwTypes 
	{
		public ref class MyArray :public xlwTypebaseClass<xlw::MyArray>
		{

		public:
			MyArray(IntPtr theRealThing):
			  xlwTypebaseClass<xlw::MyArray>(theRealThing,false){}

			MyArray(const MyArray^ theOther):
			    xlwTypebaseClass<xlw::MyArray>(new xlw::MyArray(*(theOther->theInner)),true){}

			MyArray(int size_):
				xlwTypebaseClass<xlw::MyArray>(new xlw::MyArray(size_),true){}

			void clear(){theInner->clear();}

			property double default[int]
			{
				double get(int i) 
				{
					return theInner->operator[](i);
				}
				void set(int i,double val) 
				{
					theInner->operator[](i)=val;
				}
			}
			
		   property int size
			{
				int get() 
				{
					return theInner->size();
				}
			}	

		   operator array<double>^()
		   {
			   array<double>^ theCSArray =  gcnew array<double>(theInner->size());
			   for(size_t i(0);i<theInner->size();++i)theCSArray[i]=theInner->operator[](i);
			   return theCSArray;
		   }
		   static operator MyArray^(array<double>^ theCSArray)
		   {
			   MyArray^ theXLWArray =  gcnew MyArray(theCSArray->Length);
			   for(int i(0);i<theCSArray->Length;++i)theXLWArray->theInner->operator[](i)=theCSArray[i];
			   return theXLWArray;

		   }
		   static void *getInner (MyArray^ theArray){return theArray->theInner;}
		};

	}
}
#endif

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


using namespace System;
using namespace System::Collections::Generic;
using namespace Runtime::InteropServices;
#include<xlw/ArgList.h>
#include"xlwTypeBaseClass.h"
#include"managedCellMatrix.h"

std::string CLR2CPP(String^ clrString);

namespace xlwDotNet 
{
	namespace xlwTypes 
	{
		public ref class ArgumentList :public xlwTypebaseClass<xlw::ArgumentList>
		{

		public:
			ArgumentList(IntPtr theRealThing):
			  xlwTypebaseClass<xlw::ArgumentList>(theRealThing,false){}

		   ArgumentList(CellMatrix^ cells,String^ ErrorIdentifier):
			  xlwTypebaseClass<xlw::ArgumentList>(new xlw::ArgumentList(*(cells->theInner),
				          (const char*)(Marshal::StringToHGlobalAnsi(ErrorIdentifier)).ToPointer()),true){}


            ArgumentList(String^ name):
			  xlwTypebaseClass<xlw::ArgumentList>(new xlw::ArgumentList(
				          (const char*)(Marshal::StringToHGlobalAnsi(name)).ToPointer()),true){}

		    ArgumentList(ArgumentList^ theArgumentList):
			  xlwTypebaseClass<xlw::ArgumentList>(new xlw::ArgumentList(*theArgumentList->theInner),true){}


			  //const std::vector<std::pair<std::string, ArgumentType> >& GetArgumentNamesAndTypes() const;

		enum class ArgumentType
			 {
				 string  = xlw::ArgumentList::string,
				 number  = xlw::ArgumentList::number,
				 vector  = xlw::ArgumentList::vector,
				 matrix  = xlw::ArgumentList::matrix,
				 boolean = xlw::ArgumentList::boolean,
				 list    = xlw::ArgumentList::list, 
				 cells   = xlw::ArgumentList::cells
			};
		Dictionary<String^,ArgumentType>^ GetArgumentNamesAndTypes()
		{
			const std::vector<std::pair<std::string, xlw::ArgumentList::ArgumentType> >& theRawDict = theInner->GetArgumentNamesAndTypes();
			Dictionary<String^,ArgumentType>^ theDict =  gcnew Dictionary<String^,ArgumentType>();
			for(size_t i(0); i<theRawDict.size(); ++i)
			{
				theDict->Add(gcnew String(theRawDict[i].first.c_str()),ArgumentType(theRawDict[i].second));
			}
			return theDict;
		}

			String^ GetStructureName()
			{
				return gcnew String(theInner->GetStructureName().c_str());
			}

			String^ GetStringArgumentValue(String^ ArgumentName)
			{
				return gcnew String( theInner->GetStringArgumentValue(CLR2CPP(ArgumentName)).c_str());
			}

			UInt64 GetULArgumentValue(String^ ArgumentName)
			{
				return  theInner->GetULArgumentValue(CLR2CPP(ArgumentName));
			}

			MyArray^ GetArrayArgumentValue(String^ ArgumentName)
			{
				MyArray^ result =  gcnew MyArray(IntPtr((void*)&theInner->GetArrayArgumentValue(CLR2CPP(ArgumentName))));
				return gcnew MyArray(result);
			}
			MyMatrix^ GetMatrixArgumentValue(String^ ArgumentName)
			{
				MyMatrix^ result =  gcnew MyMatrix(IntPtr((void*)&theInner->GetMatrixArgumentValue(CLR2CPP(ArgumentName))));
				return gcnew MyMatrix(result);
			}

			CellMatrix^ GetCellsArgumentValue(String^ ArgumentName)
			{
				CellMatrix^ result =  gcnew CellMatrix(IntPtr((void*)&theInner->GetCellsArgumentValue(CLR2CPP(ArgumentName))));
				return gcnew CellMatrix(result);
			}
			ArgumentList^ GetArgumentListArgumentValue(String^ ArgumentName)
			{
				ArgumentList^ result =  gcnew ArgumentList(IntPtr((void*)&theInner->GetArgumentListArgumentValue(CLR2CPP(ArgumentName))));
				return gcnew ArgumentList(result);
			}
			double GetDoubleArgumentValue(String^ ArgumentName)
			{
				return  theInner->GetDoubleArgumentValue(CLR2CPP(ArgumentName));
			}
			bool GetBoolArgumentValue(String^ ArgumentName)
			{
				return  theInner->GetBoolArgumentValue(CLR2CPP(ArgumentName));
			}

			bool IsArgumentPresent(String^ ArgumentName) 
			{
				return  theInner->IsArgumentPresent(CLR2CPP(ArgumentName));
			}




			void add(String ^ ArgumentName, String ^ value)
			{
				theInner->add(CLR2CPP(ArgumentName),CLR2CPP(value));
			}

			
			void add(String ^ ArgumentName, MyArray^ value)
			{
				theInner->add(CLR2CPP(ArgumentName),*value->theInner);
			}
			void add(String ^ ArgumentName, MyMatrix^ value)
			{
				theInner->add(CLR2CPP(ArgumentName),*value->theInner);
			}
			void add(String ^ ArgumentName, CellMatrix^ value)
			{
				theInner->add(CLR2CPP(ArgumentName),*value->theInner);
			}
			void add(String ^ ArgumentName, double value)
			{
				theInner->add(CLR2CPP(ArgumentName),value);
			}
			void add(String ^ ArgumentName, bool value)
			{
				theInner->add(CLR2CPP(ArgumentName),value);
			}

			CellMatrix^ AllData()
			{
				xlw::CellMatrix temp = theInner->AllData();
				CellMatrix^ result = gcnew CellMatrix( IntPtr((void*)&temp));
				return gcnew CellMatrix(result);
			}




		};
	}
}


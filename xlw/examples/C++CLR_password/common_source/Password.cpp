/*

 Copyright (C) 2009 2011 Narinder S Claire

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include "Password.h"


namespace 
{
	bool IsAuthenticated_flag = false;
}
bool IsAuthenticated()
{
	return IsAuthenticated_flag;
}

void authenticate()
{

	ExampleXll::Password^ theForm = gcnew ExampleXll::Password();
	theForm->ShowDialog();
	IsAuthenticated_flag = false;
	if(theForm->DialogResult == System::Windows::Forms::DialogResult::OK)
	{
		if (theForm->getUserName() == L"XLW")
		{
			if (theForm->getPassWord() == L"XLW")
			{
				IsAuthenticated_flag=true;
			}
		}
	}

	theForm->Close();

}


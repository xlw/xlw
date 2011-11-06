/*
 Copyright (C) 2008 2009  Narinder S Claire
 Copyright (C) 2011 Mark P Owen

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

namespace xlwDotNet {
[AttributeUsage(AttributeTargets::Method)]
public ref class ExcelExportAttribute : Attribute
{
private:
	initonly String^ _description;
    initonly bool _volatileFlag;
    initonly bool _timeFlag;
    initonly bool _threadSafeFlag;
    initonly bool _xlmCommandFlag;

public:
    property String^ Description
	{
		String^ get() { return _description; }
	}

	property bool VolatileFlag
	{
		bool get() { return _volatileFlag; }
	}

	property bool TimeFlag
	{
		bool get() { return _timeFlag; }
	}

	property bool ThreadSafeFlag
	{
		bool get() { return _threadSafeFlag; }
	}

	property bool XLMCommandFlag
	{
		bool get() { return _xlmCommandFlag; }
	}

	ExcelExportAttribute(String^ description)
	{
		_description = description;
        _volatileFlag = false;
        _timeFlag = false;
        _threadSafeFlag = false;
        _xlmCommandFlag = false;
	}

	ExcelExportAttribute(String^ description, bool volatileFlag)
	{
		_description = description;
        _volatileFlag = volatileFlag;
        _timeFlag = false;
        _threadSafeFlag = false;
        _xlmCommandFlag = false;
	}

    ExcelExportAttribute(String^ description, bool volatileFlag, bool timeFlag)
	{
		_description = description;
        _volatileFlag = volatileFlag;
        _timeFlag = timeFlag;
        _threadSafeFlag = false;
        _xlmCommandFlag = false;
	}

    ExcelExportAttribute(String^ description, bool volatileFlag, bool timeFlag, bool threadSafeFlag)
    {
        _description = description;
        _volatileFlag = volatileFlag;
        _timeFlag = timeFlag;
        _threadSafeFlag = threadSafeFlag;
        _xlmCommandFlag = false;
    }
};
}

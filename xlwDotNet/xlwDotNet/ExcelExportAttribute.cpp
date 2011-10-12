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

namespace xlwDotNet {
    [AttributeUsage(AttributeTargets::Method)]
public ref class ExcelExportAttribute: Attribute
{
public:
    String^ description;
    bool volatileFlag;
    bool timeFlag;
    bool threadSafeFlag;
    bool xlmCommandFlag;
    ExcelExportAttribute(String^ description_)
    {
        description = description_;
        volatileFlag = false;
        timeFlag = false;
        threadSafeFlag = false;
        xlmCommandFlag = false;
    }

    ExcelExportAttribute(String^ description_, bool volatileFlag_)
    {
        description = description_;
        volatileFlag = volatileFlag_;
        timeFlag = false;
        threadSafeFlag = false;
        xlmCommandFlag = false;
    }

    ExcelExportAttribute(String^ description_, bool volatileFlag_, bool timeFlag_)
    {
        description = description_;
        volatileFlag = volatileFlag_;
        timeFlag = timeFlag_;
        threadSafeFlag = false;
        xlmCommandFlag = false;
    }

    ExcelExportAttribute(String^ description_, bool volatileFlag_, bool timeFlag_, bool threadSafeFlag_)
    {
        description = description_;
        volatileFlag = volatileFlag_;
        timeFlag = timeFlag_;
        threadSafeFlag = threadSafeFlag_;
        xlmCommandFlag = false;
    }
};
[AttributeUsage(AttributeTargets::Parameter)]
public ref class ParameterAttribute: Attribute
{
public:
    String^ description;
    ParameterAttribute(String^ description_)
    {
        description = description_;
    }
};
}

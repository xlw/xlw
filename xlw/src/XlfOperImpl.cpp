
/*
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2011 John Adcock

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <xlw/XlfOperImpl.h>
#include <xlw/XlfExcel.h>
#include <xlw/XlfException.h>
#include <stdexcept>
#include <assert.h>

namespace
{
    std::string CombineErrorString(const char* Msg, const char* ErrorId, const char* Identifier)
    {
        std::string result(Msg);
        if(ErrorId)
        {
            result += ", ";
            result += ErrorId;
        }
        if(Identifier)
        {
            result += " ";
            result += Identifier;
        }
        return result;
    }
}

namespace xlw
{
    void XlfOperImpl::ThrowOnError(int xlret, const char* ErrorId, const char* Identifier)
    {
        if (xlret & xlretUncalced)
            throw XlfExceptionUncalculated();
        if (xlret & xlretAbort)
            throw XlfExceptionAbort();
        if (xlret & xlretStackOvfl)
            throw XlfExceptionStackOverflow();
        if (xlret & xlretInvXloper)
            THROW_XLW(CombineErrorString("invalid OPER structure (memory could be exhausted)" , ErrorId, Identifier));
        if (xlret & xlretFailed)
            THROW_XLW(CombineErrorString("command failed" , ErrorId, Identifier));
        if (xlret & xlretInvCount)
            THROW_XLW(CombineErrorString("invalid number of arguments" , ErrorId, Identifier));
        if (xlret & xlretInvXlfn)
            THROW_XLW(CombineErrorString("invalid function number" , ErrorId, Identifier));
        if (xlret & xlRetInvAsynchronousContext)
            THROW_XLW(CombineErrorString("invalid asynch conext" , ErrorId, Identifier));
        if (xlret & xlretNotClusterSafe)
            THROW_XLW(CombineErrorString("function not cluster safe" , ErrorId, Identifier));
    }

	void XlfOperImpl::MissingOrEmptyError(int xltype, const char* ErrorId, const char* identifier)
    {
        if (xltype == xltypeMissing)
            THROW_XLW(CombineErrorString("parameter is missing" , ErrorId, identifier));
        if (xltype == xltypeErr)
            THROW_XLW(CombineErrorString("parameter is error" , ErrorId, identifier));
        if (xltype == xltypeNil)
            THROW_XLW(CombineErrorString("parameter is nil" , ErrorId, identifier));
		ThrowOnError(xlretInvXloper, ErrorId, identifier);
	}

    std::string XlfOperImpl::XlTypeToString(int xlType)
    {
        DWORD type = xlType & 0xFFF;
        if (type == xltypeNum)
            return "xltypeNum";
        else if (type == xltypeStr)
            return "xltypeStr";
        else if (type == xltypeBool)
            return "xltypeBool";
        else if (type == xltypeRef)
            return "xltypeRef";
        else if (type == xltypeErr)
            return "xltypeErr";
        else if (type == xltypeMulti)
            return "xltypeMulti";
        else if (type == xltypeMissing)
            return "xltypeMissing";
        else if (type == xltypeNil)
            return "xltypeNil";
        else if (type == xltypeSRef)
            return "xltypeSRef";
        else if (type == xltypeInt)
            return "xltypeInt";
        else
            return "unknown";
    }
}





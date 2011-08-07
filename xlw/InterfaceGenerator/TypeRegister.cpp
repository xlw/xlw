
/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2011 Narinder S Claire

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include "TypeRegister.h"

template<>
bool TypeRegistry<null_type>::IsTypeRegistered(const std::string &id)const
{
	return  false;
}

template<>
bool TypeRegistry<native>::IsTypeRegistered(const std::string &id)const
{
	return  Registrations.find(id)!=Registrations.end() ;
}

template<>
bool TypeRegistry<managed>::IsTypeRegistered(const std::string &id)const
{
	return (Registrations.find(id)!=Registrations.end());
}

template<>
bool TypeRegistry<null_type>::IsOfBaseType(const std::string & id) const
{
	return false;
}

template<>
bool TypeRegistry<native>::IsOfBaseType(const std::string & id) const
{
    //if (id =="LPXLOPER")
    //    return true;

    if (id =="LPXLFOPER")
        return true;

    if (id == "double")
        return true;

    if (id == "LPXLARRAY")
        return true;

    if (id == "void")
        return true;

    return false;
}

template<>
bool TypeRegistry<managed>::IsOfBaseType(const std::string & id) const
{
	if (TypeRegistry<native>::Instance().IsTypeRegistered(id))
		return true;

    if (id =="std::string")
        return true;

    if (id == "CellMatrix")
        return true;

    return false;
}


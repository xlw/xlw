/*
 Copyright (C) 2006 Mark Joshi
 
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
#include "IncludeRegister.h"
void TypeRegistry::Register(const regData& data)
{
	Registrations.insert(std::make_pair(data.NewType,data));
}

TypeRegistry::Helper::Helper(std::string NewType,
			   std::string OldType,
			   std::string ConversionCommand,
			   bool IsAMethod,
			   bool TakesAnIdentifier,
			   std::string ExcelKey,
			   std::string IncludeFile)
			   : NewType_(NewType)
{
	regData data = { NewType,OldType,ConversionCommand,
													IsAMethod,TakesAnIdentifier,
													ExcelKey, IncludeFile};

	TypeRegistry::Instance().Register(data);
}

void TypeRegistry::BuildLists() const
{
	if (ListsBuilt)
		return;
	
	for (std::map<std::string,regData>::const_iterator it = Registrations.begin();
		it != Registrations.end(); ++it)
	{
		std::vector<std::string> chain(1);
		unsigned long pos =0;

		IncludeRegistry::Instance().Register(it->second.NewType,it->second.IncludeFile);

		chain[pos] = it->second.NewType;
		while (chain[pos] != "XlfOper")
		{
			std::map<std::string,regData>::const_iterator iter 
										= Registrations.find(chain[pos]);

			if (iter == Registrations.end())
				throw("broken chain "+chain[pos]+" " + it->first);
			
			chain.push_back(iter->second.OldType);
			++pos;

			if (pos >= 26)
				throw("26 deep type conversions suggests recursive loop");
		}

		DeductionChains.insert(std::make_pair(it->first,chain));
		
	}

	ListsBuilt=true;
}

const std::vector<std::string>& TypeRegistry::GetChain(std::string x) const
{
	BuildLists();
	std::map<std::string,std::vector<std::string> >::const_iterator iter 
		= DeductionChains.find(x);

	if (iter == DeductionChains.end())
		throw(" bad type "+x);

	for (unsigned long i=0; i < iter->second.size(); i++)
	{
		 IncludeRegistry::Instance().UseArg(iter->second[i]);
	}

	return iter->second;
}



const TypeRegistry::regData& TypeRegistry::GetRegistration(const std::string key) const
{

	std::map<std::string, regData>::const_iterator it = Registrations.find(key);

	if (it == Registrations.end())
		throw("unknown type "+key);

	return it->second;
}

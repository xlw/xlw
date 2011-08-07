//
//
//                            TypeRegister.h
//
//
/*
Copyright (C) 2006 Mark Joshi
Copyright (C) 2011 Narinder Claire

This file is part of XLW, a free-software/open-source C++ wrapper of the
Excel C API - http://xlw.sourceforge.net/

XLW is free software: you can redistribute it and/or modify it under the
terms of the XLW license.  You should have received a copy of the
license along with this program; if not, please email xlw-users@lists.sf.net

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the license for more details.
*/
#ifndef TYPE_REGISTER
#define TYPE_REGISTER

#include <string>
#include <map>
#include <vector>
#include "Singleton.h"
#include "IncludeRegister.h"

struct null_type{};
struct native{typedef null_type parent_type;};
struct managed{typedef native parent_type;};

template<class T>
class TypeRegistry : public Singleton<TypeRegistry<T> >
{
public:
	friend class Singleton<TypeRegistry<T> >;

	struct regData
	{
	public:
		regData(std::string NewType,
			std::string OldType,
			std::string Converter,
			bool IsAMethod,
			bool TakesIdentifier,
			std::string ExcelKey,
			std::string IncludeFile,
			std::string ManagedNameSpace);

		std::string NewType;
		std::string OldType;
		std::string Converter;
		bool IsAMethod;
		bool TakesIdentifier;
		std::string ExcelKey;
		std::string IncludeFile;
		std::string ManagedNameSpace;
	};

	void Register(const regData& data);

	void BuildLists() const;


	const regData& GetRegistration(const std::string key) const;

	const std::map<std::string, regData>& GetRegistrations() const
	{
		return Registrations;
	}
	const std::vector<std::string>& GetChain(std::string x) const;


	bool IsOfBaseType(const std::string & id) const;

	bool IsTypeRegistered(const std::string &id)const;

	class Helper
	{
	public:
		Helper(std::string NewType,
			std::string OldType,
			std::string ConversionCommand,
			bool IsAMethod,
			bool TakesAnIdentifier,
			std::string ExcelKey ="",
			std::string IncludeFile="",
			std::string ManagedNameSpace=""
			);
	private:

		std::string NewType_;
	};



private:

	std::map<std::string, regData> Registrations;

	mutable std::map<std::string, std::vector<std::string> > DeductionChains;

	mutable bool ListsBuilt;

};


template<class T>
TypeRegistry<T>::regData::regData(std::string NewType_,
	std::string OldType_,
	std::string Converter_,
	bool IsAMethod_,
	bool TakesIdentifier_,
	std::string ExcelKey_,
	std::string IncludeFile_,
	std::string ManagedNameSpace_)
	:
NewType(NewType_),OldType(OldType_),
	Converter(Converter_),
	IsAMethod(IsAMethod_),
	TakesIdentifier(TakesIdentifier_),
	ExcelKey(ExcelKey_),
	IncludeFile(IncludeFile_),
	ManagedNameSpace(ManagedNameSpace_)
{
}

template<class T>
void TypeRegistry<T>::Register(const regData& data)
{
	Registrations.insert(std::make_pair(data.NewType,data));
}

template<class T>
TypeRegistry<T>::Helper::Helper(std::string NewType,
	std::string OldType,
	std::string ConversionCommand,
	bool IsAMethod,
	bool TakesAnIdentifier,
	std::string ExcelKey,
	std::string IncludeFile,
	std::string ManagedNameSpace)
	: NewType_(NewType)
{
	regData data(NewType,OldType,ConversionCommand,
		IsAMethod,TakesAnIdentifier,
		ExcelKey, IncludeFile,ManagedNameSpace );

	TypeRegistry::Instance().Register(data);
}


template<class T>
void TypeRegistry<T>::BuildLists() const
{
	if (ListsBuilt)
		return;

	for (typename std::map<std::string,regData>::const_iterator it = Registrations.begin();
		it != Registrations.end(); ++it)
	{
		std::vector<std::string> chain(1);
		unsigned long pos =0;

		IncludeRegistry<T>::Instance().Register(it->second.NewType,it->second.IncludeFile);

		chain[pos] = it->second.NewType;
		while (!IsOfBaseType(chain[pos]))
		{
			typename std::map<std::string,regData>::const_iterator iter
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

template<class T>
const std::vector<std::string>& TypeRegistry<T>::GetChain(std::string x) const
{
	BuildLists();
	std::map<std::string,std::vector<std::string> >::const_iterator iter
		= DeductionChains.find(x);

	if (iter == DeductionChains.end())
	{
		if( ! TypeRegistry<typename T::parent_type>::Instance().IsTypeRegistered(x))
			throw(" bad type "+x);

		std::vector<std::string> chain(1);
		chain[0] = x;
		DeductionChains.insert(std::make_pair(x,chain));
		return DeductionChains.find(x)->second;

	}

	for (unsigned long i=0; i < iter->second.size(); i++)
	{
		IncludeRegistry<T>::Instance().UseArg(iter->second[i]);
	}

	return iter->second;
}

template<class T>
const typename TypeRegistry<T>::regData& TypeRegistry<T>::GetRegistration(const std::string key) const
{

	typename std::map<std::string, regData>::const_iterator it = Registrations.find(key);

	if (it == Registrations.end())
		throw("unknown type "+key);

	return it->second;
}


#endif

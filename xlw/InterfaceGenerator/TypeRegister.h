//
//
//                            TypeRegister.h
//
//
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
#ifndef TYPE_REGISTER
#define TYPE_REGISTER

#include <string>
#include <map>
#include <vector>
#include "Singleton.h"

class TypeRegistry : public Singleton<TypeRegistry>
{
public: 
    friend class Singleton<TypeRegistry>;
    
    struct regData
    {
    public:
        regData(std::string NewType,
                        std::string OldType,
                        std::string Converter,
                        bool IsAMethod,
                        bool TakesIdentifier,
                        std::string ExcelKey,
                        std::string IncludeFile);

        std::string NewType;
        std::string OldType;
        std::string Converter;
        bool IsAMethod;
        bool TakesIdentifier;
        std::string ExcelKey;
        std::string IncludeFile;
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

    class Helper
    {
    public:
        Helper(std::string NewType,
               std::string OldType,
               std::string ConversionCommand,
               bool IsAMethod,
               bool TakesAnIdentifier,
               std::string ExcelKey ="",
               std::string IncludeFile=""
               );
    private:

        std::string NewType_;
    };



private:
    TypeRegistry()
    {}
    TypeRegistry(const TypeRegistry&)
    {}

    std::map<std::string, regData> Registrations;

    mutable std::map<std::string, std::vector<std::string> > DeductionChains;

    mutable bool ListsBuilt;

};
#endif

//
//
//                            ArgList.h
//
//
/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2009 Narinder S Claire
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

#ifndef ARG_LIST_H
#define ARG_LIST_H

#include "xlw/MyContainers.h"
#include <xlw/CellMatrix.h>
#include <map>
#include <string>
#include <vector>

namespace xlw {

    class ArgumentList
    {
    public:

        ArgumentList(CellMatrix cells, std::string ErrorIdentifier);

        ArgumentList(std::string name);


        enum ArgumentType
        {
            string, number, vector, matrix,
            boolean, list, cells
        };

        std::string GetStructureName() const;

        const std::vector<std::pair<std::string, ArgumentType> >& GetArgumentNamesAndTypes() const;

        std::string GetStringArgumentValue(const std::string& ArgumentName);
        unsigned long GetULArgumentValue(const std::string& ArgumentName);
        double GetDoubleArgumentValue(const std::string& ArgumentName);
        inline MyArray GetArrayArgumentValue(const std::string& ArgumentName);
        inline MyMatrix GetMatrixArgumentValue(const std::string& ArgumentName);
        bool GetBoolArgumentValue(const std::string& ArgumentName);
        CellMatrix GetCellsArgumentValue(const std::string& ArgumentName);
        ArgumentList GetArgumentListArgumentValue(const std::string& ArgumentName);


        // bool indicates whether the argument was found
        bool GetIfPresent(const std::string& ArgumentName,
            unsigned long& ArgumentValue);
        bool GetIfPresent(const std::string& ArgumentName,
            double& ArgumentValue);
        inline bool GetIfPresent(const std::string& ArgumentName,
            MyArray& ArgumentValue);
        inline bool GetIfPresent(const std::string& ArgumentName,
            MyMatrix& ArgumentValue);
        bool GetIfPresent(const std::string& ArgumentName,
            bool& ArgumentValue);
        bool GetIfPresent(const std::string& ArgumentName,
            CellMatrix& ArgumentValue);
        bool GetIfPresent(const std::string& ArgumentName,
            ArgumentList& ArgumentValue);


        bool IsArgumentPresent(const std::string& ArgumentName) const;

        void CheckAllUsed(const std::string& ErrorId) const;

        CellMatrix AllData() const; // makes data into a cell matrix that could be used for
                                    // creating the same argument list
                                    // useful for checking the class works!

        // data insertions

        void add(const std::string& ArgumentName, const std::string& value);
		void add(const std::string& ArgumentName, const char * value);
        void add(const std::string& ArgumentName, double value);
        inline void add(const std::string& ArgumentName, const MyArray& value);
        inline void add(const std::string& ArgumentName, const MyMatrix& value);
        void add(const std::string& ArgumentName, bool value);
        void add(const std::string& ArgumentName, const CellMatrix& values);
        void addList(const std::string& ArgumentName, const CellMatrix& values);
        void add(const std::string& ArgumentName, const ArgumentList& values);

    private:
        template<class TYPE>
        void addInternal(const std::string& ArgumentName, const TYPE& value, std::map<std::string, TYPE>& typeMap, ArgumentType type);
        template<class TYPE>
        const TYPE& GetArgumentValueInternal(std::string ArgumentName, std::map<std::string, TYPE>& typeMap);


        void addArray(const std::string& ArgumentName, const CellMatrix& values);
        void addMatrix(const std::string& ArgumentName, const CellMatrix& values);
        const CellMatrix& GetArrayArgumentValueInternal(const std::string& ArgumentName);
        const CellMatrix& GetMatrixArgumentValueInternal(const std::string& ArgumentName);

        std::string StructureName;
        std::vector<std::pair<std::string, ArgumentType> > ArgumentNames;
        std::map<std::string,double> DoubleArguments;
        std::map<std::string,CellMatrix> ArrayArguments;
        std::map<std::string,CellMatrix> MatrixArguments;
        std::map<std::string,std::string> StringArguments;
        std::map<std::string,CellMatrix> ListArguments;


        std::map<std::string,CellMatrix> CellArguments;
        std::map<std::string,bool> BoolArguments;

        std::map<std::string,ArgumentType> Names;

        std::map<std::string,bool> ArgumentsUsed;

        void GenerateThrow(std::string message, size_t row, size_t column);
        void UseArgumentName(const std::string& ArgumentName); // private as no error checking performed
        void RegisterName(const std::string& ArgumentName, ArgumentType type);
    };
}

inline void xlw::ArgumentList::add(const std::string& ArgumentName, const MyArray& value)
{
    size_t size(ArrayTraits<MyArray>::size(value));
    CellMatrix convertedValue(size, 1);
    for(size_t i(0); i < size; ++i)
    {
        convertedValue(i, 0) = ArrayTraits<MyArray>::getAt(value, i);
    }
    addMatrix(ArgumentName, convertedValue);
}

inline void xlw::ArgumentList::add(const std::string& ArgumentName, const MyMatrix& value)
{
    size_t rows(MatrixTraits<MyMatrix>::rows(value));
    size_t columns(MatrixTraits<MyMatrix>::columns(value));
    CellMatrix convertedValue(rows, columns);
    for(size_t row(0); row < rows; ++row)
    {
        for(size_t col(0); col < columns; ++col)
        {
            convertedValue(row, col) = MatrixTraits<MyMatrix>::getAt(value, row, col);
        }
    }
    addMatrix(ArgumentName, convertedValue);
}

inline xlw::MyArray xlw::ArgumentList::GetArrayArgumentValue(const std::string& ArgumentName)
{
    const CellMatrix& value(GetArrayArgumentValueInternal(ArgumentName));
    size_t size(value.RowsInStructure());
    MyArray returnValue(ArrayTraits<MyArray>::create(size));
    for(size_t i(0); i < size; ++i)
    {
        ArrayTraits<MyArray>::setAt(returnValue, i, value(i, 0).NumericValue());
    }
    return returnValue;
}

inline xlw::MyMatrix xlw::ArgumentList::GetMatrixArgumentValue(const std::string& ArgumentName)
{
    const CellMatrix& value(GetMatrixArgumentValueInternal(ArgumentName));
    size_t rows(value.RowsInStructure());
    size_t columns(value.ColumnsInStructure());
    MyMatrix returnValue(MatrixTraits<MyMatrix>::create(rows, columns));
    for(size_t row(0); row < rows; ++row)
    {
        for(size_t col(0); col < columns; ++col)
        {
            MatrixTraits<MyMatrix>::setAt(returnValue, row, col, value(row, col).NumericValue());
        }
    }
    return returnValue;
}

inline bool xlw::ArgumentList::GetIfPresent(const std::string& ArgumentName, MyArray& ArgumentValue)
{
    if (!IsArgumentPresent(ArgumentName))
        return false;

    ArgumentValue = GetArrayArgumentValue(ArgumentName);
    return true;
}

inline bool xlw::ArgumentList::GetIfPresent(const std::string& ArgumentName, MyMatrix& ArgumentValue)
{
    if (!IsArgumentPresent(ArgumentName))
        return false;

    ArgumentValue = GetMatrixArgumentValue(ArgumentName);
    return true;
}
#endif

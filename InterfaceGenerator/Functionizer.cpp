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
#ifdef _MSC_VER
#if _MSC_VER < 1250
#pragma warning(disable:4786)
#endif
#endif
#include "Functionizer.h"
#include <iostream>


namespace
{
    template<class T>
    T mini(T a, T b)
    {
        return a < b ? a : b;
    }
}
std::string LeftString(std::string input, unsigned long i)
{
    i = mini<unsigned long>(static_cast<unsigned long>(input.size()), i);
    std::string ret(input.begin(), input.begin()+i);
    return ret;
}

FunctionModel FunctionFind(std::vector<Token>::const_iterator& it, std::vector<Token>::const_iterator end, bool TimeDefault)
{
    // we should be at start of function

    std::string returnType = it->GetValue();
    ++it;
    bool Volatile = false;
    bool time =TimeDefault;
    bool threadsafe = false;

    if (it == end)
        throw("function half declared at end of file");

    std::string functionDesc("too lazy to comment this function");

    if (it->GetType() == Token::comment)
    {
        functionDesc = it->GetValue();
        ++it;
    }

    if (it == end)
        throw("function half declared at end of file");

    while (it->GetType() == Token::comment)
    {
        std::string commentString = it->GetValue();

        if (LeftString(commentString,5UL) != "<xlw:")
            throw("unexpected comment in function definition before function name");

        bool found = false;
        if (commentString == "<xlw:volatile")
        {
            Volatile =true;
            ++it;
            found = true;
            if (it == end)
                throw("function half declared at end of file");
        }
        if (commentString == "<xlw:time")
        {
            time = true;
            ++it;
            found = true;
            if (it == end)
                throw("function half declared at end of file");
        }
        if (commentString == "<xlw:threadsafe")
        {
            threadsafe = true;
            ++it;
            found = true;
            if (it == end)
                throw("function half declared at end of file");
        }
        if (!found)
            throw("unknown xlw command: "+commentString);
    }

    if (it->GetType() != Token::identifier)
        throw("function name expected after return type");
    
    std::string functionName(it->GetValue());

    FunctionModel theFunction(returnType,functionName,functionDesc,Volatile,time,threadsafe);

    ++it;
    if (it == end)
        throw("function half declared at end of file");

    if ( it->GetType() != Token::left)
        throw("left parenthesis expected after function name: "+functionName);

    ++it;
    if (it == end)
        throw("function half declared at end of file "+functionName);

    while ( it->GetType() != Token::right)
    {
        if (it->GetType() != Token::identifier)
            throw("return type expected in arg list "+functionName);

        std::string argType = it->GetValue(); 

        ++it;
        if (it == end)
            throw("function half declared at end of file "+functionName);

        if (it->GetType() != Token::identifier)
            throw("argument name expected in arg list "+functionName);

        std::string argName = it->GetValue(); 

        ++it;
        if (it == end)
            throw("function half declared at end of file "+functionName);

        std::string argComment("too lazy to comment this one");

        if (it->GetType() == Token::comment)
        {
            argComment = it->GetValue();
            ++it;
            if (it == end)
                throw("function half declared at end of file "+functionName);
        }

        // ok got this argument's data

        theFunction.AddArgument(argType,argName,argComment);

        if (it->GetType() == Token::comma)
        {
            ++it;
            if (it == end)
                throw("function half declared at end of file "+functionName);
        }

    }
    ++it; // get past final right bracket
    return theFunction;

}

std::vector<FunctionModel> ConvertToFunctionModel(const std::vector<Token>& input, std::string& LibraryName)
{
    std::vector<FunctionModel> output;
    bool timeDefault=false;

    std::vector<Token>::const_iterator it = input.begin();

    while (it != input.end())
    {
        Token ThisToken = *it;

        switch (ThisToken.GetType())
        {
            case Token::preprocessor :
                ++it;
                break; // ignore preprocessor directives
            case Token::curlyleft :
                throw("curly bracket found, only functions can be coped with");
                break;
            case Token::curlyright :
                throw("curly bracket found, only functions can be coped with");
                break;
            case Token::ampersand :
                throw("unexpected ampersand found, return type expected");
                break;
            case Token::comma :
                throw("unexpected comma found, return type expected");
                break;
            case Token::right :
                throw("unexpected ) found, return type expected");
                break;
            case Token::left :
                throw("unexpected ( found, return type expected");
                break;
            case Token::semicolon :
                ++it;
                break;
            case Token::comment :
                {
                    std::string val = it->GetValue();
                    if (LeftString(val,5) == "<xlw:")
                    {
                        bool found = false;

                        if (val.size()>= 19 && val.substr(0,17) == "<xlw:libraryname=")
                        {
                            LibraryName = val.substr(17,val.size());
                            found =true;
                        }

                        if (LeftString(val,12) == "<xlw:timeall")
                        {
                            timeDefault = true;
                            found =true;

                        }

                        if (LeftString(val,13) == "<xlw:timenone")
                        {
                            timeDefault = false;
                            found =true;

                        }

                        if (!found)
                            std::cout << "Unknown xlw command "+val+"\n";

                    }
                    ++it; //ignore comment unless in function definition
                }
                break;
            case Token::identifier :
                output.push_back(FunctionFind(it,input.end(),timeDefault));
                break;
            default:
                throw("unknown token type found");
        }



    }

    return output;

}

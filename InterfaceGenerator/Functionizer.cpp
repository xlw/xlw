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

#include "Functionizer.h"

FunctionModel FunctionFind(std::vector<Token>::const_iterator& it, std::vector<Token>::const_iterator end)
{
	// we should be at start of function

	std::string returnType = it->GetValue();
	++it;
	bool Volatile = false;

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

	if (it->GetType() == Token::comment)
	{
		std::string commentString = it->GetValue();

		if (commentString == "<xlw:volatile")
		{
			Volatile =true;
			++it;
			if (it == end)
				throw("function half declared at end of file");
		}
		else
			throw("unexpected comment in function definition ");
	}

	if (it->GetType() != Token::identifier)
		throw("function name expected after return type");
	
	std::string functionName(it->GetValue());

	FunctionModel theFunction(returnType,functionName,functionDesc,Volatile);

	++it;
	if (it == end)
		throw("function half declared at end of file");

	if ( it->GetType() != Token::left)
		throw("left parenthesis expected after function name :"+functionName);

	++it;
	if (it == end)
		throw("function half declared at end of file"+functionName);

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
					if (val.size()>= 19 && val.substr(0,17) == "<xlw:libraryname=")
					{
						LibraryName = val.substr(19,val.size());
					}
					++it; //ignore comment unless in function definition
				}
				break;
			case Token::identifier :
				output.push_back(FunctionFind(it,input.end()));
				break;
			default:
				throw("unknown token type found");
		}



	}

	return output;

}

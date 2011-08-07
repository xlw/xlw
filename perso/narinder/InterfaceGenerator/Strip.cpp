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

#include "Strip.h"


std::vector<Token> Strip(const std::vector<Token> & input)
{
    std::vector<Token> output1;

    std::vector<Token>::const_iterator it= input.begin();

    while (it != input.end())
    {
        if (it->GetType() != Token::ampersand)
            if (!(it->GetType() == Token::identifier && it->GetValue() == "const"))
                output1.push_back(*it);

        ++it;
    }

    std::vector<Token> output;
    std::vector<Token>::const_iterator iter= output1.begin();

    while (iter != output1.end())
    {
        if (iter->GetType()  == Token::identifier && iter->GetValue() == "unsigned")
        {

            if (iter+1 != output1.end())
            {
                bool pushed=false;
                if ((iter +1) ->GetType() == Token::identifier
                            && (iter+1)->GetValue() == "long")
                {
                            output.push_back(Token(Token::identifier,"unsigned long"));
                            ++iter;
                            ++iter;
                            pushed=true;
                }

                if ((iter +1) ->GetType() == Token::identifier
                            && (iter+1)->GetValue() == "int")
                {
                            output.push_back(Token(Token::identifier,"unsigned int"));
                            ++iter;
                            ++iter;
                            pushed=true;
                }

                if ((iter +1) ->GetType() == Token::identifier
                            && (iter+1)->GetValue() == "short")
                {
                            output.push_back(Token(Token::identifier,"unsigned short"));
                            ++iter;
                            ++iter;
                            pushed=true;
                }
                if (!pushed)
                {
                    output.push_back(*iter);
                    ++iter;
                }
            }
            else
            {
                output.push_back(*iter);
                ++iter;
            }

        }
        else
        {
                output.push_back(*iter);
                ++iter;
        }
    }
    return output;




}

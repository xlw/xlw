
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

#include "Tokenizer.h"
#include "Outputter.h"

Token::Token(TokenType TheType_, const std::string& value_)
: TheType(TheType_), Value(value_)
{
}
Token::TokenType Token::GetType() const
{
    return TheType;
}

std::string Token::GetValue() const
{
    return Value;
}

void RemoveSpaces(std::string& value)
{
    while (value.size() > 0 && value[value.size()-1] ==' ')
    {
        value.resize(    value.size()-1);
    }
}

std::vector<Token> Tokenize(const std::vector<char>& input)
{
    std::vector<Token> output;

    std::vector<char>::const_iterator it = input.begin();

    while (it != input.end())
    {
        char c = *it;
        ++it;

        switch (c)
        {
        case  ' ' : // space so move on;

            break;
        case '\n' : // new line so move on;
            break;
        case ',' :
            output.push_back(Token(Token::comma,""));
            break;
        case '(':
            output.push_back(Token(Token::left,""));
            break;
        case ')':
            output.push_back(Token(Token::right,""));
            break;
        case '&':
            output.push_back(Token(Token::ampersand,""));
            break;
        case ';':
            output.push_back(Token(Token::semicolon,""));
            break;
        case '{':
            output.push_back(Token(Token::left,""));
            break;
        case '}':
            output.push_back(Token(Token::right,""));
            break;
        case '/': // should start comment
            {
                char d = *it;
                ++it;
                if ( d== '/') // one line comment
                {
                    std::string value;
                    while (*it != '\n' && it+1 != input.end())
                    {
                        PushBack(value,*it);
                        ++it;
                    }

                    RemoveSpaces(value);
                    output.push_back(Token(Token::comment,value));
                }
                else
                    if (d == '*' )// multi-line comment)
                    {
                        bool done = false;
                        std::string value;
                        while (!done)
                        {
                            while (it != input.end() &&*it != '*' )
                            {
                                PushBack(value,*it);
                                ++it;
                            }

                            if (it == input.end())
                                done = true;
                            else
                            {
                                ++it;
                                if (*it == '/') // comment had ended
                                {
                                    done =true;
                                    ++it;
                                }
                                else
                                {
                                    PushBack(value,'*');
                                }
                            }

                            output.push_back(Token(Token::comment, value));

                        }
                    }
                    else
                        throw(" / found where not expected.");
                break;
            }
        case '#':
            {
                std::string value;
                do
                {
                    PushBack(value,*it);
                    ++it;
                }
                while (it != input.end() && *it != '\n');

                if (it != input.end())
                    ++it;

                output.push_back(Token(Token::preprocessor, value));
                break;
            }
        default:
            {
                // ok we assume its an identifier
                std::string value;
                PushBack(value,c);

                while (it != input.end() && *it != '\n' && *it != ' '  && *it != '(' && *it != ')' && *it !=',' && *it !='&' && *it !='/')
                {
                    PushBack(value,*it);
                    ++it;
                };

                if (it != input.end() && *it != '(' && *it != ')' && *it !='&' && *it!='/')
                    ++it;

                output.push_back(Token(Token::identifier, value));
                }
        }

// comma, left, right, ampersand,  semicolon, curlyleft, curlyright, comment,
//          preprocessor,  identifier


    }


    return output;

}

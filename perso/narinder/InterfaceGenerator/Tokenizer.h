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

#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include <vector>

class Token
{
public:
    enum TokenType
    {
         comma, left, right, ampersand,  semicolon, curlyleft, curlyright, comment,
          preprocessor,  identifier,
    };

    Token(TokenType TheType, const std::string& value);
    TokenType GetType() const;
    std::string GetValue() const;

private:

    TokenType TheType;
    std::string Value;

};

std::vector<Token> Tokenize(const std::vector<char>& input);

#endif

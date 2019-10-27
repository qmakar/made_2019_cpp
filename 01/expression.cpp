//
//  expression.cpp
//  01
//
//  Created by qmakar on 27.10.2019.
//  Copyright © 2019 qmakar. All rights reserved.
//

#include "expression.hpp"

bool split(const std::string& source, const std::string& operations, std::string& lex1, std::string& lex2, char& op)
{
    long i = source.length() - 1;
    bool t;
    std::string all_oper = "*/-+";
    do
    {
        t = (i > 0) &&
        (operations.find(source[i]) != std::string::npos) &&
        (all_oper.find(source[i-1]) == std::string::npos);
        i--;
    }
    while ((i >= 0) && (!t));
    if (t)
    {
        i++;
        lex1 = source.substr(0, i);
        lex2 = source.substr(i + 1);
        op=source[i];
        return true;
    }
    return false;
    
}

double expr(const std::string& source, unsigned long pos)
{
    std::string lex1, lex2;
    char op;
    if (!split(source, "+-", lex1, lex2, op))
    {
        return item(source, pos);
    }
    else
    {
        if (!isdigit(lex2[0]) && lex2[0] != '-')
        {
            throw Exception(pos - lex2.length());
        }
        switch(op)
        {
            case '+':
                return expr(lex1, pos - lex2.length()) + item(lex2, pos);
            default: // case '-':
                if (lex2.length()>=2 && lex2[0] == '-' && !isdigit(lex2[1]))
                {
                    throw Exception(pos - lex2.length());
                }
                return expr(lex1, pos - lex2.length()) - item(lex2, pos);
        }
    }
}

double item(const std::string& source, unsigned long pos)
{
    std::string lex1, lex2;
    char op;
    
    if (!split(source, "*/", lex1, lex2, op))
    {
        return str_to_double(source, pos);
    }
    else
    {
        if (!isdigit(lex2[0]) && lex2[0] != '-')
        {
            throw Exception(pos - lex2.length());
        }
        switch(op)
        {
            case '*':
                return item(lex1, pos - lex2.length() - 1) * str_to_double(lex2, pos);
            default: // case '/':
                return item(lex1, pos - lex2.length() - 1) / str_to_double(lex2, pos);
        }
    }
}

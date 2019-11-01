//
//  base_operation.cpp
//  01
//
//  Created by qmakar on 27.10.2019.
//  Copyright © 2019 qmakar. All rights reserved.
//

#include "base_operation.hpp"

double str_to_double(const std::string& s, unsigned long pos)
{
    double result;
    std::stringstream convert(s);
    if (!(convert >> result))
    {
        for (long i = s.length() - 1; i >= 0; i-- )
        {
            if (!isdigit(s[i]))
            {
                throw Exception(pos - (s.length() - i - 1));
            }
        }
        throw pos;
    }
    return result;
}


int check(const std::string& str, unsigned long& pos)
{
    std::string all_oper = "*/-+";
    for (int i = 0; i < str.length(); i++)
    {
        if (not(isdigit(str[i]) || all_oper.find(str[i])!=std::string::npos))
        {
            pos = i;
            return 0;
        }
    }
    return 1;
}

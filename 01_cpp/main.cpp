//
//  main.cpp
//  01
//
//  Created by qmakar on 25.10.2019.
//  Copyright © 2019 qmakar. All rights reserved.


#include "main.hpp"


int main(int argc, const char * argv[])
{
    std::string str(argv[1]);
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
    
    unsigned long pos = str.length();
    if (pos == 0 || not(check(str, pos)))
    {
        Exception ex(pos);
        std::cout << ex.msg(str) << std::endl;
        return -1;
    }
    
    try
    {
        double result = expr(str, pos-1);
        std::cout << std::fixed << result << std::endl;
    }
    catch(const Exception& ex) // ref because we don't need copy class oblect
    {
        std::cout << ex.msg(str) << std::endl;
        return -1;
    }
    
    return 0;
}

//
//  main.cpp
//  07_cpp
//
//  Created by qmakar on 07.12.2019.
//  Copyright © 2019 qmakar. All rights reserved.
//

#include "Format.hpp"
#include <vector>

int main(int argc, const char * argv[]) {
    
    
    try{
        format(1);
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
    
    std::string a("1");
    try{
        format(a);
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
    
    try{
        format(a, 1);
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
    
    try{
        format("v ", 1.5, 4.5, 3.5);
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
    
    try{
        format("{1}+{1} = {0}", 2);
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
    
    
    try{
        format("{1}+{1} = {0}", 2, "one", false);
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
    
    try{
        format("{3}+{4} = {0}", 2, "one", false);
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
    
    try{
        format("____{1}...+{11} = {0} < {1}", 2.5, 2000000000);
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
    
    try{
        format("{{1} = {0} < {1}", 1, 1);
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
    
    try{
        format("{1} = {0} < {1}}", 2.5, 1);
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
    
    try{
        format("{1} {= {0} < {1}}", 2.5, 1);
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
    
    std::cout << format("{1}+{1} = {0}", 2, "one") << std::endl;
    
    std::cout << format("{1}+{2} != {0}", "qw", "er", "qwert") << std::endl;
    
    std::cout << format("{1}+{1} = {0} < {1} bla-bla{2}", 2.5, 2000000000, 'd') << std::endl;
    
    
    
    return 0;
}

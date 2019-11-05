//
//  main.cpp
//  03_cpp
//
//  Created by Qmakar on 05.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//

#include <iostream>
#include <string>

#include "parser.hpp"
#include "token_processing.hpp"
#include "test.hpp"

bool get_str(std::string& str){
    if (std::getline(std::cin, str)){
        return 1;
    }
    else{
        return 0;
    }
}



int main(int argc, const char * argv[]) {
    std::string args(argv[1]);
    if (args == "test"){
        test1();
        test2();
        test3();
        test4();
        test5();
        
        std::cout << "All tests passed. Be carefull." << std::endl;
    }
    else if (args == "run"){
        std::string str;
        while (get_str(str)){
            parse(str, token_processing, token_processing);
        }
        
        std::cout << "Good night!" << std::endl;
        
    }
    else{
        std::cout << "Can't recognize command." << std::endl;
        
    }
    
    return 0;
}

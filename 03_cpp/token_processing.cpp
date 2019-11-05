//
//  token_processing.cpp
//  03_cpp
//
//  Created by Qmakar on 05.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//

#include "token_processing.hpp"

int token_processing(int number){ // the Nth Fibonacci
    int a = 1;
    int b = 1;
    int c;
    for (int i = 0; i < number - 2; i++){
        c = a + b;
        a = b;
        b = c;
    }
    std::cout << "Fibonacci(" << number<< ") = " << b << std::endl;
    return b;
}

bool token_processing(const std::string& str){ // is_palindrom?
    bool is_palindrom = true;
    unsigned long len = str.length();
    for (int i = 0; i < len/2; i++){
        if (str[i] != str[len - i - 1]){
            is_palindrom = false;
            break;
        }
    }
    std::cout << "\"" << str << "\"" << " " ;
    if (is_palindrom){
        std::cout << "is palindrom" << std::endl;
    }
    else{
        std::cout << "is NOT palindrom" << std::endl;
    }
    
    return is_palindrom;
}

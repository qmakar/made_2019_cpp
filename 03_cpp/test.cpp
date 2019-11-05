//
//  Test.cpp
//  02_cpp
//
//  Created by Qmakar on 01.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//

#include "test.hpp"

void test1() {
    std::string result;
    result = parse("str", token_processing, token_processing);
//    std::cout << result << std::endl;
    assert(result == "0\n");
}

void test2() {
    std::string result;
    result = parse("8", token_processing, token_processing);
//        std::cout << result << std::endl;
    assert(result == "21\n");
}

void test3() {
    std::string result;
    result = parse("abba 5 6a6", token_processing, token_processing);
//    std::cout << result << std::endl;
    assert(result == "1\n5\n1\n");
}

void test4() {
    std::string result;
    result = parse("  kitty\n  \t 6 \t\t babulya  \n\t", token_processing, token_processing);
//    std::cout << result << std::endl;
    assert(result == "0\n8\n0\n");
}

void test5() {
    std::string result;
    result = parse("\n|?23kuku\n  \t 10 20 30     madam level \t\t babulya  \n\t", token_processing, token_processing);
//    std::cout << result << std::endl;
    assert(result == "0\n55\n6765\n832040\n1\n1\n0\n");
}

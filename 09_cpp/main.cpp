//
//  main.cpp
//  09_cpp
//
//  Created by qmakar on 12.01.2020.
//  Copyright © 2020 qmakar. All rights reserved.
//

#include <iostream>
#include <cassert>

#include "Threads.h"

void test(){
    ThreadPool pool(8);
    std::vector<std::future<char>> results;
    
    auto task1 = pool.exec([]() { return "ASDF"; });
    auto res1 = task1.get();
    assert(res1 == "ASDF");
    std::cout << "[]() { return \"ASDF\"; }   --->   " << res1 << std::endl;
    
    auto task2 = pool.exec([]() { return 1; });
    auto res2 = task2.get();
    assert(res2 == 1);
    std::cout << "[]() { return 1; }   --->   " << res2 << std::endl;
    
    auto task3 = pool.exec([](int a) { return a; }, 4);
    auto res3 = task3.get();
    assert(res3 == 4);
    std::cout << "[](int a) { return a; }(4)   --->   " << res3 << std::endl;
    
    int d = 4;
    auto task4 = pool.exec([d] (int a, int b, int c) { return a + b + c + d; }, 1, 2, 3);
    auto res4 = task4.get();
    assert(res4 == 10);
    std::cout << "[d](int a, int b, int c) { return a + b + c + d; }(1,2,3)   --->   " << res4 << std::endl;
    
    for (int i = 0; i < 5; i++){
        results.emplace_back(pool.exec([i]() { return char(int('A') + i); }));
    }
    char check[5] = {'A', 'B', 'C', 'D', 'E'};
    std::cout << "[i]() { return char(int('A') + i); }   --->   " ;
    for (int i = 0;  i < 5; i++){
        char sym = results[i].get();
        assert(sym == check[i]);
        std::cout << sym << " ";
    }
    std::cout << std::endl;
    
    auto task5 = pool.exec(simple_function, 4000);
    auto res5 = task5.get();
    assert(res5 == 7998000);
    std::cout << "simple_function, 4000   --->   " << res5 << std::endl;
    
    auto task6 = pool.exec(functor(), 1,2,3);
    auto res6 = task6.get();
    assert(res6.elem_ == 16);
    std::cout << "functor(), 1,2,3   --->   " << res6.elem_ << std::endl;
    
    std::cout << "\n\nAll tests passed!!!\n\n";
}


int main()
{
    test();
    
    return 0;
}

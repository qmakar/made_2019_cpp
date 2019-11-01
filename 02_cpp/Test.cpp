//
//  Test.cpp
//  02_cpp
//
//  Created by Qmakar on 01.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//

#include "Test.hpp"

void test1() {
    Allocator<int> a(1 << 2); // 2^2 ints
    
    int * p = a.allocate(2);  // +2 - good
    assert(p != nullptr);
    p[0] = 1;
    p[1] = 2;
    p[2] = 3; // I dont need it! =( The size of p is 2, but I can change another memory!
    
}

void test2() {
    Allocator<int> a(1 << 2); // 2^2 ints
    
    int * p = a.allocate(2);  // +2 - good
    assert(p != nullptr);
    p[0] = 1;
    p[1] = 2;
    
    int * q = a.allocate(3);  // +3 - bad!!!
    assert(q == nullptr);
}

void test3() {
    Allocator<int> a(1 << 2); // 2^2 ints
    
    int * p = a.allocate(2);  // +2 - good
    assert(p != nullptr);
    p[0] = 1;
    p[1] = 2;
    p[2] = 3;
    
    int * q = a.allocate(2);  // +2 - good
    assert(q != nullptr);
    q[0] = 1;
}

void test4() {
    Allocator<int> a(1 << 2); // 2^2 ints
    
    int * p = a.allocate(2);  // +2 - good
    assert(p != nullptr);
    p[0] = 1;
    p[1] = 2;
    p[2] = 3;
    
    int * q = a.allocate(1);  // +1 - good
    assert(q != nullptr);
    q[0] = 1;
    
    a.reset();                // reset!
    p = a.allocate(3);        // +3 - good
    assert(p != nullptr);
    p[3] = 100500;
    
    q = a.allocate(1);        // +1 - good
    assert(q != nullptr);
    q[0] = 42;
}

void test5() {
    Allocator<int> a(1 << 2); // 2^2 ints
    
    int * p = a.allocate(2);  // +2 - good
    assert(p != nullptr);
    p[0] = 1;
    p[1] = 2;
    p[2] = 3;
    
    int * q = a.allocate(1);  // +1 - good
    assert(q != nullptr);
    q[0] = 1;
    
    a.reset();                // reset!
    p = a.allocate(4);        // +4 - good
    assert(p != nullptr);
    p[3] = 100500;
    
    q = a.allocate(1);        // +1 - bad!!!
    assert(q == nullptr);
}

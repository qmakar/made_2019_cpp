//
//  main.cpp
//  06_cpp
//
//  Created by qmakar on 23.11.2019.
//  Copyright © 2019 qmakar. All rights reserved.
//

#include <iostream>
#include "BigInt.hpp"

int main(int argc, const char * argv[]) {
    BigInt a = 1;
    BigInt b = -1;
    
    // test plus & minus
    assert(a + b == 0);
    assert(a - b == 2);
    assert(-a - b == 0);
    assert(-a + b == -2);
    
    assert(a + 1 == 2);
    assert(a - 1 == 0);
    assert(-a - 1 == -2);
    assert(-a + 1 == 0);
    
    assert(1 + a == 2);
    assert(1 - a == 0);
    assert(-1 - a == -2);
    assert(- 1 + a == 0);
    
    assert(a + 1000000 - 300 + b == 999700);
    
    
    
    // test comparison
    assert(a < b == false);
    assert(a <= b == false);
    assert(a > b == true);
    assert(a >= b == true);
    assert(a == b == false);
    assert(a != b == true);
    
    assert(a < 1 == false);
    assert(a <= 1 == true);
    assert(a > 1 == false);
    assert(a >= 1 == true);
    assert(a == 1 == true);
    assert(a != 1 == false);
    
    assert(1 < a == false);
    assert(1 <= a == true);
    assert(1 > a == false);
    assert(1 >= a == true);
    assert(1 == a == true);
    assert(1 != a == false);
    
    std::cout << a - b << std::endl;
    std::cout << -a - b << std::endl;
    
    std::cout << (a <= b) << std::endl;
    std::cout << (a == 1) << std::endl;
    
    
    // many sum & minus
    BigInt c = a + a + b + 897;
    assert(c == 898);
    std::cout << c << std::endl;
    
    BigInt d = a - a - b + 897;
    assert(d == 898);
    std::cout << d << std::endl;
    
    BigInt e = 100 + 100000 + 1000000 - 1 + a + a + b + 897;
    assert(e == 1100997);
    std::cout << e << std::endl;
    
    // assignment
    a = c + 3;
    assert(a == 901);
    
    a = 2;
    assert(a == 2);
    
    // big integer
    a = 2000000000;
    std::cout << a + a + a + a + a + a + a + 3 + 500 + 999 + 1 << std::endl;
    
    std::cout << "All tests passed! You're awesome! ;-)" << std::endl;
    
    return 0;
}

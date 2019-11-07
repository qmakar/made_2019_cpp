//
//  main.cpp
//  04_cpp
//
//  Created by Qmakar on 07.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//

#include <iostream>
#include "Matrix.hpp"

int main(int argc, const char * argv[]) {
    
    // test simple methods
    
    const size_t rows = 5;
    const size_t cols = 3;
    
    Matrix m(rows, cols, 1);
    m.print();                 // matrix of ones
    
    assert(m.getRows() == 5);
    assert(m.getCols() == 3);
    
    
    // test operator[]
    
    m[1][2] = 9;               // assignment
    double x = m[4][1];        // get
    m.print();                 // changed matrix
    
    assert(m[1][2] == 9);
    assert(x == 1);
    
    
    // test copy
    
    Matrix m4(m);
    m4[0][0] = 0;
    m4.print();
    
    assert(m4[0][0] == 0);  // assignment
    assert(m4[1][2] == 9);  // of 28 line of code =)
    
    // test multiply
    
    m *= 3;
    m.print();                 // matrix almost of 3
    
    Matrix m1(rows, cols, 1);
    Matrix m2(cols, rows, 2);
    Matrix m3 = m1 * m2;       // mult 2 matrix
    m3.print();
    
    m3[0] *= 3;                // mult one row
    m3.print();
    
    assert(m[0][0] == 3 &&     // change all
           m[1][2] == 27 &&    // all
           m4[1][2] == 9);     // and dont change copy
    
    assert(m3[1][0] == 6);     // mult matrix of 1 and matrix of 2
    assert(m3[0][0] == 18);    // mult 0th row of 6 by 3
    
    
    // test comparing
    
    if (m1 != m)               // is not equal ?
    {
        std::cout << "Matrix is NOT equal!" << std::endl;
    }
    else{
        std::cout << "Matrix is equal!" << std::endl;
    }
    
    if (m3[1] == m3[2])        // is equal ?
    {
        std::cout << "Rows is equal!" << std::endl;
    }
    else{
        std::cout << "Rows is not equal!" << std::endl;
    }
    
    assert(m1 != m);           // cmp matrix
    assert(m3[1] == m3[2]);    // cmp rows
    
    
    
    // test exceptions
    std::string exception;
    
    // row index
    try{
        m[-1][1] = 1;          // small index
    }
    catch (std::out_of_range ex){
        exception = ex.what();
        std::cout << ex.what() << std::endl;
    }
    assert(exception == "Can't get index -1 of 5 row in matrix");
    
    try{
        m[7][1] = 1;          // big index
    }
    catch (std::out_of_range ex){
        exception = ex.what();
        std::cout << ex.what() << std::endl;
    }
    assert(exception == "Can't get index 7 of 5 row in matrix");
    
    // col index
    try{
        m[1][-100] = 1;          // small index
    }
    catch (std::out_of_range ex){
        exception = ex.what();
        std::cout << ex.what() << std::endl;
    }
    assert(exception == "Can't get index -100 of 3 col in matrix");
    
    try{
        m[1][3] = 1;          // big index
    }
    catch (std::out_of_range ex){
        exception = ex.what();
        std::cout << ex.what() << std::endl;
    }
    assert(exception == "Can't get index 3 of 3 col in matrix");
    
    
    // mult matrix
    try{
        Matrix m = m1*m3;     // bad size!
    }
    catch (std::out_of_range ex){
        exception = ex.what();
        std::cout << ex.what() << std::endl;
    }
    assert(exception == "Can't multiply matrix of sizes 5x3 and 5x5");
    
    
    
    
    std::cout << "All test passed!" << std::endl;

    return 0;
}

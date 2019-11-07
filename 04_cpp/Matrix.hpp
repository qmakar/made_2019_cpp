//
//  Matrix.hpp
//  04_cpp
//
//  Created by Qmakar on 07.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <iostream>

class MatrixProxy;

class Matrix {
    int rows_, cols_;
    int** matrix_;
    
    friend class MatrixProxy;
public:
    Matrix(int rows = 1, int cols = 1, int value = 0);
    Matrix(const Matrix& m);
    
    ~Matrix();
    
    int getRows();
    int getCols();
    void print();
    
    Matrix& operator*=(int k);
    Matrix operator*(const Matrix& right);
    
    bool operator==(const Matrix& right);
    bool operator!=(const Matrix& right);
    
    MatrixProxy operator [] (int row);
    const MatrixProxy operator [] (int row) const;
};



class MatrixProxy{
    int cols_;
    int* row_;
    
public:
    MatrixProxy(Matrix* m, int row_idx);
    MatrixProxy(const Matrix* m, int row_idx);
    
    int& operator [] (int col_idx);
    const int operator [] (int col_idx) const;
    
    bool operator==(const MatrixProxy& right);
    bool operator!=(const MatrixProxy& right);
    
    MatrixProxy& operator*=(int k);
};


#endif /* Matrix_hpp */

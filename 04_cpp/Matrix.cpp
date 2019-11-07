//
//  Matrix.cpp
//  04_cpp
//
//  Created by Qmakar on 07.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//

#include "Matrix.hpp"

Matrix::Matrix(int rows, int cols, int value) : rows_(rows), cols_(cols){
    matrix_ = new int *[rows_];
    for (int i = 0; i < rows_; i++){
        matrix_[i] = new int [cols_];
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = value;
        }
    }
}

Matrix::Matrix(const Matrix& m){
    rows_ = m.rows_;
    cols_ = m.cols_;
    
    matrix_ = new int *[rows_];
    for (int i = 0; i < rows_; i++){
        matrix_[i] = new int [cols_];
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = m[i][j];        // proxy const
        }
    }
}

Matrix::~Matrix(){
    for (int i = 0; i < rows_; i++){
        delete [] matrix_[i];
    }
    delete [] matrix_;
}

int Matrix::getRows() {
    return rows_;
}

int Matrix::getCols() {
    return cols_;
}

void Matrix::print(){
    for (int i = 0; i < rows_; i++){
        for (int j = 0; j < cols_; j++){
            std::cout << matrix_[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

Matrix& Matrix::operator*=(int k)
{
    for (int i = 0; i < rows_; i++){
        for (int j = 0; j < cols_; j++){
            matrix_[i][j] *= k;
        }
    }
    
    return *this;
}


Matrix Matrix::operator*(const Matrix& right){
    if (cols_ != right.rows_){
        throw std::out_of_range("Can't multiply matrix of sizes " + std::to_string(rows_) + "x" + std::to_string(cols_) + " and " + std::to_string(right.rows_) + "x" + std::to_string(right.cols_));
    }
    
    Matrix tmp(rows_, right.cols_);
    for (int i = 0; i < tmp.rows_; i++){
        for (int j = 0; j < tmp.cols_; j++) {
            for (int k = 0; k < right.rows_; k++) {
                tmp[i][j] += matrix_[i][k] * right.matrix_[k][j];
            }
        }
    }
    
    return tmp;
}

bool Matrix::operator==(const Matrix& right){
    for (int i = 0; i < rows_; i++){
        for (int j = 0; j < cols_; j++){
            if (matrix_[i][j] != right.matrix_[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& right){
    return !(*this == right);
}

MatrixProxy Matrix::operator [] (int row_idx)
{
    if (row_idx < 0 || row_idx >= rows_) {
        throw std::out_of_range("Can't get index " + std::to_string(row_idx) + " of " + std::to_string(rows_) + " row in matrix");
    }
    return MatrixProxy(this, row_idx);
}

const MatrixProxy Matrix::operator [] (int row_idx) const{
    if (row_idx < 0 || row_idx >= rows_) {
        throw std::out_of_range("Can't get index " + std::to_string(row_idx) + " of " + std::to_string(rows_) + " row in matrix");
    }
    return MatrixProxy(this, row_idx);
}



MatrixProxy::MatrixProxy(Matrix* m, int row_idx){
    row_ = m->matrix_[row_idx];
    cols_ = m->cols_;
}

MatrixProxy::MatrixProxy(const Matrix* m, int row_idx){
    row_ = m->matrix_[row_idx];
    cols_ = m->cols_;
}

int& MatrixProxy::operator [] (int col_idx){
    if (col_idx < 0 || col_idx >= cols_) {
        throw std::out_of_range("Can't get index " + std::to_string(col_idx) + " of " + std::to_string(cols_) + " col in matrix");
    }
    return row_[col_idx];
}

const int MatrixProxy::operator [] (int col_idx) const{
    if (col_idx < 0 || col_idx >= cols_) {
        throw std::out_of_range("Can't get index " + std::to_string(col_idx) + " of " + std::to_string(cols_) + " col in matrix");
    }
    return row_[col_idx];
}

bool MatrixProxy::operator==(const MatrixProxy& right){
    for (int j = 0; j < cols_; j++){
        if (row_[j] != right.row_[j]){
            return false;
        }
    }
    return true;
}
bool MatrixProxy::operator!=(const MatrixProxy& right){
    return !(*this == right);
}

MatrixProxy& MatrixProxy::operator*=(int k){
    for (int j = 0; j < cols_; j++){
        row_[j] *= k;
    }
    
    return *this;
}

//
//  BigInt.cpp
//  06_cpp
//
//  Created by qmakar on 23.11.2019.
//  Copyright © 2019 qmakar. All rights reserved.
//

#include "BigInt.hpp"

BigInt::BigInt(int a) {
    if (a < 0){
        sign_ = true;
        a = -a;
    }
    size_ = 1;
    
    int tmp = a;
    while (tmp > 0){
        tmp /= 10;
        size_++;
    }
    
    size_ *= 2;
    number_ = new int[size_];
    
    // array[0] = low digit, array[last] = 0
    for (int i = 0; i < size_; i++){
        number_[i] = a % 10;
        a /= 10;
    }
}

BigInt::BigInt(size_t size, int fill_value, bool sign){
    size_ = size;
    number_ = new int [size_];
    for (int i = 0; i < size_; i++) {
        number_[i] = fill_value;
    }
    sign_ = sign;
}

BigInt::BigInt(const BigInt& obj) {
    size_ = obj.size_;
    number_ = new int[size_];
    for (int i = 0; i < size_; i++){
        number_[i] = obj.number_[i];
    }
}

BigInt BigInt::dop_code(const BigInt& obj, size_t size) const {
    BigInt tmp(size, 0);
    
    if (obj.sign_){ // negative
        for (size_t i = 0; i < obj.size_; i++){         // inverse code
            tmp.number_[i] = 10 - obj.number_[i] - 1;
        }
        for (size_t i = obj.size_; i < tmp.size_; i++){
            tmp.number_[i] = 9;
        }
        tmp++;                                          // + 1
        tmp.sign_ = 1;
    }
    else{ // positive
        for (size_t i = 0; i < obj.size_; i++){
            tmp.number_[i] = obj.number_[i];
        }
    }
    
    return tmp;
}

BigInt BigInt::pplus(const BigInt& obj) const{
    size_t new_size = size_ > obj.size_ ? size_ : obj.size_;
    BigInt tmp1 = dop_code(*this, new_size);
    BigInt tmp2 = dop_code(obj, new_size);
    BigInt res(new_size, 0);
    
    bool CF = 0; // ASM carry flag
    for (size_t i = 0; i < new_size; i++) {
        int sum = tmp1.number_[i] + tmp2.number_[i] + CF;
        CF = sum / 10;
        sum = sum % 10;
        res.number_[i] = sum;
    }
    
    BigInt result(res);
    if (res.number_[res.size_ - 1] == 9){
        res.sign_ = true;
        result = dop_code(res, new_size);
    }
    
    return result;
}

BigInt& BigInt::operator++(){
    BigInt tmp(*this);
    int i = 0;
    while (i < size_ && number_[i] == 9){
        number_[i] = 0;
        i++;
    }
    if (i == size_){
        size_t new_size = size_ * 2;
        int* new_number = new int[new_size];
        for (size_t j = 0; j < size_; j++) {
            new_number[j] = number_[j];
        }
        for (size_t j = size_; j < new_size; j++) {
            new_number[j] = 0;
        }
        delete [] number_;
        number_ = new_number;
    }
    number_[i] += 1;
    
    return *this;
}

BigInt BigInt::operator++(int){
    BigInt tmp(*this);
    ++(*this);
    return tmp;
}

BigInt BigInt::operator-() const {
    BigInt tmp(*this);
    tmp.sign_ = !sign_;
    return tmp;
}

BigInt BigInt::operator+(int a) const{
    const BigInt tmp(a);
    return *this + tmp;
}

BigInt BigInt::operator-(int a) const{
    const BigInt tmp(a);
    return *this - tmp;
}

BigInt BigInt::operator+(const BigInt& obj) const{
    return pplus(obj);
}

BigInt BigInt::operator-(const BigInt& obj) const{
    return pplus(-obj);
}

bool BigInt::operator<(const BigInt& obj) const{
    if (sign_ == 0 && obj.sign_ == 1){
        return false;
    }
    else if (sign_ == 1 && obj.sign_ == 0){
        return true;
    }
    
    size_t first1 = size_ - 1;
    size_t first2 = obj.size_ - 1;
    
    while (first1 > 0 && number_[first1] == 0){
        first1--;
    }
    while (first2 > 0 && obj.number_[first2] == 0){
        first2--;
    }
    
    if (first1 < first2){
        return true;
    }
    else if (first1 > first2){
        return false;
    }
    else{
        long idx = first1;
        while (idx >= 0){
            if (number_[idx] < obj.number_[idx]){
                return true;
            }
            else if (number_[idx] > obj.number_[idx]){
                return false;
            }
            else{
                idx--;
            }
        }
    }
    return false;
}

bool BigInt::operator>(const BigInt& obj) const{
    if (sign_ == 0 && obj.sign_ == 1){
        return true;
    }
    else if (sign_ == 1 && obj.sign_ == 0){
        return false;
    }
    
    size_t first1 = size_ - 1;
    size_t first2 = obj.size_ - 1;
    
    while (first1 > 0 && number_[first1] == 0){
        first1--;
    }
    while (first2 > 0 && obj.number_[first2] == 0){
        first2--;
    }
    
    if (first1 > first2){
        return true;
    }
    else if (first1 < first2){
        return false;
    }
    else{
        long idx = first1;
        while (idx >= 0){
            if (number_[idx] > obj.number_[idx]){
                return true;
            }
            else if (number_[idx] < obj.number_[idx]){
                return false;
            }
            else{
                idx--;
            }
        }
    }
    return false;
}

bool BigInt::operator==(const BigInt& obj) const{
    if (sign_ != obj.sign_){
        return false;
    }
    
    size_t first1 = size_ - 1;
    size_t first2 = obj.size_ - 1;
    
    while (first1 > 0 && number_[first1] == 0){
        first1--;
    }
    while (first2 > 0 && obj.number_[first2] == 0){
        first2--;
    }
    
    if (first1 != first2){
        return false;
    }
    
    long idx = first1;
    while (idx >= 0){
        if (number_[idx] != obj.number_[idx]){
            return false;
        }
        idx--;
    }
    
    return true;
}

bool BigInt::operator!=(const BigInt& obj) const{
    return !((*this) == obj);
}

bool BigInt::operator>=(const BigInt& obj) const{
    return !((*this) < obj);
}

bool BigInt::operator<=(const BigInt& obj) const{
    return !((*this) > obj);
}

bool BigInt::operator<(const int& obj) const{
    BigInt tmp(obj);
    return (*this) < tmp;
}

bool BigInt::operator<=(const int& obj) const{
    BigInt tmp(obj);
    return (*this) <= tmp;
}

bool BigInt::operator>(const int& obj) const{
    BigInt tmp(obj);
    return (*this) > tmp;
}

bool BigInt::operator>=(const int& obj) const{
    BigInt tmp(obj);
    return (*this) >= tmp;
}

bool BigInt::operator==(const int& obj) const{
    BigInt tmp(obj);
    return (*this) == tmp;
}

bool BigInt::operator!=(const int& obj) const{
    BigInt tmp(obj);
    return (*this) != tmp;
}

std::ostream& operator<<(std::ostream& os, const BigInt& obj){
    long i = obj.size_ - 1;
    if (obj.sign_){
        os << '-';
    }
    while (obj.number_[i] == 0 && i > 0){
        i--;
    }
    for (long j = i; j >= 0; j--){
        os << obj.number_[j];
    }
    return os;
}


BigInt& BigInt::operator=(BigInt const& obj) {
    if (this != &obj) {
        delete [] number_;
        sign_ = obj.sign_;
        size_ = obj.size_;
        number_ = new int[size_];
        for (int i = 0; i < size_; i++) {
            number_[i] = obj.number_[i];
        }
    }
    return *this;
}

BigInt& BigInt::operator=(int obj) {
//    delete [] number_;
    BigInt a(obj);
    *this = a;
    return *this;
}

BigInt operator+(int i, const BigInt& obj)
{
    BigInt tmp(i);
    return tmp + obj;
}

BigInt operator-(int i, const BigInt& obj)
{
    BigInt tmp(i);
    return tmp - obj;
}

bool operator<(int i, const BigInt& obj){
    BigInt tmp(i);
    return tmp < obj;
}
bool operator<=(int i, const BigInt& obj){
    BigInt tmp(i);
    return tmp <= obj;
}
bool operator>(int i, const BigInt& obj){
    BigInt tmp(i);
    return tmp > obj;
}
bool operator>=(int i, const BigInt& obj){
    BigInt tmp(i);
    return tmp >= obj;
}
bool operator==(int i, const BigInt& obj){
    BigInt tmp(i);
    return tmp == obj;
}
bool operator!=(int i, const BigInt& obj){
    BigInt tmp(i);
    return tmp != obj;
}

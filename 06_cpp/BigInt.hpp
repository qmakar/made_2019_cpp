//
//  BigInt.hpp
//  06_cpp
//
//  Created by qmakar on 23.11.2019.
//  Copyright © 2019 qmakar. All rights reserved.
//

#ifndef BigInt_hpp
#define BigInt_hpp

#include <iostream>

class BigInt {
    int* number_ = nullptr;
    bool sign_ = false; // 0 - positive, 1 - negative
    size_t size_;
    
    BigInt dop_code(const BigInt& obj, size_t size) const;
    
public:
    BigInt(int a);
    BigInt(size_t size, int fill_value, bool sign=false);
    BigInt(const BigInt& obj);
    
    BigInt& operator++();
    BigInt operator++(int);
    
    BigInt operator+(int a) const;
    BigInt operator-(int a) const;
    BigInt operator+(const BigInt& obj) const;
    BigInt operator-(const BigInt& obj) const;
    
    bool operator<(const BigInt& obj) const;
    bool operator<=(const BigInt& obj) const;
    bool operator>=(const BigInt& obj) const;
    bool operator>(const BigInt& obj) const;
    bool operator==(const BigInt& obj) const;
    bool operator!=(const BigInt& obj) const;
    bool operator<(const int& obj) const;
    bool operator<=(const int& obj) const;
    bool operator>=(const int& obj) const;
    bool operator>(const int& obj) const;
    bool operator==(const int& obj) const;
    bool operator!=(const int& obj) const;
    
    BigInt& operator= (BigInt const& obj);
    BigInt& operator=(int obj);
    
    BigInt pplus(const BigInt& obj) const;
    
    BigInt operator-() const;
    
    friend std::ostream& operator<<(std::ostream& os, const BigInt& obj);
    
};

BigInt operator+(int i, const BigInt& obj);
BigInt operator-(int i, const BigInt& obj);

bool operator<(int i, const BigInt& obj);
bool operator<=(int i, const BigInt& obj);
bool operator>(int i, const BigInt& obj);
bool operator>=(int i, const BigInt& obj);
bool operator==(int i, const BigInt& obj);
bool operator!=(int i, const BigInt& obj);

#endif /* BigInt_hpp */

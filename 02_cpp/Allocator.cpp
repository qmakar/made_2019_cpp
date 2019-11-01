//
//  Allocator.cpp
//  02_cpp
//
//  Created by Qmakar on 01.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//

#include "Allocator.hpp"

template class Allocator<int>;

template <typename T>
Allocator<T>::Allocator(size_t max_size){
    buf_size_ = max_size;
    buffer_ = new T[buf_size_];
    last_index_ = 0;
}

template <typename T>
T* Allocator<T>::allocate(size_t size){
    if (last_index_ + size > buf_size_){
        return nullptr;
    }
    T* ptr = buffer_ + last_index_;
    last_index_ += size;
    return ptr;
}
template <typename T>
void Allocator<T>::reset(){
    last_index_ = 0;
}

template <typename T>
Allocator<T>::~Allocator(){
    delete[] buffer_;
}

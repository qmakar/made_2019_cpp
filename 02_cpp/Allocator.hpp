//
//  Allocator.hpp
//  02_cpp
//
//  Created by Qmakar on 01.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//

#ifndef Allocator_hpp
#define Allocator_hpp

#include <stdio.h>

template <typename T>
class Allocator
{
    T* buffer_;
    size_t buf_size_;
    size_t last_index_ = -1;
public:
    Allocator(size_t max_size = 0) ;
    ~Allocator();
    T* allocate(size_t size);
    void reset();
};



#endif /* Allocator_hpp */

//
//  Exception.hpp
//  01
//
//  Created by Mak on 27.10.2019.
//  Copyright © 2019 Mak. All rights reserved.
//

#define DEBUG 0

#ifndef Exception_hpp
#define Exception_hpp

#include "base_operation.hpp"

class Exception
{
    unsigned long pos_;
public:
    Exception(unsigned long pos = 0) : pos_(pos){
#if DEBUG
        std::cout << "constructor Exception" << std::endl;
#endif
    };
    Exception(const Exception& obj)
    {
#if DEBUG
        std::cout << "copy Exception" << std::endl;
#endif
        pos_ = obj.pos_;
    }
    ~Exception()
    {
#if DEBUG
        std::cout << "destructor Exception" << std::endl;
#endif
    }
    std::string msg(const std::string& str) const;
    
};

#endif /* Exception_hpp */

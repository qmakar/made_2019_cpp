//
//  Exception.hpp
//  01
//
//  Created by Mak on 27.10.2019.
//  Copyright © 2019 Mak. All rights reserved.
//

#ifndef Exception_hpp
#define Exception_hpp

#include "base_operation.hpp"

class Exception
{
    unsigned long pos_;
public:
    Exception(unsigned long pos = 0) : pos_(pos){};
    
    std::string msg(const std::string& str) const;
    
};

#endif /* Exception_hpp */

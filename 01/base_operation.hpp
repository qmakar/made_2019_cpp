//
//  base_operation.hpp
//  01
//
//  Created by Mak on 27.10.2019.
//  Copyright © 2019 Mak. All rights reserved.
//

#ifndef base_operation_hpp
#define base_operation_hpp

#include <iostream>
#include <sstream>

#include "Exception.hpp"


double str_to_double(const std::string& s, unsigned long pos);
int check(const std::string& str, unsigned long& pos);

#endif /* base_operation_hpp */

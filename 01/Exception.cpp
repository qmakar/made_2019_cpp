//
//  Exception.cpp
//  01
//
//  Created by qmakar on 27.10.2019.
//  Copyright © 2019 qmakar. All rights reserved.
//

#include "Exception.hpp"

std::string Exception::msg(const std::string& str) const
{
    std::string spaces(pos_, ' ');
    std::string result = "Can't parse string:\n" + str + "\n" + \
                        spaces + "^\nPlease, check your data!";
    return result;
}

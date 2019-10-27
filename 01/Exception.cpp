//
//  Exception.cpp
//  01
//
//  Created by Mak on 27.10.2019.
//  Copyright © 2019 Mak. All rights reserved.
//

#include "Exception.hpp"

std::string Exception::msg(const std::string& str) const
{
    std::string spaces(pos_, ' ');
    std::string result = "Can't parse string:\n" + str + "\n" + \
                        spaces + "^\nPlease, check your data!";
    return result;
}

//
//  parser.hpp
//  03_cpp
//
//  Created by Qmakar on 05.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//

#ifndef parser_hpp
#define parser_hpp

#include <iostream>
#include <string>
#include <sstream>

using f_int_t = int(*)(int);
using f_str_t = bool(*)(const std::string&);
using f_before_t = void(*)(const std::string&, int&);
using f_after_t = void(*)();


void skip_spaces(const std::string&, int&);
void end_of_parse();

std::string parse(const std::string& str, f_int_t fint, f_str_t fstr, f_before_t f_before_parse=skip_spaces, f_after_t f_after_parse=end_of_parse);


#endif /* parser_hpp */

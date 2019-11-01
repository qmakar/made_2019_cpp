//
//  expression.hpp
//  01
//
//  Created by qmakar on 27.10.2019.
//  Copyright © 2019 qmakar. All rights reserved.
//

#ifndef expression_hpp
#define expression_hpp

#include "base_operation.hpp"
#include "Exception.hpp"

bool split(const std::string&, const std::string&, std::string&, std::string&, char&, bool&); // Разделение строки на 2 лексемы
double expr(const std::string&, unsigned long); // Вычисление выражения. Разделение по +-
double item(const std::string&, unsigned long); // Разделение по */

#endif /* expression_hpp */

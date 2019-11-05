//
//  parser.cpp
//  03_cpp
//
//  Created by Qmakar on 05.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//

#include "parser.hpp"

void skip_spaces(const std::string& str, int& i){
    while (i < str.length() &&
           (str[i] == ' ' ||
           str[i] == '\n' ||
           str[i] == '\t')){
        i++;
    }
}

void end_of_parse(){
    std::cout << "End of parsing!\n\n";
}


std::string parse(const std::string& str, f_int_t fint, f_str_t fstr, f_before_t f_before_parse, f_after_t f_after_parse){
    int i = 0;
    f_before_parse(str, i);
    
    std::string result = "";
    
    
    while (i < str.length()){
        bool is_num = true;
        bool checked = false;
        std::string substr = "";
        
        while (i < str.length() &&
               str[i] != ' ' &&
               str[i] != '\n' &&
               str[i] != '\t'){
            
            if (!isdigit(str[i])){
                is_num = false;
            }
            checked = true;
            substr += str[i];
            i++;
        }
        if (checked){
            if (is_num){
                int number;
                std::stringstream convert(substr);
                convert >> number;
                result += std::to_string(fint(number)) + '\n';
            }
            else{
                result += std::to_string(fstr(substr)) + '\n';
            }
        }
        i++;
    }
    
    f_after_parse();
    
    return result;
}

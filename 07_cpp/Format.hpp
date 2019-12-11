//
//  Format.hpp
//  07_cpp
//
//  Created by qmakar on 07.12.2019.
//  Copyright © 2019 qmakar. All rights reserved.
//

#ifndef Format_hpp
#define Format_hpp

#include <iostream>
#include <sstream>

#include <algorithm>
#include <vector>

std::string parse_string(const std::string& str, const std::vector<std::string>& args);

template <class T>
bool process(T& str, int& argc)
{
    throw std::runtime_error("Wrong format string");
    return false;
}

template <class T>
bool process(std::vector<std::string>& vec, int& argc, const T& val)
{
    std::stringstream s;
    s << val;
    vec[argc++] = s.str();
    return true;
}

template <class T, class... Args>
bool process(std::vector<std::string>& vec, int& argc, T& val, const Args&... args)
{
    std::stringstream s;
    s << val;
    vec[argc++] = s.str();
    process(vec, argc, (args)...);
    return true;
}

template <class T, class... Args>
std::string format(const T& val, const Args&... args)
{
    throw std::runtime_error("Wrong format string");
}


template <class... Args>
std::string format(const std::string& str, const Args&... args)
{
    const std::size_t n = sizeof...(Args);
    std::vector<std::string> vec(n);

    int argc = 0;
    process(vec, argc, (args)...);
    
    return parse_string(str, vec);
}

template <class... Args>
std::string format(const char* c_str, const Args&... args)
{
    std::string templ_(c_str);
    
    const std::size_t n = sizeof...(Args);
    std::vector<std::string> vec(n);
    
    int argc = 0;
    process(vec, argc, (args)...);
    
    return parse_string(templ_, vec);
}

std::string parse_string(const std::string& str, const std::vector<std::string>& args){
    std::string result;
    int max_index = 0;
    bool flag = false;
    for (int i = 0; i < str.size(); i++){
        while (i < str.size() && str[i] != '{' && str[i] != '}'){
            result += str[i];
            i++;
        }
        if (i >= str.size() || str[i] == '}'){
            if (args.size() - 1 > max_index){
                throw std::runtime_error("Too many arguments for format string!!!");
            }
            if (!flag){
                throw std::runtime_error("It isn't FORMAT string, it's JUST string -__-");
            }
            if (str[i] == '}'){
                throw std::runtime_error(format("DAMN! Look at the format string \"{1}\" and at position: {0}", i, str));
            }
            return result;
        }
        
        flag = true;
        
        i++; // skip {
        std::string number;
        while (i < str.size() && str[i] != '}'){
            if (isdigit(str[i])){
                number += str[i];
                i++;
            }
            else{
                throw std::runtime_error(format("YOUR format string \"{1}\" is shit in position: {0}", i-1, str));
            }
        }
        if (i >= str.size() || number.empty()){
            throw std::runtime_error(format("Wrong format string \"{1}\" in position: {0}", i-1, str));
        }
        
        int index = stoi(number);
        if (index >= args.size()){
            throw std::runtime_error(format("Wrong format string \"{1}\" in position: {0}", i-1, str));
        }
        result += args[index];
        max_index = std::max(max_index, index);
    }
    
    if (args.size()-1 > max_index){
        throw std::runtime_error("Too many arguments for format string!!!");
    }
    return result;
}

#endif /* Format_hpp */

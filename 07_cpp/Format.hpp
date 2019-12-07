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

bool replace_all(std::string& str, const std::string& from, const std::string& to);
bool replace(std::string& str, int a, const std::string& new_str);


template <class T>
bool process(T& str, int& argc)
{
    throw std::runtime_error("Wrong format string");
    return false;
}

template <class T>
bool process(std::string& str, int& argc, T& val)
{
    std::stringstream s;
    s << val;
    replace(str, argc++, s.str());
    return true;
}


template <class T, class... Args>
bool process(std::string& str, int& argc, T& val, Args... args)
{
    std::stringstream s;
    s << val;
    
    replace(str, argc++, s.str());
    process(str, argc, (args)...);
    return true;
}



template <class T, class... Args>
bool format(T val, Args... args)
{
    throw std::runtime_error("Wrong format string");
    return false;
}


template <class... Args>
std::string format(const std::string& str, Args... args)
{
    std::string templ_ = str;
    
    if ((templ_.find('{') == std::string::npos) || (templ_.find('}') == std::string::npos)) {
        throw std::runtime_error("Format string doesn\'t have any arguments in {}");
    }
    try{
        int argc = 0;
        process(templ_, argc, (args)...);
    }
    catch (std::runtime_error e)
    {
        throw;
    }
    
    if ((str.find('{') != std::string::npos) || (str.find('}') != std::string::npos)) {
        throw std::runtime_error("Wrong format");
    }
    
    return templ_;
}

template <class... Args>
std::string format(const char* c_str, Args... args)
{
    std::string templ_(c_str);
    
    auto max_elem = [] (size_t pos1, size_t pos2) {
        return pos1 < pos2 ? pos1 : pos2;
    };
    
    size_t pos;
    pos = max_elem(templ_.find('{'), templ_.find('}'));
    if (pos == std::string::npos) {
        throw std::runtime_error("Format string doesn\'t have any arguments in {}");
    }
    
    int argc = 0;
    process(templ_, argc, (args)...);
    
    pos = max_elem(templ_.find('{'), templ_.find('}'));
    if (pos != std::string::npos) {
        replace_all(templ_, "{", "[");
        replace_all(templ_, "}", "]");
        throw std::runtime_error(format("Wrong format string \"{1}\" in position: {0}", pos, templ_));
    }
    return templ_;
}


bool replace_all(std::string& str, const std::string& from, const std::string& to){
    size_t pos;
    while ((pos = str.find(from)) != std::string::npos){
        str = str.substr(0, pos) + to + str.substr(pos + from.size());
        pos = str.find(from, pos + to.size());
    }
    return true;
}


bool replace(std::string& str, int a, const std::string& new_str){
    std::string formatting = "{" + std::to_string(a) + "}";
    size_t pos = str.find(formatting);
    if (pos == std::string::npos){
        replace_all(str, "{", "[");
        replace_all(str, "}", "]");
        throw std::runtime_error(format("Can\'t insert argument \"{0}\" into format string\"{1}\" ", new_str, str));
    }
    
    while (pos != std::string::npos){
        str = str.substr(0, pos) + new_str + str.substr(pos + formatting.size());
        pos = str.find(formatting, pos + new_str.size());
    }
    
    return true;
}



#endif /* Format_hpp */

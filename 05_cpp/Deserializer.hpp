//
//  Deserializer.hpp
//  05_cpp
//
//  Created by Qmakar on 17.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//

#ifndef Deserializer_hpp
#define Deserializer_hpp

#include "base.hpp"
#include <string.h>


class Deserializer
{
    std::istream& in_;
    static constexpr char Separator = ' ';
    
public:
    explicit Deserializer(std::istream& in) : in_(in){}

    template <class T>
    Error load(T& object)
    {
        return object.serialize(*this);
    }
    
    template <class... Args>
    Error operator()(Args&... args)
    {
        return process((args)...);
    }

private:
    
    template <class T, class... Args>
    Error process(T& val, Args&... args)
    {
        return Error::IsNotSerialized;
    }
    
    template <class... Args>
    Error process(bool& val, Args&... args)
    {
        std::string text;
        in_ >> text;
        
        if (text == "true")
            val = true;
        else if (text == "false")
            val = false;
        else
            return Error::CorruptedArchive;
        
        if constexpr (sizeof...(Args) > 0){
            return process((args)...);
        }
        else{
            return Error::NoError;
        }
    }
    
    template <class... Args>
    Error process(uint64_t& val, Args&... args){
        std::string text;
        in_ >> text;
        
        bool has_only_digits = true;
        for (size_t i = 0; i < text.length(); i++){
            if (!isdigit(text[i])){
                has_only_digits = false;
                break;
            }
        }
        
        if (!has_only_digits){
            return Error::CorruptedArchive;
        }
        
        val = std::stoull(text);
        
        if constexpr (sizeof...(Args) > 0){
            return process((args)...);
        }
        else{
            return Error::NoError;
        }
    }
    
};

#endif /* Deserializer_hpp */

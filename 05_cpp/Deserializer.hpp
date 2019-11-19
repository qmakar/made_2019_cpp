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

    template <typename T, class = std::enable_if_t<has_serialize_v<T>>>
    Error load (T& object)
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
        if (process(val) != Error::NoError){
            return Error::CorruptedArchive;
        };
        return process((args)...);
    }
    
    template <class T>
    Error process(T& val)
    {
        return Error::CorruptedArchive;
    }
    
    template <>
    Error process(bool& val)
    {
        std::string text;
        in_ >> text;
        
        if (text == "true")
            val = true;
        else if (text == "false")
            val = false;
        else
            return Error::CorruptedArchive;
        
        return Error::NoError;
    }
    
    template <>
    Error process(uint64_t& val)
    {
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
        return Error::NoError;
    }
};

#endif /* Deserializer_hpp */

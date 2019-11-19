//
//  Serializer.hpp
//  05_cpp
//
//  Created by Qmakar on 16.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//

#ifndef Serializer_hpp
#define Serializer_hpp

#include "base.hpp"
#include "CheckFunction.hpp"

template<typename T>
struct IsSerialize;

class Serializer
{
    std::ostream& out_;
    static constexpr char Separator = ' ';
    
public:
    explicit Serializer(std::ostream& out = std::cout) : out_(out) {}
    
    template <typename T, std::enable_if_t<IsSerialize<T>::value, Error>* = nullptr>
    Error save (T& object)
    {
        return object.serialize(*this);
    }
    
//     Пусть будет одна такая весия, на будущее, чтобы не искать долго =)
    template <typename T>
    auto save (T& object) ->
        typename std::enable_if_t<!IsSerialize<T>::value, Error>
    {
        return Error::IsNotSerialized;
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
            return Error::IsNotSerialized;
        };
        return process((args)...);
    }
    
    template <class T>
    Error process(T& val)
    {
        return Error::IsNotSerialized;
    }
    
    template <>
    Error process<uint64_t>(uint64_t& val)
    {
        out_ << val << Separator;
        return Error::NoError;
    }
    
    template <>
    Error process<bool>(bool& val)
    {
        if (val){
            out_ << "true" << Separator;
        }
        else{
            out_ << "false" << Separator;
        }
        return Error::NoError;
    }
};


template<typename T>
struct IsSerialize
{
private:
    static int check(...);
    static Serializer a;
    
    template <class U>
    static auto check(U* u) -> decltype(u->serialize(a));
    
public:
    static constexpr bool value = IsSame<Error,
                                        decltype(IsSerialize<T>::check((T*) nullptr))
                                        >::value;
};


#endif /* Serializer_hpp */

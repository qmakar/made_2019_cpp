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

template<bool, typename T = void>
struct enable_if
{
    
};

template<typename T>
struct enable_if<true, T>
{
    using type = T;
};

class Serializer
{
    std::ostream& out_;
    static constexpr char Separator = ' ';
    
public:
    explicit Serializer(std::ostream& out = std::cout) : out_(out) {}
    
    template <typename T>
    auto save (T& object) ->
        typename std::enable_if<IsSerialize<T>::value, Error>::type
    {
        return object.serialize(*this);
    }
    
    template <typename T>
    auto save (T& object) ->
        typename std::enable_if<!IsSerialize<T>::value, Error>::type
    {
        return Error::IsNotSerialized;
    }
    
    template <class... Args>
    Error operator()(Args... args)
    {
        return process(std::forward<Args>(args)...);
    }
    
private:
    
    
    template <class T, class... Args>
    Error process(T&& val, Args&&... args)
    {
        return Error::IsNotSerialized;
    }
    
    template <class... Args>
    Error process(bool&& val, Args&&... args)
    {
        if (val){
            out_ << "true" << Separator;
        }
        else{
            out_ << "false" << Separator;
        }
        
        if constexpr (sizeof...(Args) > 0){
            return process(std::forward<Args>(args)...);
        }
        else{
            return Error::NoError;
        }
    }
    
    template <class... Args>
    Error process(uint64_t&& val, Args&&... args)
    {
        out_ << val << Separator;
        
        if constexpr (sizeof...(Args) > 0){
            return process(std::forward<Args>(args)...);
        }
        else{
            return Error::NoError;
        }
    }
};


template<typename T>
struct IsSerialize
{
private:
    static int check(...);
    static Serializer a;
//     static const Serializer& b = a;
    
    template <class U>
    static auto check(U* u) -> decltype(u->serialize(a));
    
public:
    static constexpr bool value = IsSame<Error,
                                        decltype(IsSerialize<T>::check((T*) nullptr))
                                        >::value;
};


#endif /* Serializer_hpp */

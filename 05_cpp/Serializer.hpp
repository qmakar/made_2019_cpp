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

class Serializer
{
    std::ostream& out_;
    static constexpr char Separator = ' ';
    
public:
    explicit Serializer(std::ostream& out = std::cout) : out_(out) {}
    
    template <typename T, class = std::enable_if_t<has_serialize_v<T>>>
    Error save (T& object)
    {
        return object.serialize(*this);
    }
    
    template <class... Args>
    Error operator()(Args... args)
    {
        return process((args)...);
    }
    
private:
    
    template <class T, class... Args>
    Error process(T val, Args... args)
    {
        if (process(val) != Error::NoError){
            return Error::IsNotSerialized;
        };
        return process((args)...);
    }
    
    template <class T>
    Error process(T val)
    {
        return Error::IsNotSerialized;
    }
    
    template <>
    Error process(uint64_t val)
    {
        out_ << val << Separator;
        return Error::NoError;
    }
    
    template <>
    Error process(bool val)
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

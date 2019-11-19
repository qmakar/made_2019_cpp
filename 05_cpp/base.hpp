//
//  base.hpp
//  05_cpp
//
//  Created by Qmakar on 17.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//

#ifndef base_hpp
#define base_hpp

#include <iostream>
#include <sstream>
#include <type_traits>

enum class Error
{
    NoError,
    CorruptedArchive,
    IsNotSerialized
};


template <class T, class = void>
struct has_serialize : std::false_type {};

template <class T>
struct
has_serialize<T,
            std::enable_if_t<std::is_same_v<Error,
                                            std::decay_t<decltype(std::declval<T>().serialize(std::declval<T&>()))>>>
            > : std::true_type {};


template <class T>
constexpr bool has_serialize_v = has_serialize<T>::value;

#endif /* base_hpp */

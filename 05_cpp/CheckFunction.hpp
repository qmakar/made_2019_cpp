//
//  CheckFunction.hpp
//  05_cpp
//
//  Created by Qmakar on 17.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//

#ifndef CheckFunction_hpp
#define CheckFunction_hpp

#include "base.hpp"

template <class T1, class T2>
struct IsSame
{
    static constexpr bool value = false;
};

template <class T>
struct IsSame<T, T>
{
    static constexpr bool value = true;
};

//template <typename>
//struct argType;
//
//template <typename R, typename A>
//struct argType<R(A)>
//{ using type = A; };



//template<typename T>
//struct HasFoo
//{
//private:
//    static int check(...);
//
//    template <class U>
//    static auto check(U* u) -> decltype(u->foo(1));
//
//public:
//    static constexpr bool value =
//    IsSame
//    <
//    void,
//    decltype(HasFoo<T>::check((T*) nullptr))
//    >::value;
//};

#endif /* CheckFunction_hpp */

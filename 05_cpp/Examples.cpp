////
////  Examples.cpp
////  05_cpp
////
////  Created by Mak on 17.11.2019.
////  Copyright © 2019 Qmakar. All rights reserved.
////
//
//#include "Examples.hpp"
//template <typename T>
//void print(T&& val)
//{
//    std::cout << val << '\n';
//}
////
//template <>
//void print<int>(int&& val)
//{
//    std::cout << 555 << '\n';
//}
//
//
//
//template <class T, class... Args>
//void print(T&& val, Args&&... args)
//{
//    std::cout << val << '\n';
//    print(std::forward<Args>(args)...);
//}
//
//template <class... Args>
//void print(int&& val, Args&&... args)
//{
//    std::cout << 111 << '\n';
//    print(std::forward<Args>(args)...);
//}
//
//
//struct A
//{
//    void foo(int a) {}
//};
//
//struct B
//{
//};
//
//
//int main(){
//    std::cout << HasFoo<A>::value << '\n';
//    std::cout << HasFoo<B>::value << '\n';
//    
//    print(1, "abc", 2);
//    
//    
//    print(1.7);
//}

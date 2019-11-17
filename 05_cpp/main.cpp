//
//  main.cpp
//  05_cpp
//
//  Created by Qmakar on 16.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//

#include <iostream>
#include "base.hpp"
#include "Serializer.hpp"
#include "Deserializer.hpp"



struct Data
{
    uint64_t a = 0;
    uint64_t b = 0;
    bool c = false;
    
    template <class T>
    Error serialize(T& serializer)
    {
        return serializer(a, b, c);
    }
    
    Error f()
    {
        return Error::IsNotSerialized;
    }
};

struct Data1
{
    uint64_t a = 0;
    uint64_t b = 0;
    bool c = false;
};

struct BadStruct{
    int a = 0;
    std::string s = "";
    
    template <class T>
    Error serialize(T& serializer)
    {
        return serializer(a, s);
    }
};

//struct BadStruct{
//    int a = 0;
//    std::string s = "";
//
//    template <class T>
//    Error serialize(T& serializer)
//    {
//        return serializer(a, s);
//    }
//};


int main(int argc, const char * argv[]) {
    std::stringstream stream;
    Error err;
    
//    std::cout << IsSerialize<Data>::value << std::endl;
    
    // serialize good data
    Data x { 10, 2, true };
    Serializer serializer(stream);
    err = serializer.save(x);

    assert(err == Error::NoError);


    // deserialize good data
    Data y;
    Deserializer deserializer(stream);
    err = deserializer.load(y);

    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
//
//
    // deserialize BAD data
    Data z;
    stream.clear();
    stream << "1w 3 0";          // BAD data
    Deserializer deserializer2(stream);
    err = deserializer2.load(z);

    assert(err == Error::CorruptedArchive);

    // serialize BAD data
    BadStruct a { 1, "Hello" };  // BAD types
    Serializer serializer2(stream);
    err = serializer2.save(a);

    assert(err == Error::IsNotSerialized);
    
    
    // serialize BAD data
    Data1 b { 0, 0, true};  // NO serialize method
    Serializer serializer3(stream);
    err = serializer3.save(b);
    
    assert(err == Error::IsNotSerialized);
    
    
    return 0;
}

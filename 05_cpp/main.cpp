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
    bool b = false;
    uint64_t c = 0;
    
    template <class T>
    Error serialize(T& serializer)
    {
        return serializer(a, b, c);
    }
};

struct Data2
{
    bool a = false;
    uint64_t b = 0;
    bool c = false;
    
    template <class T>
    Error serialize(T& serializer)
    {
        return serializer(a, b, c);
    }
};

struct Data3
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


int main(int argc, const char * argv[]) {
    
    std::stringstream stream;
    Error err;
    
//    std::cout << IsSerialize<Data>::value << std::endl;
    
    
    
    // serialize good data   -- UINT first and last
    Data x { 10, true, 2};
    Serializer serializer(stream);
    err = serializer.save(x);

    assert(err == Error::NoError);


    // deserialize good data   -- UINT first and last
    Data y;
    Deserializer deserializer(stream);
    err = deserializer.load(y);

    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
    
    
    // deserialize one struct to another - BAD
    Data2 yy;
    Deserializer deserializer11(stream);
    err = deserializer11.load(yy);
    
    assert(err == Error::CorruptedArchive);

    
    // serialize good data   -- BOOL first and last
    stream.clear();
    Data2 x2 { true, 2};
    Serializer serializer1(stream);
    err = serializer1.save(x2);
    
    assert(err == Error::NoError);
    
    // deserialize good data  -- BOOL first and last
    Data2 y2;
    Deserializer deserializer1(stream);
    err = deserializer1.load(y2);
    
    assert(err == Error::NoError);
    assert(x2.a == y2.a);
    assert(x2.b == y2.b);
    assert(x2.c == y2.c);
    

    
    
    // deserialize BAD data
    Data z;
    stream.clear();
    stream << "1w 3 0";          // BAD data
    Deserializer deserializer2(stream);
    err = deserializer2.load(z);

    assert(err == Error::CorruptedArchive);

    // serialize BAD data
    stream.clear();
    BadStruct a { 1, "Hello" };  // BAD types
    Serializer serializer2(stream);
    err = serializer2.save(a);

    assert(err == Error::IsNotSerialized);
    
    
    // serialize BAD data
    stream.clear();
    Data3 b { 0, 0, true};  // NO serialize method
    Serializer serializer3(stream);
    err = serializer3.save(b);
    
    assert(err == Error::IsNotSerialized);
    
    
    // deserialize BAD data
    stream.clear();
    Data3 c { 0, 0, true};  // NO deserialize method
    stream.clear();
    stream << "1 2 0";          // BAD data
    Deserializer deserializer3(stream);
    err = deserializer3.load(c);
    
    assert(err == Error::IsNotSerialized);
    
    
    
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}

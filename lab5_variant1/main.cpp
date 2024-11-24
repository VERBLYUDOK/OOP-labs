#include "FixedMemoryResource.h"
#include "PmrVector.h"
#include <iostream>

struct MyStruct {
    int a;
    double b;
    std::string c;

    MyStruct(int a_, double b_, const std::string& c_) : a(a_), b(b_), c(c_) {}
};

int main() {
    FixedMemoryResource memoryResource1(1024);
    
    PmrVector<int> vec1(&memoryResource1);

    vec1.push_back(10);
    vec1.push_back(20);
    vec1.push_back(30);

    for (auto it = vec1.begin(); it != vec1.end(); ++it) {
        std::cout << *it << ' ';
    }

    std::cout << std::endl;

    FixedMemoryResource memoryResource2(2048);
    
    PmrVector<MyStruct> vec2(&memoryResource2);

    vec2.push_back(MyStruct(10, 8.0, "abc"));
    vec2.push_back(MyStruct(20, 16.0, "def"));
    vec2.push_back(MyStruct(30, 32.0, "ghi"));

    for (const auto& val : vec2) {
        std::cout << val.a << ' ' << val.b << ' ' << val.c << std::endl;
    }

    return 0;
}
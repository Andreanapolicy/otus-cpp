#include "src/allocator.h"
#include <iostream>
#include <vector>

int main(int, char const *[])
{   
    std::vector<int, Alloc<5, int>> simpleVec;
    simpleVec.push_back(2);
    simpleVec.push_back(4);
    simpleVec.push_back(6);
    simpleVec.push_back(8);
    simpleVec.push_back(16);

    for (const auto key : simpleVec)
    {
        std::cout << key << std:: endl;
    }
    return 0;
}
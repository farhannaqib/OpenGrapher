#include <stdio.h>
#include <iostream>

#define IS_TRUE(x) { if (!(x)) { std::cout << "Test failed: " << #x << std::endl; return 1; } }
#define IS_FALSE(x) { if (x) { std::cout << "Test failed: " << #x << std::endl; return 1; } }
#define IS_EQUAL(x, y) { if ((x) != (y)) { std::cout << "Test failed: " << #x << " != " << #y << std::endl; return 1; } }
#define IS_NOT_EQUAL(x, y) { if ((x) == (y)) { std::cout << "Test failed: " << #x << " == " << #y << std::endl; return 1; } }
#include <stdio.h>

#define IS_TRUE(x) { if (!(x)) { std::cout << "Test failed: " << #x << std::endl; return 1; } }
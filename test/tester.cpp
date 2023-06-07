#ifdef TEST
#include "testerutils.cpp"

#include "tokenizertest.cpp"
#include "asttest.cpp"

int main() {
    IS_TRUE(tokenizerTests());
    IS_TRUE(astTests());
    return 0;
}

#endif
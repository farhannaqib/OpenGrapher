#ifdef TEST
#include "testerutils.cpp"

#include "tokenizertest.cpp"
#include "asttest.cpp"
#include "solvertest.cpp"

int main() {
    IS_TRUE(tokenizerTests());
    IS_TRUE(astTests());
    IS_TRUE(solverTests());
    return 0;
}

#endif
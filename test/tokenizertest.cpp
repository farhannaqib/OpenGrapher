#include <string>

#include "testerutils.cpp"
#include "tokenizer.h"

bool testReadToken() {
    std::string input = "1+2";
    Token token = readToken(input);
    IS_EQUAL(token.type, TokenType::NUM);
    IS_EQUAL(token.data, "1");
    IS_EQUAL(input, "+2");
    return true;
}
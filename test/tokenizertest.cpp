#include <string>

#include "testerutils.cpp"
#include "tokenizer.h"

bool testReadBasicToken() {
    std::string input = "1+2";
    Token token = readToken(input);
    IS_EQUAL(token.type, TokenType::NUM);
    IS_EQUAL(token.data, "1");
    IS_EQUAL(input, "+2");
    return true;
}

bool testReadCorrectToken() {
    std::string input = "1+2";
    Token token = readToken(input);
    token = readToken(input);
    IS_EQUAL(token.type, TokenType::ADD);
    token = readToken(input);
    IS_EQUAL(token.type, TokenType::NUM);
    return true;
}

bool testReadToken() {
    IS_TRUE(testReadBasicToken());
    IS_TRUE(testReadCorrectToken());
    return true;
}
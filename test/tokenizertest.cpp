#include <string>

#include "testerutils.cpp"
#include "tokenizer.h"

// --- readToken tests --- //

bool testReadBasicToken() {
    std::string input = "1+2";
    Token token = readToken(input);
    IS_EQUAL(token.type, TokenType::NUM);
    IS_EQUAL(token.data, "1");
    IS_EQUAL(input, "+2");
    token = readToken(input);
    IS_EQUAL(token.type, TokenType::ADD);
    token = readToken(input);
    IS_EQUAL(token.type, TokenType::NUM);
    IS_EQUAL(token.data, "2");
    return true;
}

bool testReadAllBasicTokens() {
    std::string input = "+-*/^%,()MAXMINLOGLNSINCOSTANCSCSECCOTSQRTABSFLOORCIELX";
    for (int i = 0; i < 24; i++) {
        Token token = readToken(input);
        IS_EQUAL(token.type, (TokenType) i);
        IS_EQUAL(token.data, tokens[i].string);
    }
    return true;
}

bool testReadConstant() {
    // note: std::string truncates doubles
    // so code is much less precise, revisit later
    std::string input = "PI";
    Token token = readToken(input);
    IS_EQUAL(token.type, TokenType::NUM);
    IS_EQUAL(token.data, "3.141593");
    input = "E";
    token = readToken(input);
    IS_EQUAL(token.type, TokenType::NUM);
    IS_EQUAL(token.data, "2.718282");
    return true;
}

bool testReadNum() {
    std::string inputs[] = {"1.2", "1.", ".2"};
    Token token;
    for (int i = 0; i < 3; i++) {
        std::string input = inputs[i];
        token = readToken(input);
        IS_EQUAL(token.type, TokenType::NUM);
        IS_EQUAL(token.data, inputs[i]);
    }
    std::string input = "1.2.3";
    token = readToken(input);
    IS_EQUAL(token.type, TokenType::ERROR);
    return true;
}

bool testReadError() {
    std::string inputs[] = {".", "", "amogus"};
    for (std::string input : inputs) {
        Token token = readToken(input);
        IS_EQUAL(token.type, TokenType::ERROR);
    }
    return true;
}

bool testReadToken() {
    IS_TRUE(testReadBasicToken());
    IS_TRUE(testReadAllBasicTokens());
    IS_TRUE(testReadConstant());
    IS_TRUE(testReadNum());
    IS_TRUE(testReadError());
    return true;
}

// --- readString tests --- //

bool testReadBasicString() {
    std::string input = "1+2";
    std::queue<Token> tokens = readString(input);
    IS_EQUAL(tokens.size(), 3);
    IS_EQUAL(tokens.front().type, TokenType::NUM);
    IS_EQUAL(tokens.front().data, "1");
    tokens.pop();
    IS_EQUAL(tokens.front().type, TokenType::ADD);
    tokens.pop();
    IS_EQUAL(tokens.front().type, TokenType::NUM);
    IS_EQUAL(tokens.front().data, "2");
    return true;
}

bool testRemovingTokensFromString() {
    std::string input = "1+-2";
    std::queue<Token> tokens = readString(input);
    IS_EQUAL(tokens.size(), 3);
    IS_EQUAL(tokens.front().type, TokenType::NUM);
    IS_EQUAL(tokens.front().data, "1");
    tokens.pop();
    IS_EQUAL(tokens.front().type, TokenType::SUB);
    tokens.pop();
    IS_EQUAL(tokens.front().type, TokenType::NUM);
    IS_EQUAL(tokens.front().data, "2");
    input = "1--2";
    tokens = readString(input);
    IS_EQUAL(tokens.size(), 3);
    IS_EQUAL(tokens.front().type, TokenType::NUM);
    IS_EQUAL(tokens.front().data, "1");
    tokens.pop();
    IS_EQUAL(tokens.front().type, TokenType::ADD);
    tokens.pop();
    IS_EQUAL(tokens.front().type, TokenType::NUM);
    IS_EQUAL(tokens.front().data, "2");
    return true;
}

bool testNegatingNumberInString() {
    // TODO: fix issue with arbitrary floats
    std::string input = "-1";
    std::queue<Token> tokens = readString(input);
    IS_EQUAL(tokens.size(), 1);
    IS_EQUAL(tokens.front().type, TokenType::NUM);
    IS_EQUAL(tokens.front().data, "-1.000000");
    return true;
}

bool testReadString() {
    IS_TRUE(testReadBasicString());
    IS_TRUE(testRemovingTokensFromString());
    IS_TRUE(testNegatingNumberInString());
    return true;
}

// ----------------------- //

bool tokenizerTests() {
    IS_TRUE(testReadToken());
    IS_TRUE(testReadString());
    return true;
}
#include <string>

#include "testerutils.cpp"
#include "tokenizer.h"

// --- readToken tests --- //

bool testReadBasicToken() {
    std::string input = "1+2";
    Token token = readToken(input);
    IS_EQUAL(token, NumToken(1));
    IS_EQUAL(input, "+2");
    token = readToken(input);
    IS_EQUAL(token, Token(TokenType::ADD));
    token = readToken(input);
    IS_EQUAL(token, NumToken(2));
    return true;
}

bool testReadAllBasicTokens() {
    std::string input = "+-*/^%,()MAXMINLOGLNSINCOSTANCSCSECCOTSQRTABSFLOORCIELX";
    for (int i = 0; i < 24; i++) {
        Token token = readToken(input);
        IS_EQUAL(token, Token((TokenType) i));
    }
    return true;
}

bool testReadConstant() {
    // note: std::string truncates doubles
    // so code is much less precise, revisit later
    std::string input = "PI";
    Token token = readToken(input);
    IS_EQUAL(token, NumToken(3.141593));
    input = "E";
    token = readToken(input);
    IS_EQUAL(token, NumToken(2.718282));
    return true;
}

bool testReadNum() {
    std::string inputs[] = {"1.2", "1.", ".2"};
    Token token;
    for (int i = 0; i < 3; i++) {
        std::string input = inputs[i];
        token = readToken(input);
        IS_EQUAL(token, NumToken(std::stod(inputs[i])));
    }
    std::string input = "1.2.3";
    token = readToken(input);
    IS_EQUAL(token, ErrorToken());
    return true;
}

bool testReadError() {
    std::string inputs[] = {".", "", "amogus"};
    for (std::string input : inputs) {
        Token token = readToken(input);
        IS_EQUAL(token, ErrorToken());
    }
    return true;
}

bool testNoIntPreference() {
    std::string input1 = "1.0";
    std::string input2 = "1";
    Token token1 = readToken(input1);
    Token token2 = readToken(input2);
    IS_EQUAL(token1, token2);
    return true;
}

bool testReadToken() {
    IS_TRUE(testReadBasicToken());
    IS_TRUE(testReadAllBasicTokens());
    IS_TRUE(testReadConstant());
    IS_TRUE(testReadNum());
    IS_TRUE(testReadError());
    IS_TRUE(testNoIntPreference());
    return true;
}

// --- readString tests --- //

bool testReadBasicString() {
    std::string input = "1+2";
    std::queue<Token> tokens = readString(input);
    IS_EQUAL(tokens.size(), 3);
    IS_EQUAL(tokens.front(), NumToken(1));
    tokens.pop();
    IS_EQUAL(tokens.front(), Token(TokenType::ADD));
    tokens.pop();
    IS_EQUAL(tokens.front(), NumToken(2));
    return true;
}

bool testRemovingTokensFromString() {
    std::string input = "1+-2";
    std::queue<Token> tokens = readString(input);
    IS_EQUAL(tokens.size(), 3);
    IS_EQUAL(tokens.front(), NumToken(1));
    tokens.pop();
    IS_EQUAL(tokens.front(), Token(TokenType::SUB));
    tokens.pop();
    IS_EQUAL(tokens.front(), NumToken(2));
    input = "1--2";
    tokens = readString(input);
    IS_EQUAL(tokens.size(), 3);
    IS_EQUAL(tokens.front(), NumToken(1));
    tokens.pop();
    IS_EQUAL(tokens.front().type, TokenType::ADD);
    tokens.pop();
    IS_EQUAL(tokens.front(), NumToken(2));
    return true;
}

bool testNegatingNumberInString() {
    std::string input = "-1";
    std::queue<Token> tokens = readString(input);
    IS_EQUAL(tokens.size(), 1);
    IS_EQUAL(tokens.front().type, TokenType::NUM);
    IS_EQUAL(std::stod(tokens.front().data), -1);
    return true;
}

bool testAddingTokensToString() {
    std::string input = "-(1+2)";
    std::queue<Token> tokens = readString(input);
    IS_EQUAL(tokens.size(), 7);
    IS_EQUAL(tokens.front(), NumToken(0));
    return true;
}

bool testReadFunctions() {
    std::string input = "SIN(1)";
    std::queue<Token> tokens = readString(input);
    IS_EQUAL(tokens.size(), 4);
    IS_EQUAL(tokens.front(), Token(TokenType::SIN));
    tokens.pop();
    IS_EQUAL(tokens.front(), Token(TokenType::LB));
    tokens.pop();
    IS_EQUAL(tokens.front(), NumToken(1));
    tokens.pop();
    IS_EQUAL(tokens.front(), Token(TokenType::RB));
    return true;
}

bool testReadNegatives() {
    std::string input = "1+-2";
    std::queue<Token> tokens = readString(input);
    IS_EQUAL(tokens.size(), 3);
    IS_EQUAL(tokens.front(), NumToken(1));
    tokens.pop();
    IS_EQUAL(tokens.front(), Token(TokenType::SUB));
    tokens.pop();
    IS_EQUAL(tokens.front(), NumToken(2));
    input = "COS(-2)";
    tokens = readString(input);
    IS_EQUAL(tokens.size(), 4);
    IS_EQUAL(tokens.front(), Token(TokenType::COS));
    tokens.pop();
    tokens.pop();
    IS_EQUAL(tokens.front(), NumToken(-2));
    return true;
}

bool testVariableMultiplication() {
    std::string input = "2X";
    std::queue<Token> tokens = readString(input);
    IS_EQUAL(tokens.size(), 3);
    IS_EQUAL(tokens.front(), NumToken(2));
    tokens.pop();
    IS_EQUAL(tokens.front(), Token(TokenType::MUL));
    tokens.pop();
    IS_EQUAL(tokens.front(), Token(TokenType::VAR));
    return true;
}

bool testReadString() {
    IS_TRUE(testReadBasicString());
    IS_TRUE(testRemovingTokensFromString());
    IS_TRUE(testNegatingNumberInString());
    IS_TRUE(testAddingTokensToString());
    IS_TRUE(testReadFunctions());
    IS_TRUE(testReadNegatives());
    IS_TRUE(testVariableMultiplication());
    return true;
}

// ----------------------- //

bool tokenizerTests() {
    IS_TRUE(testReadToken());
    IS_TRUE(testReadString());
    return true;
}
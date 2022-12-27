#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>

// Token representations
enum class TokenType {
    ADD, SUB,
    MUL, DIV,
    POW, MOD, 
    LB, RB,
    SIN, COS, TAN, 
    CSC, SEC, COT,
    SQRT, ABS,
    FLOOR, CIEL,
    VAR,
    NUM, ERROR
}; 

static const struct TokenValues {
    std::string string;
    int precedence;
} tokens[] = { // last three are placeholders
    {"+", 1}, {"-", 1},
    {"*", 2}, {"/", 2},
    {"^", 3}, {"%", 2},
    {"(", 0}, {")", 0},
    {"SIN", 0}, {"COS", 0}, {"TAN", 0},
    {"CSC", 0}, {"SEC", 0}, {"COT", 0},
    {"SQRT", 0}, {"ABS", 0},
    {"FLOOR", 0}, {"CIEL", 0},
    {"x", 0},
    {"number", 0}, {"error", 0}
};

// Token class that describes a single token
// with its type and data
class Token {
    public:
    TokenType type;
    std::string data;

    void setType(TokenType t) {
        type = t;
        data = tokens[(int)t].string;
    }
};

// Number token that stores its number
class NumToken : public Token {
    public:

    void setNum(std::string n) {
        data = n;
    }

    NumToken() {
        setType(TokenType::NUM);
    }
};

// Reads and returns the token at the front
// while removing its characters. If no match
// is found, the error token is returned.
// Any set of characters that doesn't directly
// match with the look up table is an error token.
// Whitespace is removed when finding tokens
Token read(std::string& input, bool lastWasRBOrNum);

#endif
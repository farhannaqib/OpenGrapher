#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>

// Token representations
enum class TokenType {
    ADD, SUB,
    MUL, DIV,
    POW, MOD, 
    LB, RB,
    MAX, MIN,
    LOG, LN,
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
    {"MAX", 0}, {"MIN", 0},
    {"LOG", 0}, {"LN", 0},
    {"SIN", 0}, {"COS", 0}, {"TAN", 0},
    {"CSC", 0}, {"SEC", 0}, {"COT", 0},
    {"SQRT", 0}, {"ABS", 0},
    {"FLOOR", 0}, {"CIEL", 0},
    {"x", 0},
    {"number", 0}, {"error", 0}
};

static const struct ConstantValues {
    std::string string;
    double value;
} constants[] = {
    {"PI", 3.14159265358979323846},
    {"E", 2.71828182845904523536}
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

    NumToken(std::string n) {
        setType(TokenType::NUM);
        data = n;
    }
};

class ErrorToken : public Token {
    public: 

    ErrorToken() {
        setType(TokenType::ERROR);
    }
};

// Reads and returns a queue of tokens
// corresponding with the input. If no match
// is found, a queue with only the error token
// is returned.
// Whitespace is removed when finding tokens
std::queue<Token> readString(std::string input);

#endif
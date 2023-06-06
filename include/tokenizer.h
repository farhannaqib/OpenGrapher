#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <queue>

// Token representations
enum class TokenType {
    ADD, SUB,
    MUL, DIV,
    POW, MOD,
    COMMA, LB, RB,
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
    {"+", 2}, {"-", 2},
    {"*", 3}, {"/", 3},
    {"^", 4}, {"%", 3},
    {",", 1}, {"(", 0}, {")", 0},
    {"MAX", 0}, {"MIN", 0},
    {"LOG", 0}, {"LN", 0},
    {"SIN", 0}, {"COS", 0}, {"TAN", 0},
    {"CSC", 0}, {"SEC", 0}, {"COT", 0},
    {"SQRT", 0}, {"ABS", 0},
    {"FLOOR", 0}, {"CIEL", 0},
    {"X", 0},
    {"number", 0}, {"error", 0},
};

static const struct ConstantValues {
    std::string string;
    double value;
} constants[] = {
    {"PI", 3.141592653589793},
    {"E", 2.718281828459045}
};

// Token class that describes a single token
// with its type and data
class Token {
    public:
    TokenType type;
    std::string data;

    Token() {}

    Token(TokenType t) {
        setType(t);
    }

    void setType(TokenType t) {
        type = t;
        data = tokens[(int)t].string;
    }

    bool operator==(const Token& other) const {
        if (type == other.type) return true;
        return data == other.data;
    }
};

// Number token that stores its number
class NumToken : public Token {
    public:

    NumToken(std::string n) {
        setType(TokenType::NUM);
        data = n;
    }

    bool operator==(const NumToken& other) const {
        return data == other.data;
    }
};

class ErrorToken : public Token {
    public: 

    ErrorToken() {
        setType(TokenType::ERROR);
    }
};

// Reads and returns the first token it sees
// while removing it from the input string. 
// Note, this means that strings such as "-1" 
// will return a subtraction token. If no match
// is found, an error token is returned.
// Whitespace is removed when finding tokens
Token readToken(std::string& input);

// Reads and returns a queue of tokens
// corresponding with the input. If no match
// is found, a queue with only the error token
// is returned.
// Whitespace is removed when finding tokens
// Tokens will be added or removed based on 
// relevance for parsing.
std::queue<Token> readString(std::string input);

#endif
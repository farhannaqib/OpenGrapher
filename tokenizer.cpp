#ifndef TOKENIZER_
#define TOKENIZER_

#include <vector>
#include <iostream>
#include <string>

// Token representations
enum class TokenType {
    ADD, SUB,
    MUL, DIV,
    EXP, MOD, 
    LB, RB,
    NUM, ERROR
}; 

// Token representations in string form
// NUM and ERROR have placeholder values
static const std::string tokens[] = {
    "+", "-", "*", "/", "^", "%", 
    "(", ")", "n", "e"
};

// Token class that describes a single token
// with its type and data
class Token {
    public:
    TokenType type;
    std::string data;

    void setType(TokenType t) {
        type = t;
        data = tokens[(int)t];
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
// Whitespace is removed when finding tokens
Token read(std::string& input) {
    Token token;

    // TODO fix the switch
    switch(input.front()) {
        case '+':
            token.setType(TokenType::ADD);
            break;
        case '-':
            token.setType(TokenType::SUB);
            break;
        case '*':
            token.setType(TokenType::MUL);
            break;
        case '/':
            token.setType(TokenType::DIV);
            break;
        case '^':
            token.setType(TokenType::EXP);
            break;
        case '%':
            token.setType(TokenType::MOD);
            break;
        case '(':
            token.setType(TokenType::LB);
            break;
        case ')':
            token.setType(TokenType::RB);
            break;
        default:
            token.setType(TokenType::ERROR);
            break;
    }
    if (token.type != TokenType::ERROR) {
        input.erase(0, 1);
        return token;
    }
    else {
        std::string t;
        while (isdigit(input.front())) {
            t.append(1, input.front());
            input.erase(0, 1);
        }
        if (t == "") return token;

        NumToken numToken;
        numToken.setNum(t);
        return numToken;
    }
}

#endif
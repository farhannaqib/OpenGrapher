#ifndef TOKENIZER_
#define TOKENIZER_

#include <vector>
#include <iostream>
#include <string>

enum class TokenType {
    ADD, SUB,
    MUL, DIV,
    EXP, MOD, 
    NUM, ERROR
};
static const std::string tokens[] = {
    "+", "-", "*", "/", "^", "%", 
    "n", "e"
};

class Token {
    public:
    TokenType type;
    std::string data;

    void setType(TokenType t) {
        type = t;
        data = tokens[(int)t];
    }

    ~Token() {}
};

class NumToken : public Token {
    public:

    void setNum(std::string n) {
        data = n;
    }

    NumToken() {
        setType(TokenType::NUM);
    }
};

// returns token if only a single character
// was needed. returns the error token
// otherwise

Token read(std::string& input) {
    Token token;

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
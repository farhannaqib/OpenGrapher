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
    "+", "-", "*", "/", "^", "%", "(", ")",
    "n", "e"
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
Token read(std::string& input, bool lastWasRBOrNum) {
    Token token;
    token.setType(TokenType::ERROR);

    while(isspace(input.front())) input.erase(0, 1);

    // checks through all 1-char tokens
    bool negValue = false;
    for (int i = 0; i < 8; i++) {
        if (input.front() == tokens[i].front()) {

            // accounts for unary negative op
            if (i == 1 && !lastWasRBOrNum) {
                negValue = true;
                input.erase(0, 1);
                break;
            }

            token.setType((TokenType) i);
            input.erase(0, 1);
            return token;
        }
    }

    std::string t;
    while (isdigit(input.front())) {
        t.append(1, input.front());
        input.erase(0, 1);
    }
    if (t == "") return token;

    if (negValue) t.insert(0, "-");
    NumToken numToken;
    numToken.setNum(t);
    return numToken;
}

#endif
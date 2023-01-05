#include <vector>
#include <iostream>
#include <string>
#include <queue>

#include "tokenizer.h"

// reads a single Token character and 
// removes it from the input
Token read(std::string& input, bool lastWasRBOrNum) {
    Token token;
    token.setType(TokenType::ERROR);

    while(isspace(input.front())) input.erase(0, 1);

    // checks through all tokens
    bool negValue = false;
    for (int i = 0; i < 23; i++) {
        unsigned int len = tokens[i].string.length();
        if (input.substr(0, len) == tokens[i].string) {

            // accounts for unary negative op
            if (i == 1 && !lastWasRBOrNum) {
                negValue = true;
                input.erase(0, len);
                break;
            }

            token.setType((TokenType) i);
            input.erase(0, len);
            return token;
        }
    }

    // check for constants
    for (int i = 0; i < 2; i++) {
        unsigned int len = constants[i].string.length();
        if (input.substr(0, len) == constants[i].string) {
            NumToken numToken;
            numToken.setNum(constants[i].string);
            input.erase(0, len);
            return numToken;
        }
    }

    std::string t;
    bool noDec = true;
    while(isdigit(input.front())) {
        t.append(1, input.front());
        input.erase(0, 1);
        if (input.front()=='.') {
            if (noDec) {
                t.append(1, input.front());
                input.erase(0, 1);
                noDec = false;
            } else return token;
        }
    }
    if (t == "") return ErrorToken(); // error token

    if (negValue) t.insert(0, "-");
    NumToken numToken;
    numToken.setNum(t);
    return numToken;
}

std::queue<Token> readString(std::string input) {
    std::queue<Token> q;

    while (!input.empty()) {
        // read token
        if (!q.empty() && (q.back().type == TokenType::RB 
        || q.back().type == TokenType::NUM)) 
        q.push(read(input, true));
        else q.push(read(input, false));
    }

    return q;
}
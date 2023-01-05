#include <vector>
#include <iostream>
#include <string>

#include "tokenizer.h"

Token* read(std::string& input, bool lastWasRBOrNum) {
    Token* token = new Token();
    token->setType(TokenType::ERROR);

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

            token->setType((TokenType) i);
            input.erase(0, len);
            return token;
        }
    }

    // check for constants
    for (int i = 0; i < 2; i++) {
        unsigned int len = constants[i].string.length();
        if (input.substr(0, len) == constants[i].string) {
            NumToken* numToken = new NumToken();
            numToken->setNum(constants[i].string);
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
    if (t == "") return token; // error token

    if (negValue) t.insert(0, "-");
    NumToken* numToken = new NumToken();
    numToken->setNum(t);
    return numToken;
}
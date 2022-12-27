#include <vector>
#include <iostream>
#include <string>

#include "tokenizer.h"

Token read(std::string& input, bool lastWasRBOrNum) {
    Token token;
    token.setType(TokenType::ERROR);

    while(isspace(input.front())) input.erase(0, 1);

    // checks through all tokens
    bool negValue = false;
    for (int i = 0; i < 19; i++) {
        unsigned int len = tokens[i].string.length();
        if (input.substr(0, len) == tokens[i].string) {

            // accounts for unary negative op
            if (i == 1 && !lastWasRBOrNum) {
                negValue = true;
                input.erase(0, len);
                break;
            } // TODO make this something 
            // else's responsibility

            token.setType((TokenType) i);
            input.erase(0, len);
            return token;
        }
    }

    std::string t;
    while (isdigit(input.front())) {
        t.append(1, input.front());
        input.erase(0, 1);
    }
    if (t == "") return token; // error token

    if (negValue) t.insert(0, "-");
    NumToken numToken;
    numToken.setNum(t);
    return numToken;
}
#include <vector>
#include <iostream>
#include <string>
#include <queue>

#include "tokenizer.h"

// reads a single Token character and 
// removes it from the input
Token read(std::string& input) {
    Token token;
    token.setType(TokenType::ERROR);

    while(isspace(input.front())) input.erase(0, 1);

    // checks through all tokens
    for (int i = 0; i < 23; i++) {
        unsigned int len = tokens[i].string.length();
        if (input.substr(0, len) == tokens[i].string) {

            token.setType((TokenType) i);
            input.erase(0, len);
            return token;
        }
    }

    // check for constants
    for (int i = 0; i < 2; i++) {
        unsigned int len = constants[i].string.length();
        if (input.substr(0, len) == constants[i].string) {
            NumToken numToken = NumToken(constants[i].string);
            input.erase(0, len);
            return numToken;
        }
    }

    std::string t = "";
    bool noDec = true;
    while(isdigit(input.front())) {
        t.append(1, input.front());
        input.erase(0, 1);
        if (input.front()=='.') {
            if (noDec) {
                t.append(1, input.front());
                input.erase(0, 1);
                noDec = false;
            } else return ErrorToken();
        }
    }
    if (t == "" || t == ".") return ErrorToken(); // error token

    NumToken numToken = NumToken(t);
    return numToken;
}

// helper method that updates an addop token
// precondition: second token is also an addop
void updateAddOp(Token &first, Token second) {
    if (first.type == second.type) first.setType(TokenType::ADD);
    else first.setType(TokenType::SUB);
}

std::queue<Token> readString(std::string input) {
    std::queue<Token> q;

    while (!input.empty()) {
        // read token
        Token t = read(input);

        // deals with [+-] [+-]
        if ((int)t.type < 2 && (q.size() != 0 
        && (int) q.back().type < 2)) {
            updateAddOp(q.back(), t);
            continue; // consumes second token
        }

        // deals with ![(Xn_] [+-]
        if ((int) t.type < 2 && (q.size()==0 || q.back().type == TokenType::LB 
        || q.back().type == TokenType::MUL || q.back().type == TokenType::DIV || q.back().type == TokenType::POW)) {
            Token next = read(input);
            if (next.type == TokenType::NUM)  {
                next.data = std::to_string(std::stoi(next.data)*(1-(2*(int) t.type)));
                q.push(next);
                continue;
            }
            else q.push(NumToken("0")); // turns -[non num] into 0-[non num]
        }

        if (t.type == TokenType::ERROR) {
            q = std::queue<Token>();
            q.push(ErrorToken());
            return q;
        }

        q.push(t);
    }

    return q;
}
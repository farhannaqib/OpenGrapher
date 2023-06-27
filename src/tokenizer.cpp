#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

#include "tokenizer.h"

Token readToken(std::string& input) {
    Token token = Token();

    while(isspace(input.front())) input.erase(0, 1);

    // checks through all tokens
    for (int i = 0; i < 24; i++) {
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
            NumToken numToken = NumToken(constants[i].value);
            input.erase(0, len);
            return numToken;
        }
    }

    // account for decimal numbers
    std::string t = "";
    bool noDec = true;
    while(isdigit(input.front()) || (noDec && input.front() == '.')) {
        if (input.front()=='.') {
            t.append(1, input.front());
            input.erase(0, 1);
            noDec = false;
        }
        else {
            t.append(1, input.front());
            input.erase(0, 1);
        }
    }
    if (t == "" || t == "." || input.front()=='.') return ErrorToken();
    
    NumToken numToken = NumToken(std::stod(t));
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
    std::transform(input.begin(), input.end(), input.begin(), ::toupper);

    while (!input.empty()) {
        // read token
        Token t = readToken(input);

        // TODO, fix this logic so t.type == NUM works too
        if (t.type == TokenType::VAR && q.size() != 0 && (q.back().type == TokenType::NUM 
        || q.back().type == TokenType::VAR || q.back().type == TokenType::RB)) {
            Token mulToken = Token(TokenType::MUL);
            q.push(mulToken);
        }

        // deals with [+-] [+-]
        if ((int)t.type < 2 && (q.size() != 0 
        && (int) q.back().type < 2)) {
            updateAddOp(q.back(), t);
            continue; // consumes second token
        }

        // deals with adding negatives to operations
        if ((int) t.type < 2 && (q.size()==0 || q.back().type == TokenType::LB 
        || q.back().type == TokenType::MUL || q.back().type == TokenType::DIV 
        || q.back().type == TokenType::POW)) {
            Token next = readToken(input);
            if (next.type == TokenType::NUM)  {
                next.data = std::to_string(std::stod(next.data)*(1-(2*(int) t.type)));
                q.push(next);
            }
            else {
                // note: maybe switch this to -1*[] instead of 0-[]?
                q.push(NumToken(0)); // turns -[non num] into 0-[non num]
                q.push(t);
                q.push(next);
            }
            continue;
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
#include <iostream>
#include <string>
#include <queue>
#include <stack>

#include "tokenizer.h"
#include "ast.h"

int main() {
    std::string inputs[] {
        "1+2", "1+2*3", "1+2*3-4",
        "1^2", "0+1^2", "E+1"
    };
    
    for (std::string input : inputs){
        std::queue<Token> output = RPN(input);
        while (!output.empty()) {
            std::cout << output.front().data << " ";
            output.pop();
        }
        std::cout << std::endl;
    }

    return 0;
}

std::queue<Token> RPN(std::string input) {
    std::queue<Token> q;

    while (!input.empty()) {
        // read token
        if (!q.empty() && (q.back().type == TokenType::RB 
        || q.back().type == TokenType::NUM)) 
        q.push(read(input, true));
        else q.push(read(input, false));
    }

    // TODO list:
    // account for |
    // account for )X, X(, nx, and xn
    // change from RPN to AST

    std::queue<Token> output;
    std::stack<Token> opstack;

    while (!q.empty()) {
        Token token = q.front();
        q.pop();

        if (token.type == TokenType::NUM || 
        token.type == TokenType::VAR) output.push(token);
        else if (token.type == TokenType::LB) opstack.push(token);
        else if (token.type == TokenType::RB) {
            while (opstack.top().type != TokenType::LB) {
                output.push(opstack.top());
                opstack.pop();
            }
            opstack.pop();
        }
        else if ((int) token.type < 6) {
            if (!opstack.empty()) {
                Token topOp = opstack.top();
                int opPrec = tokens[(int)topOp.type].precedence;
                int curPrec = tokens[(int)token.type].precedence;
                while (topOp.type != TokenType::LB && (opPrec > curPrec 
                || (opPrec == curPrec && token.type != TokenType::POW))) {
                    output.push(opstack.top());
                    opstack.pop();
                    if (opstack.empty()) break;
                    topOp = opstack.top();
                }
            }
            opstack.push(token);
        }
        else if (token.type != TokenType::ERROR) {
            opstack.push(token);
        }
        else return std::queue<Token>();
    }

    while (!opstack.empty()) {
        output.push(opstack.top());
        opstack.pop();
    }

    return output;
}
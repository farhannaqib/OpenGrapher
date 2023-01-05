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
        ASTNode* output = AST(input);
        std::cout << toString(output) << std::endl;
    }

    return 0;
}

void addNode(std::stack<ASTNode*>* nodestack, Token* token) {
    ASTNode* newNode = new ASTNode();
    int size = nodestack->size();
    if (size >= 0) {
        newNode->token = token;
    }
    if (size >= 1) {
        newNode->rightChild = nodestack->top();
        nodestack->pop();
    }
    if (size >= 2) {
        newNode->leftChild = nodestack->top();
        nodestack->pop();
    }
    nodestack->push(newNode);
};

ASTNode* AST(std::string input) {
    std::queue<Token*> q;

    while (!input.empty()) {
        // read token
        if (!q.empty() && (q.back()->type == TokenType::RB 
        || q.back()->type == TokenType::NUM)) 
        q.push(read(input, true));
        else q.push(read(input, false));
    }

    // TODO list:
    // account for |
    // account for )X, X(, nx, and xn
    // change from RPN to AST

    std::stack<ASTNode*> nodestack;
    std::stack<Token*> opstack;

    while (!q.empty()) {
        Token* token = q.front();
        q.pop();

        if (token->type == TokenType::NUM || 
        token->type == TokenType::VAR) {
            ASTNode* num = new ASTNode();
            num->token = token;
            nodestack.push(num);
        }
        else if (token->type == TokenType::LB) opstack.push(token);
        else if (token->type == TokenType::RB) {
            while (opstack.top()->type != TokenType::LB) {
                addNode(&nodestack, opstack.top());
                opstack.pop();
            }
            opstack.pop();
        }
        else if ((int) token->type < 6) {
            if (!opstack.empty()) {
                Token* topOp = opstack.top();
                int opPrec = tokens[(int)topOp->type].precedence;
                int curPrec = tokens[(int)token->type].precedence;
                while (topOp->type != TokenType::LB && (opPrec > curPrec 
                || (opPrec == curPrec && token->type != TokenType::POW))) {
                    addNode(&nodestack, opstack.top());
                    opstack.pop();
                    if (opstack.empty()) break;
                    topOp = opstack.top();
                }
            }
            opstack.push(token);
        }
        else if (token->type != TokenType::ERROR) {
            opstack.push(token);
        }
        else {
            ASTNode* errorNode = new ASTNode();
            Token* errorToken = new Token();
            errorToken->setType(TokenType::ERROR);
            errorNode->token = errorToken;
            return errorNode;
        }
    }

    while (!opstack.empty()) {
        addNode(&nodestack, opstack.top());
        opstack.pop();
    }

    return nodestack.top();
}
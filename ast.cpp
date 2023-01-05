#include <iostream>
#include <string>
#include <queue>
#include <stack>

#include "tokenizer.h"
#include "ast.h"

int main() {
    std::string inputs[] {
        "1+2", "1+2*3", "1+2*3-4",
        "1^2", "0+1^2", "E+1", "1+s",
        "1--2", "1--(2)", "1+-2", "1-+2",
        "-1"
    };
    
    for (std::string input : inputs){
        ASTNode* output = stringtoAST(input);
        std::cout << ASTtoString(output) << std::endl;
    }

    return 0;
}

// helper method that adds node by removing 
// from the nodestack when it can
void addNode(std::stack<ASTNode*> &nodestack, Token token) {
    ASTNode* newNode = new ASTNode();
    int size = nodestack.size();
    if (size >= 0) {
        newNode->token = token;
    }
    if (size >= 1) {
        newNode->rightChild = nodestack.top();
        nodestack.pop();
    }
    if (size >= 2) {
        newNode->leftChild = nodestack.top();
        nodestack.pop();
    }
    nodestack.push(newNode);
};

ASTNode* stringtoAST(std::string input) {
    std::queue<Token> q = readString(input);

    // shunting yard algorithm below

    std::stack<ASTNode*> nodestack;
    std::stack<Token> opstack;

    while (!q.empty()) {
        Token token = q.front();
        q.pop();

        if (token.type == TokenType::NUM || 
        token.type == TokenType::VAR) {
            ASTNode* num = new ASTNode();
            num->token = token;
            nodestack.push(num);
        }
        else if (token.type == TokenType::LB) opstack.push(token);
        else if (token.type == TokenType::RB) {
            while (opstack.top().type != TokenType::LB) {
                addNode(nodestack, opstack.top());
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
                    addNode(nodestack, opstack.top());
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
        else {
            ASTNode* errorNode = new ASTNode();
            errorNode->token = ErrorToken();
            return errorNode;
        }
    }

    while (!opstack.empty()) {
        addNode(nodestack, opstack.top());
        opstack.pop();
    }

    return nodestack.top();
}
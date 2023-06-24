#include <string>
#include <queue>
#include <stack>

#include "tokenizer.h"
#include "ast.h"

// helper method that adds node by removing 
// from the nodestack when it can
void addNode(std::stack<ASTNode*> &nodestack, Token token) {
    ASTNode* newNode = new ASTNode();
    int size = nodestack.size();
    if (size >= 0) {
        newNode->token = token;
    }
    if (size >= 1) {
        newNode->leftChild = nodestack.top();
        nodestack.pop();
    }
    if (size >= 2) {
        newNode->rightChild = newNode->leftChild;
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
        else if (token.type == TokenType::RB && !opstack.empty()) {
            while (opstack.top().type != TokenType::LB) {
                addNode(nodestack, opstack.top());
                opstack.pop();
            }
            opstack.pop();
            if (!opstack.empty() && (int)opstack.top().type > 8 &&
            (int)opstack.top().type < 23) {
                addNode(nodestack, opstack.top());
                opstack.pop();
            }
        }
        else if ((int) token.type < 7) {
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

std::string ASTtoString(ASTNode* node) {
    if (!node) return "";
    if (node->token.type == TokenType::ERROR) return node->token.data;

    std::string leftstr = ASTtoString(node->leftChild);
    std::string rightstr = ASTtoString(node->rightChild);

    // nested ifs moment
    // checks whether parenthesis are needed for pemdas ops
    if ((int)node->token.type < 6) {
        int headprec = tokens[(int)node->token.type].precedence;
        if (node->leftChild) {
            int leftprec = tokens[(int)node->leftChild->token.type].precedence;
            if (leftprec != 0 && headprec > leftprec) {
                leftstr = std::string("(").append(leftstr).append(")");
            }
        }
        if (node->rightChild) {
            int rightprec = tokens[(int)node->rightChild->token.type].precedence;
            if (rightprec != 0 && headprec > rightprec) {
                rightstr = std::string("(").append(rightstr).append(")");
            }
        }
    }

    if ((int) node->token.type >= 9 && (int) node->token.type <= 21) {
        if (node->rightChild) return node->token.data.append("(")
        .append(leftstr).append(", ").append(rightstr).append(")");
        return node->token.data.append("(").append(leftstr).append(")");
    } 

    // for num tokens
    std::string output = leftstr.append(node->token.data).append(rightstr);
    while (output.find(".000000") != std::string::npos) {
        output.erase(output.find(".000000"), 7);
    }
    if (output == "-0") output = "0";
    return output;
}

ASTNode* copyAST(ASTNode* tree) {
    if (!tree) return nullptr;
    ASTNode* copy = new ASTNode();
    copy->token = tree->token;
    copy->leftChild = copyAST(tree->leftChild);
    copy->rightChild = copyAST(tree->rightChild);
    return copy;
}

void deleteAST(ASTNode* tree) {
    if (!tree) return;
    deleteAST(tree->leftChild);
    deleteAST(tree->rightChild);
    delete tree;
}
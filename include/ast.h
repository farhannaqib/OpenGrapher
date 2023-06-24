#ifndef AST_H
#define AST_H

#include <vector>
#include <queue>
#include <string>

#include "tokenizer.h"

// Node for the AST, holds child node and token info
struct ASTNode {
    Token token;
    ASTNode* leftChild;
    ASTNode* rightChild;

    bool operator==(const ASTNode& other) const {
        bool tokenStatus = (token == other.token);
        bool leftChildStatus = false;
        if (leftChild == nullptr || other.leftChild == nullptr) {
            if (leftChild == nullptr && other.leftChild == nullptr) {
                leftChildStatus = true;
            }
        } else leftChildStatus = (*leftChild == *other.leftChild);

        bool rightChildStatus = false;
        if (rightChild == nullptr || other.rightChild == nullptr) {
            if (rightChild == nullptr && other.rightChild == nullptr) {
                rightChildStatus = true;
            }
        } else rightChildStatus = (*rightChild == *other.rightChild);

        return tokenStatus && leftChildStatus && rightChildStatus;
    }

    bool operator!=(const ASTNode& other) const {
        return !(*this == other);
    }
};

// AST generator given an input
// There is no guarantee that the input is a valid 
// equation, the only Error token that comes from 
// this function results from an invalid token from 
// the tokenizer
ASTNode* stringtoAST(std::string input);

// returns equivalent string to the AST
std::string ASTtoString(ASTNode* node);

ASTNode* copyAST(ASTNode* node);

void deleteAST(ASTNode* node);

#endif
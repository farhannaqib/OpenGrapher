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
};

// AST generator given an input
ASTNode* stringtoAST(std::string input);

// returns equivalent string to the AST
std::string ASTtoString(ASTNode* node) {
    if (!node) return "";
    return ASTtoString(node->leftChild).append(node->token.data)
    .append(ASTtoString(node->rightChild));
}

#endif
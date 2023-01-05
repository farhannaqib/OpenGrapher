#ifndef AST_H
#define AST_H

#include <vector>
#include <queue>
#include <string>

#include "tokenizer.h"

struct ASTNode {
    Token* token;
    ASTNode* leftChild;
    ASTNode* rightChild;
};

ASTNode* AST(std::string input);

std::string toString(ASTNode* node) {
    if (!node) return "";
    return toString(node->leftChild).append(node->token->data)
    .append(toString(node->rightChild));
}

#endif
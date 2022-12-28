#ifndef AST_H
#define AST_H

#include <vector>
#include <queue>
#include <string>

#include "tokenizer.h"

struct ASTNode {
    Token token;
    ASTNode* leftChild;
    ASTNode* rightChild;
};

std::queue<Token> RPN(std::string input);

#endif
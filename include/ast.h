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
// There is no guarantee that the input is a valid 
// equation, the only Error token that comes from 
// this function results from an invalid token from 
// the tokenizer
ASTNode* stringtoAST(std::string input);

// returns equivalent string to the AST
std::string ASTtoString(ASTNode* node);

#endif
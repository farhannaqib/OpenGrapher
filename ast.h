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
        if (node->leftChild) return node->token.data.append("(")
        .append(leftstr).append(", ").append(rightstr).append(")");
        return node->token.data.append("(").append(rightstr).append(")");
    } 
    return leftstr.append(" ").append(node->token.data).append(" ").append(rightstr);
}

#endif
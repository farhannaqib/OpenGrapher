#include <math.h>
#include <string>
#include <iostream>

#include "tokenizer.h"
#include "ast.h"
#include "solver.h"

// TODO fix simplify, what if it runs into a 0? 
// TODO fix the comma thing

// Helper method to determine whether 
// a branch is a number node
bool isValidNum(ASTNode* node) {
    if (node->leftChild || node->rightChild) return false;
    if (node->token.type == TokenType::NUM) return true;
    return false;
}

void simplify(ASTNode* tree) {
    if (!tree) return;
    // functions w two args get parsed w a comma to maintain
    // the order of args, this removes the comma for simplifying
    if (tree->leftChild && tree->leftChild->token.type == TokenType::COMMA) {
        ASTNode* left = tree->leftChild->leftChild;
        ASTNode* right = tree->leftChild->rightChild;
        tree->leftChild->leftChild = nullptr;
        tree->leftChild->rightChild = nullptr;
        delete tree->leftChild;
        tree->leftChild = left;
        tree->rightChild = right;
    }
    simplify(tree->leftChild);
    simplify(tree->rightChild);

    // considers how many nodes that we can use for calculations
    // are available
    int numOfChildren = (tree->leftChild ? 1 : 0) + (tree->rightChild ? 1 : 0);
    int numOfSingleChildren = 0;
    if (tree->leftChild && isValidNum(tree->leftChild)) 
    numOfSingleChildren++;
    if (tree->rightChild && isValidNum(tree->rightChild)) 
    numOfSingleChildren++;

    double newData = 0;

    if (numOfSingleChildren == 1 && numOfChildren == 1) {
        double child = std::stod(tree->rightChild->token.data);
        delete tree->rightChild;
        tree->rightChild = nullptr;

        switch(tree->token.type) {
            case (TokenType::LN):
                newData = log(child);
                break;
            case (TokenType::SIN):
                newData = sin(child);
                break;
            case (TokenType::COS):
                newData = cos(child);
                break;
            case (TokenType::TAN):
                newData = tan(child);
                break;
            case (TokenType::CSC):
                newData = 1.0/sin(child);
                break;
            case (TokenType::SEC):
                newData = 1.0/cos(child);
                break;
            case (TokenType::COT):
                newData = 1.0/tan(child);
                break;
            case (TokenType::SQRT):
                newData = sqrt(child);
                break;
            case (TokenType::ABS):
                newData = abs(child);
                break;
            case (TokenType::FLOOR):
                newData = floor(child);
                break;
            case (TokenType::CIEL):
                newData = ceil(child);
                break;
            default:
                break;
        }
        tree->token = NumToken(newData);
    }
    else if (numOfSingleChildren == 2) { // token has to be binary
        double left = std::stod(tree->leftChild->token.data);
        double right = std::stod(tree->rightChild->token.data);
        delete tree->leftChild;
        tree->leftChild = nullptr;
        delete tree->rightChild;
        tree->rightChild = nullptr;

        switch(tree->token.type) {
            case (TokenType::ADD):
                newData = left+right;
                break;
            case (TokenType::SUB):
                newData = left-right;
                break;
            case (TokenType::MUL):
                newData = left*right;
                break;
            case (TokenType::DIV):
                newData = left/right;
                break;
            case (TokenType::POW):
                newData = pow(left,right);
                break;
            case (TokenType::MOD):
                newData = (int)left%(int)right;
                break;
            case (TokenType::MAX):
                newData = std::max(left,right);
                break;
            case (TokenType::MIN):
                newData = std::min(left,right);
                break;
            case(TokenType::LOG):
                newData = log(left)/log(right);
                break;
            default:
                break;
        }
        tree->token = NumToken(newData);
    }
}
#include <math.h>
#include <string>
#include <iostream>
#include <limits>

#include "tokenizer.h"
#include "ast.h"
#include "solver.h"

// Helper method to determine whether 
// a branch is a number node
bool isValidNum(ASTNode* node) {
    if (node->leftChild || node->rightChild) return false;
    if (node->token.type == TokenType::NUM) return true;
    return false;
}

// Helper method to determine whether
// a branch is a number or variable node
bool isValidNumOrVar(ASTNode* node) {
    if (node->leftChild || node->rightChild) return false;
    if (node->token.type == TokenType::NUM 
    || node->token.type == TokenType::VAR) return true;
    return false;
}

bool canBeSimplified(ASTNode* tree) {
    if (!tree || tree->token == TokenType::ERROR) return false;
    if (isValidNumOrVar(tree)) return true;
    if ((int) tree->token.type <= 6) {
        return canBeSimplified(tree->leftChild) && canBeSimplified(tree->rightChild);
    }
    else if ((int) tree->token.type < 23 && (int) tree->token.type > 8) {
        return canBeSimplified(tree->leftChild);
    }
    return false;
}

void simplify(ASTNode* tree) {
    if (!tree) return;
    // functions w two args get parsed w a comma to maintain
    // the order of args, this removes the comma for simplifying
    // this also means that canBeSimplified returns false, since it 
    // expects a function to have one arg, that being the comma...
    // No point in fixing it since the application only has to check
    // a given tree once, and the tree resets after each new input
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
        double child = std::stod(tree->leftChild->token.data);
        delete tree->leftChild;
        tree->leftChild = nullptr;

        switch(tree->token.type) {
            case (TokenType::LN):
                if (child <= 0) throw std::domain_error("ln of negative number");
                newData = log(child);
                break;
            case (TokenType::SIN):
                newData = sin(child);
                break;
            case (TokenType::COS):
                newData = cos(child);
                break;
            case (TokenType::TAN):
                if (cos(child) == 0) throw std::domain_error("tan of pi/2");
                newData = tan(child);
                break;
            case (TokenType::CSC):
                if (sin(child) == 0) throw std::domain_error("csc of 0");
                newData = 1.0/sin(child);
                break;
            case (TokenType::SEC):
                if (cos(child) == 0) throw std::domain_error("sec of pi/2");
                newData = 1.0/cos(child);
                break;
            case (TokenType::COT):
                if (tan(child) == 0) throw std::domain_error("cot of 0");
                newData = 1.0/tan(child);
                break;
            case (TokenType::SQRT):
                if (child < 0) throw std::domain_error("sqrt of negative number");
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
                if (right == 0) throw std::domain_error("division by 0");
                newData = left/right;
                break;
            case (TokenType::POW):
                newData = pow(left,right);
                break;
            case (TokenType::MOD):
                if (right <= 0) throw std::domain_error("mod by non-positive number");
                newData = (int)left%(int)right;
                break;
            case (TokenType::MAX):
                newData = std::max(left,right);
                break;
            case (TokenType::MIN):
                newData = std::min(left,right);
                break;
            case(TokenType::LOG):
                if (left <= 0 || right <= 0) throw std::domain_error("log of negative number");
                newData = log(left)/log(right);
                break;
            default:
                break;
        }
        tree->token = NumToken(newData);
    }
}

void replaceVar(ASTNode* tree, double x) {
    if (!tree) return;
    if (tree->token.type == TokenType::VAR) {
        tree->token = NumToken(x);
    }
    replaceVar(tree->leftChild, x);
    replaceVar(tree->rightChild, x);
}

double evaluateAtX(ASTNode* tree, double x) {
    if (!tree) throw std::invalid_argument("Tree is null");
    if (!canBeSimplified(tree)) throw std::invalid_argument("Tree cannot be simplified");
    ASTNode* copy = copyAST(tree);
    replaceVar(copy, x);
    simplify(copy);
    double result = std::stod(copy->token.data);
    deleteAST(copy);
    return result;
}
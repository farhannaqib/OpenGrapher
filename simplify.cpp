#include <math.h>
#include <string>
#include <iostream>

#include "tokenizer.h"
#include "ast.h"

// input an AST tree
// use DFS to go through each branch
// simplify numbers n shi through calculations
// avoid variables

// we need to define a calculate method
// that will calculate a specific tree branch
// and return errors if the inputs are incorrect

bool isValidNum(ASTNode* node) {
    if (node->leftChild || node->rightChild) return false;
    if (node->token.type == TokenType::NUM) return true;
    return false;
}

void simplify(ASTNode* tree) {
    if (!tree) return;
    simplify(tree->leftChild);
    simplify(tree->rightChild);

    // simple operations
    int numOfSingleChildren = 0;
    if (tree->leftChild && isValidNum(tree->leftChild)) 
    numOfSingleChildren++;
    if (tree->rightChild && isValidNum(tree->rightChild)) 
    numOfSingleChildren++;

    if (numOfSingleChildren == 2) { // token has to be binary
        double left = std::stod(tree->leftChild->token.data);
        double right = std::stod(tree->rightChild->token.data);
        delete tree->leftChild;
        tree->leftChild = nullptr;
        delete tree->rightChild;
        tree->rightChild = nullptr;
        std::string newData = "";
        std::cout << "made it" << std::endl;

        switch(tree->token.type) {
            case (TokenType::ADD):
                newData = std::to_string(left+right);
                break;
            case (TokenType::SUB):
                newData = std::to_string(left-right);
                break;
            case (TokenType::MUL):
                newData = std::to_string(left*right);
                break;
            case (TokenType::DIV):
                newData = std::to_string(left/right);
                break;
            case (TokenType::POW):
                newData = std::to_string(pow(left,right));
                break;
            case (TokenType::MOD):
                newData = std::to_string((int) left % (int) right);
                break;
            default:
                newData = "";
                break;
        }
        tree->token = NumToken(newData);
    }
    

}

int main() {
    std::string inputs[] {
        "1+2", "1+2*3", "1+2*3-4",
        "1^2", "0+1^2", "E+1", "1+s",
        "1--2", "1--(-2)", "1+-2", "1-+2",
        "-1", "SIN(2)", "MAX(2, 3)", "MAX(1+2,3)", 
        "(4+5)", "0-(1)", "0-(4+5)", "-(4+5)"
    };
    
    //for (std::string input : inputs){
    //    ASTNode* output = stringtoAST(input);
    //    std::cout << ASTtoString(output) << std::endl;
    //}

    std::string inputs2[] {
        "1+2", "1+2*3", "1+2*3-4",
        "1^2", "0+1^2", "E+1"
    };

    for (std::string input : inputs2) {
        ASTNode* output = stringtoAST(input);
        simplify(output);
        std::cout << ASTtoString(output) << std::endl;
    }

    return 0;
}
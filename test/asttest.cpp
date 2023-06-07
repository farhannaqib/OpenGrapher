#include <string>

#include "testerutils.cpp"
#include "ast.h"

// --- stringtoAST tests --- //

bool testChartoAST() {
    std::string input = "1";
    ASTNode* ast = stringtoAST(input);
    IS_EQUAL(ast->token, NumToken(1));
    IS_EQUAL(ast->leftChild, nullptr);
    IS_EQUAL(ast->rightChild, nullptr);
    return true;
}

bool testSimpleStringtoAST() {
    std::string input = "1+2";
    ASTNode* ast = stringtoAST(input);
    IS_EQUAL(ast->token, Token(TokenType::ADD));
    IS_EQUAL(ast->leftChild->token, NumToken(1));
    IS_EQUAL(ast->rightChild->token, NumToken(2));
    return true;
}

bool testLessSimpleStringtoAST() {
    std::string input = "1+2*3";
    ASTNode* ast = stringtoAST(input);
    IS_EQUAL(ast->token, Token(TokenType::ADD));
    IS_EQUAL(ast->leftChild->token, NumToken(1));
    IS_EQUAL(*ast->rightChild, *stringtoAST("2*3"));
    return true;
}

bool testFunctiontoAST() {
    std::string input = "SIN(1)";
    ASTNode* ast = stringtoAST(input);
    IS_EQUAL(ast->token, Token(TokenType::SIN));
    IS_EQUAL(ast->leftChild->token, NumToken(1));
    IS_EQUAL(ast->rightChild, nullptr);
    return true;
}

bool testStringtoAST() {
    IS_TRUE(testChartoAST());
    IS_TRUE(testSimpleStringtoAST());
    IS_TRUE(testLessSimpleStringtoAST());
    IS_TRUE(testFunctiontoAST());
    return true;
}

// --- ASTtoString tests --- //

bool testASTtoString() {
    return true;
}

// ------------------------ //

bool astTests() {
    IS_TRUE(testStringtoAST());
    IS_TRUE(testASTtoString());
    return true;
}
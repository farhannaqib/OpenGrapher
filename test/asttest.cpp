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
    input = "MAX(1,2)";
    ast = stringtoAST(input);
    IS_EQUAL(ast->token, Token(TokenType::MAX));
    IS_EQUAL(ast->leftChild->token, Token(TokenType::COMMA));
    IS_EQUAL(ast->leftChild->leftChild->token, NumToken(1));
    IS_EQUAL(ast->leftChild->rightChild->token, NumToken(2));
    return true;
}

bool testParentheticalStringtoAST() {
    std::string input = "(1+2)";
    ASTNode* ast = stringtoAST(input);
    IS_EQUAL(*ast, *stringtoAST("1+2"));
    input = "1+(2*3)";
    ast = stringtoAST(input);
    IS_EQUAL(*ast, *stringtoAST("1+2*3"));
    return true;
}

bool testStringtoAST() {
    IS_TRUE(testChartoAST());
    IS_TRUE(testSimpleStringtoAST());
    IS_TRUE(testLessSimpleStringtoAST());
    IS_TRUE(testFunctiontoAST());
    IS_TRUE(testParentheticalStringtoAST());
    return true;
}

// --- ASTtoString tests --- //

bool testBasicASTtoString() {
    std::string inputs[] = {"1", "1+2", "1+2*3", 
    "1+2*3-4", "1^2", "0+1^2"};
    for (std::string input : inputs) {
        IS_EQUAL(ASTtoString(stringtoAST(input)), input);
    }
    return true;
}

bool testFunctionASTtoString() {
    std::string inputs[] = {"SIN(1)", "MAX(2,3)", 
    "MAX(1+4,3)", "LOG(4,2)"};
    for (std::string input : inputs) {
        IS_EQUAL(ASTtoString(stringtoAST(input)), input);
    }
    return true;
}

bool testASTtoString() {
    IS_TRUE(testBasicASTtoString());
    IS_TRUE(testFunctionASTtoString());
    return true;
}

// ------------------------ //

bool astTests() {
    IS_TRUE(testStringtoAST());
    IS_TRUE(testASTtoString());
    return true;
}
#include <string>

#include "testerutils.cpp"
#include "solver.h"

// -- canBeSimplified tests -- //

bool testCanBeSimplified() {
    std::string input = "1+2";
    ASTNode* ast = stringtoAST(input);
    IS_TRUE(canBeSimplified(ast));
    ast = stringtoAST("1+(2)");
    IS_TRUE(canBeSimplified(ast));
    ast = stringtoAST("1+2*3");
    IS_TRUE(canBeSimplified(ast));
    ast = stringtoAST("1+2)");
    IS_FALSE(canBeSimplified(ast));
    ast = stringtoAST("1+2*X");
    IS_TRUE(canBeSimplified(ast));
    ast = stringtoAST("1+SIN(X)");
    IS_TRUE(canBeSimplified(ast));
    ast = stringtoAST("1*SIN(X)");
    IS_TRUE(canBeSimplified(ast));
    ast = stringtoAST("1+SIN(X+2");
    IS_FALSE(canBeSimplified(ast));
    ast = stringtoAST("1+SIN(S+2)");
    IS_FALSE(canBeSimplified(ast));
    return true;
}

// --- simplify tests --- //

bool testBasicSimplify() {
    std::string input = "1+2";
    ASTNode* ast = stringtoAST(input);
    simplify(ast);
    IS_EQUAL(ast->token, NumToken(3));
    ast = stringtoAST("1+2*3");
    simplify(ast);
    IS_EQUAL(ast->token, NumToken(7));
    ast = stringtoAST("1+2*3-4");
    simplify(ast);
    IS_EQUAL(ast->token, NumToken(3));
    ast = stringtoAST("1^2");
    simplify(ast);
    IS_EQUAL(ast->token, NumToken(1));
    return true;
}

bool testParentheticalSimplify() {
    std::string input = "(1+2)";
    ASTNode* ast = stringtoAST(input);
    simplify(ast);
    IS_EQUAL(ast->token, NumToken(3));
    ast = stringtoAST("(1+2)*3");
    simplify(ast);
    IS_EQUAL(ast->token, NumToken(9));
    ast = stringtoAST("1+(2*3)");
    simplify(ast);
    IS_EQUAL(ast->token, NumToken(7));
    ast = stringtoAST("0-(1)");
    simplify(ast);
    IS_EQUAL(ast->token, NumToken(-1));
    ast = stringtoAST("0-(1+2)");
    simplify(ast);
    IS_EQUAL(ast->token, NumToken(-3));
    ast = stringtoAST("-(1+2)");
    simplify(ast);
    IS_EQUAL(ast->token, NumToken(-3));
    return true;
}

bool testFunctionSimplify() {
    std::string input = "5*SIN(PI)";
    ASTNode* ast = stringtoAST(input);
    simplify(ast);
    IS_EQUAL(ast->token, NumToken(0));
    ast = stringtoAST("MAX(2,3)");
    simplify(ast);
    IS_EQUAL(ast->token, NumToken(3));
    ast = stringtoAST("MAX(1+4,3)");
    simplify(ast);
    IS_EQUAL(ast->token, NumToken(5));
    ast = stringtoAST("MAX(1,1)");
    simplify(ast);
    IS_EQUAL(ast->token, NumToken(1));
    ast = stringtoAST("SIN(PI)+1");
    simplify(ast);
    IS_EQUAL(ast->token, NumToken(1));
    ast = stringtoAST("LOG(2,2)");
    simplify(ast);
    IS_EQUAL(ast->token, NumToken(1));
    return true;
}

bool testSimplify() {
    IS_TRUE(testBasicSimplify());
    IS_TRUE(testParentheticalSimplify());
    IS_TRUE(testFunctionSimplify());
    return true;
}

// -- evaluateAtX tests -- //

bool testEvaluateAtX() {
    std::string input = "1+X";
    ASTNode* ast = stringtoAST(input);
    IS_EQUAL(evaluateAtX(ast, 1), 2);
    IS_EQUAL(evaluateAtX(ast, 2), 3);
    IS_EQUAL(evaluateAtX(ast, 3), 4);
    IS_EQUAL(evaluateAtX(ast, -1), 0);
    ast = stringtoAST("1+X*2");
    IS_EQUAL(evaluateAtX(ast, 1), 3);
    IS_EQUAL(evaluateAtX(ast, 2), 5);
    IS_EQUAL(evaluateAtX(ast, 3), 7);
    IS_EQUAL(evaluateAtX(ast, -1), -1);
    return true;
}

// ---------------------- //

bool solverTests() {
    IS_TRUE(testCanBeSimplified());
    IS_TRUE(testSimplify());
    IS_TRUE(testEvaluateAtX());
    return true;
}
#include <string>

#include "testerutils.cpp"
#include "solver.h"

// --- simplify tests --- //

bool testBasicSimplify() {
    std::string input = "1+2";
    ASTNode* ast = stringtoAST(input);
    simplify(ast);
    IS_EQUAL(ast->token, NumToken(3));
    return true;
}

bool testSimplify() {
    IS_TRUE(testBasicSimplify());
    return true;
}

// ---------------------- //

bool solverTests() {
    IS_TRUE(testSimplify());
    return true;
}
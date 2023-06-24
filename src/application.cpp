#include <iostream>
#include <string>

#include "tokenizer.h"
#include "ast.h"
#include "solver.h"
#include "grapher.h"

#if !defined(TEST)

int main() {
    std::string inputs[] {
        "1+2", "1+2*3", "1+2*3-4",
        "1^2", "0+1^2", "E+1", "1+s",
        "1--2", "1--(-2)", "1+-2", "1-+2",
        "-1", "SIN(PI)", "MAX(2, 3)", "MAX(1+4,3)", 
        "LOG(2,2)", "LOG(4,2)",
        "(4+5)", "0-(1)", "0-(4+5)", "-(4+5)", 
        "SQRT(9+16)-(5^2/5)"
    };
    
    for (std::string input : inputs){
       ASTNode* output = stringtoAST(input);
       simplify(output);
       std::cout << input << " = " << ASTtoString(output) << std::endl;
    }

    std::string eq = "SIN(X)^2";
    ASTNode* ast = stringtoAST(eq);
    std::cout << eq << " {X = 2} = " << evaluateAtX(ast, 2) << std::endl;
    std::cout << eq << " {X = 3} = " << evaluateAtX(ast, 3) << std::endl;

    std::string inputs2[] {
        "1+2+3+(6/4)*4 - 2^X"
    };

    // for (std::string input : inputs2) {
    //     std::cout << input << std::endl;
    //     ASTNode* output = stringtoAST(input);
    //     simplify(output);
    //     std::cout << ASTtoString(output) << std::endl;
    // }

    return 0;
}

#endif
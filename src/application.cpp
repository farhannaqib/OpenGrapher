#include <iostream>
#include <string>

#include "tokenizer.h"
#include "ast.h"
#include "simplify.h"
#include "grapher.h"

#if !defined(TEST)

int main() {
    std::string inputs[] {
        "1+2", "1+2*3", "1+2*3-4",
        "1^2", "0+1^2", "E+1", "1+s",
        "1--2", "1--(-2)", "1+-2", "1-+2",
        "-1", "SIN(PI)", "MAX(2, 3)", "MAX(1+4,3)", 
        "LOG(2,2)", "LOG(4,2)",
        "(4+5)", "0-(1)", "0-(4+5)", "-(4+5)"
    };
    
    //for (std::string input : inputs){
    //    ASTNode* output = stringtoAST(input);
    //    std::cout << ASTtoString(output) << std::endl;
    //}

    std::string inputs2[] {
        "1+2+3+(6/4)*4 - 2^X"
    };

    for (std::string input : inputs2) {
        std::cout << inputs2[0] << std::endl;
        ASTNode* output = stringtoAST(input);
        simplify(output);
        std::cout << ASTtoString(output) << std::endl;
    }

    return 0;
}

#endif
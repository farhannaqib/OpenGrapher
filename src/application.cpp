#include <iostream>
#include <string>

#include <unistd.h>

#include "tokenizer.h"
#include "ast.h"
#include "solver.h"
#include "grapher.h"

#if !defined(TEST)

int main() {

    std::string input;
    Grapher grapher = Grapher();
    grapher.init();

    while (true) {
        try {
            std::cout << "Enter an equation: " << std::endl;
            std::cin >> input;
            grapher.run(input);
            break;
        } catch (std::exception& e) {
            std::cout << "Invalid equation." << std::endl;
        }
    }
    
    return 0;
}

#endif
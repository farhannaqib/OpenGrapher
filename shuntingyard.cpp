#include <iostream>
#include <string>
#include <queue>

#include "tokenizer.cpp"



int main() {
    std::string input("1+23-3*4");
    std::queue<TokenType> q;

    while (!input.empty()) {
        q.push(read(input));
    }

    while (!q.empty()) {
        // std::cout << q.front() << std::endl;
        // q.pop();
    }

    // whitespace shld be ignored
    // change strings to tokens

    return 0;
}
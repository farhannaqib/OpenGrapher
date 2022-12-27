#include <iostream>
#include <string>
#include <queue>
#include <stack>

#include "tokenizer.cpp"

void testTokenizer() {
    std::string input("1 + (2-3)/4");
    std::queue<Token> q;

    while (!input.empty()) q.push(read(input));
    
    while (!q.empty()) {
        std::cout << q.front().data << std::endl;
        q.pop();
    }
}

int main() {
    std::string input("1 + (2-3)/4");
    std::queue<Token> output;
    std::stack<Token> stack;

    while (!input.empty()) {
        Token token = read(input);
        if (token.type == TokenType::NUM) output.push(token);
    }

    return 0;
}
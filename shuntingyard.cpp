#include <iostream>
#include <string>
#include <queue>
#include <stack>

#include "tokenizer.cpp"

int main() {
    std::string input("-1+(22-3)/4");
    std::queue<Token> q;

    while (!input.empty()) {
        if (!q.empty() && (q.back().type == TokenType::RB 
        || q.back().type == TokenType::NUM)) 
        q.push(read(input, true));
        else q.push(read(input, false));
    }
    
    while (!q.empty()) {
        std::cout << q.front().data << std::endl;
        q.pop();
    }

    return 0;
}
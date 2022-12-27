#include <iostream>
#include <string>
#include <queue>

#include "tokenizer.cpp"

int main() {
    std::string input("1+2-3/4");
    std::queue<Token> q;

    while (!input.empty()) {
        q.push(read(input));
    }

    while (!q.empty()) {
        std::cout << q.front().data << std::endl;
        q.pop();
    }

    // whitespace shld be ignored
    // change strings to tokens

    return 0;
}
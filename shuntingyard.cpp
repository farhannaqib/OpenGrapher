#include <iostream>
#include <string>
#include <queue>

std::string read(std::string& input) {
    std::string token;
    if (input.front() == '+' || input.front() == '-'
    || input.front() == '*' || input.front() == '/') {
        token.append(1, input.front());
        input.erase(0, 1);
    }
    else while (input.front() > 47 && input.front() < 58) {
        token.append(1, input.front());
        input.erase(0, 1);
    }
    return token;
}

int main() {
    std::string input("1+23-3*4");
    std::queue<std::string> q;

    while (!input.empty()) {
        q.push(read(input));
    }

    return 0;
}
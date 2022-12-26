#include <vector>
#include <string>

enum class TokenType {
    ADD, SUB,
    MUL, DIV,
    NUM, EXP,
    MOD, ERROR
};

// returns token if only a single character
// was needed. returns the error token
// otherwise

TokenType read(std::string& input) {
    TokenType token = TokenType::ERROR;

    switch(input.front()) {
        case '+':
            token = TokenType::ADD;
            break;
        case '-':
            token = TokenType::SUB;
            break;
        case '*':
            token = TokenType::MUL;
            break;
        case '/':
            token = TokenType::DIV;
            break;
        case '^':
            token = TokenType::EXP;
            break;
        case '%':
            token = TokenType::MOD;
            break;
    }
    if (token != TokenType::ERROR) input.erase(0, 1);
    
    else {
        std::string t;
        while (isdigit(input.front())) {
            t.append(1, input.front());
        }
        int x = std::stoi(t);
        token = // TODO stop using enum so number is accounted for
    }

    return token;
}
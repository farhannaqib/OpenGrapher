#include <vector>
#include <string>

enum class TokenType {
    ADD, SUB,
    MUL, DIV,
    NUM, EXP,
    MOD, ERROR
};

class Token {
    public:
    TokenType type;

    void setType(TokenType t) {
        type = t;
    }
};

class NumToken : public Token {
    public:
    int num;

    void setNum(int n) {
        num = n;
    }

    NumToken() {
        setType(TokenType::NUM);
    }
 };

// returns token if only a single character
// was needed. returns the error token
// otherwise

Token read(std::string& input) {
    Token token;
    token.setType(TokenType::ERROR);

    switch(input.front()) {
        case '+':
            token.setType(TokenType::ADD);
            break;
        case '-':
            token.setType(TokenType::SUB);
            break;
        case '*':
            token.setType(TokenType::MUL);
            break;
        case '/':
            token.setType(TokenType::DIV);
            break;
        case '^':
            token.setType(TokenType::EXP);
            break;
        case '%':
            token.setType(TokenType::MOD);
            break;
    }
    if (token.type != TokenType::ERROR) input.erase(0, 1);
    
    else {
        std::string t;
        while (isdigit(input.front())) {
            t.append(1, input.front());
            input.erase(0, 1);
        }
        if (t == "") return token;

        int x = std::stoi(t);
        NumToken numToken;
        numToken.setNum(x);
        return numToken;
    }
}
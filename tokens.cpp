#include <vector>

enum class TokenType {
    ADD, SUB,
    MUL, DIV,
    NUM
};

class Token {
    public:
        std::vector<Token*> children;
        TokenType op;

        ~Token() {
            for (Token* child : children) delete child;
            children.clear();
        }
};

class NumToken : public Token {
    public: 
        int num;
        
        NumToken(int num) {
            this->num = num;
            op = TokenType::NUM;
        }
};
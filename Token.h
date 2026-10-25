#ifndef CALCULATOR_TOKEN_H
#define CALCULATOR_TOKEN_H

#include <string>

enum class TokenType { Number, Plus, Minus, Star, Slash, L_brack, R_brack, Function, End};

struct Token {
    TokenType type;
    double x{};
    std::string func;
};

#endif //CALCULATOR_TOKEN_H

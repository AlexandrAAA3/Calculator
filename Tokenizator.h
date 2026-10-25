#ifndef CALCULATOR_TOKENIZER_H
#define CALCULATOR_TOKENIZER_H

#include <string>
#include <vector>
#include "Token.h"

class Tokenizator {
public:
    Tokenizator() = default;

    ~Tokenizator() = default;

    static std::vector<Token> tokenize(const std::string &in_string);
};

#endif //CALCULATOR_TOKENIZER_H

#ifndef CALCULATOR_PARSER_H
#define CALCULATOR_PARSER_H

#include <vector>
#include <memory>
#include "Token.h"
#include "NodeParser.h"

class Parser {
    const std::vector<Token> &P_tokens;
    int pos{};

    Token peek() const;

    Token advance();

public:
    explicit Parser(const std::vector<Token> &tokens);

    std::unique_ptr<Node> parse();

private:
    std::unique_ptr<Node> parse_expression();

    std::unique_ptr<Node> parse_term();

    std::unique_ptr<Node> parse_factor();
};

#endif //CALCULATOR_PARSER_H

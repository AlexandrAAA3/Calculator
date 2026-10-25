#include "Parser.h"
#include <stdexcept>

Parser::Parser(const std::vector<Token> &tokens) : P_tokens(tokens) {
}

Token Parser::peek() const {
    if (pos >= P_tokens.size())
        return {TokenType::End, 0.0, ""};
    return P_tokens[pos];
}

Token Parser::advance() {
    if (pos >= P_tokens.size())
        return {TokenType::End, 0.0, ""};
    return P_tokens[pos++];
}

std::unique_ptr<Node> Parser::parse() {
    auto root{parse_expression()};
    if (peek().type != TokenType::End) {
        throw std::invalid_argument("ERROR_P1, unexpected token at end of input");
    }
    return root;
}

std::unique_ptr<Node> Parser::parse_expression() {
    auto left{parse_term()};
    while (true) {
        Token t{peek()};
        if (t.type == TokenType::Plus || t.type == TokenType::Minus) {
            advance();
            auto right = parse_term();
            left = std::make_unique<BinaryOpNode>(
                (t.type == TokenType::Plus) ? '+' : '-',
                std::move(left), std::move(right)
            );
        } else
            break;
    }
    return left;
}

std::unique_ptr<Node> Parser::parse_term() {
    auto left{parse_factor()};
    while (true) {
        Token t{peek()};
        if (t.type == TokenType::Star || t.type == TokenType::Slash) {
            advance();
            auto right{parse_factor()};
            left = std::make_unique<BinaryOpNode>(
                (t.type == TokenType::Star) ? '*' : '/',
                std::move(left), std::move(right)
            );
        } else {
            break;
        }
    }
    return left;
}

std::unique_ptr<Node> Parser::parse_factor() {
    Token t{peek()};

    // число
    if (t.type == TokenType::Number) {
        advance();
        return std::make_unique<NumberNode>(t.x);
    }

    // скобка
    if (t.type == TokenType::L_brack) {
        advance();
        auto expr{parse_expression()};
        Token closing{peek()};
        if (closing.type != TokenType::R_brack) {
            throw std::invalid_argument("ERROR_P2, missing closing bracket ')'");
        }
        advance();
        return expr;
    }

    // унарный минус
    if (t.type == TokenType::Minus) {
        advance();
        auto Minus_value{parse_factor()};
        return std::make_unique<UnaryMinusNode>(std::move(Minus_value));
    }

    // обработка внешних функций
    if (t.type == TokenType::Function) {
        advance();
        if (peek().type != TokenType::L_brack) {
            throw std::invalid_argument("ERROR_P3, expected '(' after function name");
        }
        advance(); // - (
        auto arg = parse_expression();
        if (peek().type != TokenType::R_brack) {
            throw std::invalid_argument("ERROR_P4, missing ')' for function");
        }
        advance(); // - )
        return std::make_unique<FunctionNode>(t.func, std::move(arg));
    }

    throw std::invalid_argument("ERROR_P5, unexpected token, expected number, '(' or unary '-'");
}

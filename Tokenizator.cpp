#include "Tokenizator.h"
#include <cctype>
#include <stdexcept>
#include <numbers>

std::vector<Token> Tokenizator::tokenize(const std::string &in_string) {
    std::string buff;
    std::vector<Token> out_vector;

    for (int i{}; i < in_string.size(); i++) {
        char c{in_string[i]};

        if (std::isdigit(c) || c == '.') {
            buff += c;
            continue;
        }

        if (std::isalpha(c)) {
            buff += c;
            continue;
        }

        if (!buff.empty()) {
            if (buff == "e") {
                out_vector.push_back({TokenType::Number, std::numbers::e, ""});
            } else if (buff == "pi") {
                out_vector.push_back({TokenType::Number, std::numbers::pi, ""});
            } else if (buff == "phi") {
                out_vector.push_back({TokenType::Number, std::numbers::phi, ""});
            } else if (std::isalpha(buff[0])) {
                out_vector.push_back({TokenType::Function, 0.0, buff});
            } else {
                try {
                    out_vector.push_back({TokenType::Number, std::stod(buff), ""});
                } catch (...) {
                    throw std::invalid_argument("ERROR_T1, incorrect number:" + buff);
                }
            }
            buff.clear();
        }

        switch (c) {
            case ' ':
            case '\t':
                break;
            case '+':
                out_vector.push_back({TokenType::Plus, 0.0, ""});
                break;
            case '-':
                out_vector.push_back({TokenType::Minus});
                break;
            case '*':
                out_vector.push_back({TokenType::Star});
                break;
            case '/':
                out_vector.push_back({TokenType::Slash});
                break;
            case '(':
                out_vector.push_back({TokenType::L_brack});
                break;
            case ')':
                out_vector.push_back({TokenType::R_brack});
                break;
            default:
                //throw std::invalid_argument("ERROR_T2, incorrect character: " + std::string(1, c));
                out_vector.push_back({TokenType::Function, 0.0, std::string(1, c)});
        }
    }

    if (!buff.empty()) {
        if (buff == "e") {
            out_vector.push_back({TokenType::Number, std::numbers::e, ""});
        } else if (buff == "pi") {
            out_vector.push_back({TokenType::Number, std::numbers::pi, ""});
        } else if (buff == "phi") {
            out_vector.push_back({TokenType::Number, std::numbers::phi, ""});
        } else if (std::isalpha(buff[0]))
            out_vector.push_back({TokenType::Function, 0.0, buff});
        else
            out_vector.push_back({TokenType::Number, std::stod(buff), ""});
    }

    out_vector.push_back({TokenType::End, 0.0, ""});

    return out_vector;
}

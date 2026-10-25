#ifndef CALCULATOR_NODEPARSER_H
#define CALCULATOR_NODEPARSER_H

#include <memory>
#include <stdexcept>
#include <string>
#include <functional>
#include <unordered_map>

using PluginFunc = std::function<double(double)>;

extern std::unordered_map<std::string, PluginFunc> functionTable;

class Node {
public:
    virtual ~Node() = default;

    virtual double evaluate() const = 0;
};

class NumberNode : public Node {
    double NNValue;

public:
    explicit NumberNode(double value) : NNValue(value) {
    }

    double evaluate() const override { return NNValue; }
};

class BinaryOpNode : public Node {
    char bin_operation;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

public:
    BinaryOpNode(char op, std::unique_ptr<Node> l, std::unique_ptr<Node> r)
        : bin_operation(op), left(std::move(l)), right(std::move(r)) {
    }

    double evaluate() const override {
        double l = left->evaluate();
        double r = right->evaluate();
        switch (bin_operation) {
            case '+': return l + r;
            case '-': return l - r;
            case '*': return l * r;
            case '/':
                if (r == 0.0) throw std::domain_error("ERROR_NP1, division by zero");
                return l / r;
            default: throw std::runtime_error("ERROR_NP2, unknown operator");
        }
    }
};

class UnaryMinusNode : public Node {
    std::unique_ptr<Node> UMN_arg;

public:
    explicit UnaryMinusNode(std::unique_ptr<Node> a) : UMN_arg(std::move(a)) {
    }

    double evaluate() const override { return -UMN_arg->evaluate(); }
};

// Узел для вызова функций из плагинов
class FunctionNode : public Node {
    std::string funcName;
    std::unique_ptr<Node> arg;

public:
    FunctionNode(std::string name, std::unique_ptr<Node> a)
        : funcName(std::move(name)), arg(std::move(a)) {
    }

    double evaluate() const override {
        auto it = functionTable.find(funcName);
        if (it == functionTable.end()) {
            throw std::runtime_error("ERROR_NP3, unknown function: " + funcName);
        }
        return it->second(arg->evaluate());
    }
};

#endif //CALCULATOR_NODEPARSER_H

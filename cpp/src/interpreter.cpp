#include "interpreter.h"
#include <stdexcept>

/*
The Visitor Pattern:

evaluate → 
        node.accept() → 
            v.visit(*this) → 
                Interpreter::visit(ConcreteType&). 

Four hops, then the work happens.

*/

Interpreter::Interpreter() {}

const std::unordered_map<
    TokenType, std::function<std::variant<double, bool>(double, double)>> 
    Interpreter::binary_op_map = {
        { TokenType::PLUS, [](double a, double b) { return a + b; } },
        { TokenType::MINUS, [](double a, double b) { return a - b; } },
        { TokenType::MULTIPLY, [](double a, double b) { return a * b; } },
        { TokenType::DIVIDE, [](double a, double b) { return a / b; } },
        { TokenType::LESS_THAN, [](double a, double b) { return a < b; } },
        { TokenType::GREATER_THAN, [](double a, double b) { return a > b; } },
        { TokenType::LESS_THAN_EQUAL, [](double a, double b) { return a <= b; } },
        { TokenType::GREATER_THAN_EQUAL, [](double a, double b) { return a >= b; }},
        { TokenType::EQUAL_TO, [](double a, double b) { return a == b; } },
        { TokenType::NOT_EQUAL, [](double a, double b) { return a != b; } },
    };

// Entry point ------------------------------

void Interpreter::evaluate(ASTNode& node) {
    node.accept(*this);
}


// Evauluators ------------------------------

void Interpreter::visit(NumberNode& node) {
    result = node.number;
}

void Interpreter::visit(IdentifierNode& node) {
    auto it = symbol_table.find(node.identifier);

    if (it != symbol_table.end()) {
        result = it->second; 
    } else {
        throw std::runtime_error("ERROR: " 
            + node.identifier + " does not exist. ");
    }
}

void Interpreter::visit(BinaryOpNode& node) {

}

void Interpreter::visit(UnaryOpNode& node) {

}

void Interpreter::visit(AssignNode& node) {

}

void Interpreter::visit(PrintNode& node) {

}

void Interpreter::visit(BlockNode& node) {

}

void Interpreter::visit(WhileNode& node) {

}

void Interpreter::visit(ConditionalNode& node) {

}
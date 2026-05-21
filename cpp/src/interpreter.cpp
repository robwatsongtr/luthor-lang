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
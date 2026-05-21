#include "interpreter.h"

Interpreter::Interpreter() {}

void Interpreter::evaluate(ASTNode& node) {
    node.accept(*this);
}
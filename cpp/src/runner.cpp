#include "runner.h"

// Runner owns the ProgramNode via unique_ptr, takes ownership 
// through the constructor with std::move, and run() loops 
// calling accept() on each statement — exactly the shape main.cpp 
// expects.

Runner::Runner(std::unique_ptr<ProgramNode> program) 
    : program(std::move(program)) {}

void Runner::run(Visitor& v) {
    for (const auto& stmt : program->statements) {
        stmt->accept(v); 
    }
}
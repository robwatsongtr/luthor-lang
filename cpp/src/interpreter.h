#pragma once
#include "nodes.h"

#include <variant>
#include <unordered_map> 

class Interpreter: public Visitor {
public:
    Interpreter(std::unique_ptr<ProgramNode> program);   

    void run();

private:
    std::unique_ptr<ProgramNode> program; 
    std::variant<double, std::string> result; 

    std::unordered_map<
        std::string, std::variant<double, std::string>> symbol_table;  

    void evaluate(ASTNode&); 

    void visit(UnaryOpNode&);
    void visit(BinaryOpNode&);

};
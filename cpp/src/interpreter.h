#pragma once
#include "nodes.h"

#include <variant>
#include <unordered_map> 

class Interpreter: public Visitor {
public:
    Interpreter();

private:
    std::variant<double, std::string> result; 

    std::unordered_map<
        std::string, std::variant<double, std::string>> symbol_table;  

    void evaluate(ASTNode&); 

    void visit(UnaryOpNode&);
    void visit(BinaryOpNode&);
    void visit(NumberNode&);
    void visit(IdentifierNode&);
    void visit(AssignNode&);
    void visit(BlockNode&);
    void visit(ConditionalNode&);
    void visit(WhileNode&);
    void visit(PrintNode&);
    void visit(ProgramNode&);
    
};
#pragma once
#include "tokens.h"

#include <memory>
#include <vector>
#include <string>

struct ASTNode {
    // virtual on the destructor tells the runtime  "when you destroy 
    // through this base pointer, look up the vtable at runtime to 
    // find the real destructor
    virtual ~ASTNode() = default; 
};

struct UnaryOpNode : public ASTNode {
    TokenType op_type;
    std::unique_ptr<ASTNode> operand;

    UnaryOpNode(TokenType op_type, std::unique_ptr<ASTNode> operand) 
        : op_type(op_type), operand(std::move(operand)) {}
};

struct BinaryOpNode : public ASTNode {
    TokenType op_type;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

    BinaryOpNode(TokenType op_type, std::unique_ptr<ASTNode> left, 
          std::unique_ptr<ASTNode> right) 
        : op_type(op_type), left(std::move(left)), right(std::move(right)) {}
};

struct NumberNode : public ASTNode {
    double number; 

    NumberNode(double number) : number(number) {}
}; 

struct IdentifierNode : public ASTNode {
    std::string identifier; 

    IdentifierNode(std::string identifier) : identifier(identifier) {}
};

struct AssignNode : public ASTNode {
    std::string var_name;
    std::unique_ptr<ASTNode> expression;

    AssignNode(std::string var_name, std::unique_ptr<ASTNode> expression)
        : var_name(var_name), expression(std::move(expression)) {}
};
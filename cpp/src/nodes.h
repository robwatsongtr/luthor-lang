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
    virtual std::string toString() const = 0;   
};


struct UnaryOpNode : public ASTNode {
    Token op_type;
    std::unique_ptr<ASTNode> operand;

    UnaryOpNode(const Token& op_type, std::unique_ptr<ASTNode> operand) 
        : op_type(op_type), operand(std::move(operand)) {}

    std::string toString() const override {
        return "Unary(" + op_type.lexeme + ", " + operand->toString() + ")";
    }
};


struct BinaryOpNode : public ASTNode {
    Token op_type;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

    BinaryOpNode(const Token& op_type, std::unique_ptr<ASTNode> left, 
          std::unique_ptr<ASTNode> right) 
        : op_type(op_type), left(std::move(left)), right(std::move(right)) {}

    std::string toString() const override {
        return "BinaryOp(" + op_type.lexeme + ", " 
                           + left->toString() + ", " 
                           + right->toString() + ")";
    }
};

struct NumberNode : public ASTNode {
    double number; 

    NumberNode(double number) : number(number) {}
}; 


struct IdentifierNode : public ASTNode {
    std::string identifier; 

    IdentifierNode(const std::string& identifier) : identifier(identifier) {}
};


struct AssignNode : public ASTNode {
    std::string var_name;
    std::unique_ptr<ASTNode> expression;

    AssignNode(const std::string& var_name, std::unique_ptr<ASTNode> expression)
        : var_name(var_name), expression(std::move(expression)) {}
};


struct BlockNode: public ASTNode {
    std::vector<std::unique_ptr<ASTNode>> statements; 

    BlockNode(std::vector<std::unique_ptr<ASTNode>> statements) 
        : statements(std::move(statements)) {}
};


struct ConditionalNode: public ASTNode {
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<ASTNode> then_block;
    std::unique_ptr<ASTNode> else_block;
    
    ConditionalNode(std::unique_ptr<ASTNode> condition, 
                    std::unique_ptr<ASTNode> then_block, 
                    std::unique_ptr<ASTNode> else_block)
        : condition(std::move(condition)),
          then_block(std::move(then_block)),
          else_block(std::move(else_block)) {}
};


struct WhileNode: public ASTNode {
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<ASTNode> body_block;

    WhileNode(std::unique_ptr<ASTNode> condition,
              std::unique_ptr<ASTNode> body_block )
        : condition(std::move(condition)), 
          body_block(std::move(body_block)) {}
};


struct PrintNode: public ASTNode {
    std::unique_ptr<ASTNode> expression;

    PrintNode(std::unique_ptr<ASTNode> expression) 
        : expression(std::move(expression)) {}
};


struct ProgramNode: public ASTNode {
    std::vector<std::unique_ptr<ASTNode>> statements; 

    ProgramNode(std::vector<std::unique_ptr<ASTNode>> statements) 
        : statements(std::move(statements)) {}
};

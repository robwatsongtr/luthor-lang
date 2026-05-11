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




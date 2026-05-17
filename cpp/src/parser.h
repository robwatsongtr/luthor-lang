#pragma once 
#include "tokens.h"
#include "nodes.h"

#include <string>
#include <vector>
#include <optional>

class Parser {
public:
    // constructor definition 
    Parser(const std::vector<Token>& tok_stream);

    // kicks off the parsing 
    std::unique_ptr<ASTNode> program();

private:
    int tok_pos; 
    const std::vector<Token>& tok_stream; 
    static const std::vector<TokenType> comparison_tokens;

    void advance();
    std::optional<Token> token_peek();
    Token consume(TokenType expected_token);

    // EBNF methods: 
    std::unique_ptr<ASTNode> statement();
    std::unique_ptr<ASTNode> assignment();
    std::unique_ptr<ASTNode> conditional();
    std::unique_ptr<ASTNode> print_statement();
    std::unique_ptr<ASTNode> while_statement();
    std::unique_ptr<ASTNode> block();

    std::unique_ptr<ASTNode> expression();
    std::unique_ptr<ASTNode> comparison();
    std::unique_ptr<ASTNode> term();
    std::unique_ptr<ASTNode> factor();
    std::unique_ptr<ASTNode> unary();
    std::unique_ptr<ASTNode> primary();
};


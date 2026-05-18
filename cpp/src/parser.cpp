#include "parser.h"

#include <stdexcept>
#include <sstream>


Parser::Parser(const std::vector<Token>& tok_stream) : 
    tok_stream(tok_stream), tok_pos(0) {}

const std::vector<TokenType> Parser::comparison_tokens = {
    TokenType::LESS_THAN,
    TokenType::GREATER_THAN,
    TokenType::LESS_THAN_EQUAL,
    TokenType::GREATER_THAN_EQUAL,
    TokenType::EQUAL_TO,
    TokenType::NOT_EQUAL
};

void Parser::advance() { 
    tok_pos++; 
}

std::optional<Token> Parser::token_peek() {
    auto token = tok_stream[tok_pos];

    if (token.token_type != TokenType::END_OF_FILE ) {
        return token; 
    } else {
        return std::nullopt; 
    }
}

Token Parser::consume(TokenType expected_token) {
    if(!token_peek()) {
        std::ostringstream oss;
        oss << "Unexpected end of input at " << tok_pos;     
        throw std::runtime_error(oss.str());
    } 

    auto token = token_peek().value(); 

    if (token.token_type == expected_token) {
        advance();
        return token;
    } else {
        std::ostringstream oss;
        oss << "Unexpected token '" << token.lexeme 
            << "' at " << tok_pos;      
        throw std::runtime_error(oss.str());
    }
}

std::unique_ptr<ASTNode> Parser::program() {
    std::vector<std::unique_ptr<ASTNode>> statements;

    while (token_peek()) {
        auto stmnt = statement();
        statements.push_back(std::move(stmnt));
    }

    //  make_unique → new → malloc → OS
    auto program = std::make_unique<ProgramNode>(
        std::move(statements)
    );

    return program;
}

std::unique_ptr<ASTNode> Parser::statement() {
    switch (token_peek().value().token_type) {
        case TokenType::KNOW:
            return assignment();

        case TokenType::SUPPOSE:
            return conditional();

        case TokenType::DOOM:
            return print_statement();

        case TokenType::CRIME:
            return while_statement();

        default:
            return expression();     
    };
}
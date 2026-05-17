#include "parser.h"

#include <stdexcept>

Parser::Parser(const std::vector<Token>& tok_stream) : 
    tok_stream(tok_stream), tok_pos(0) {}

const std::vector<TokenType> comparison_tokens = {
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
#pragma once

#include <string>

enum class TokenType {
    // single char symbols
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    L_PARENS,
    R_PARENS,
    LESS_THAN,
    GREATER_THAN,

    // multi char symbols
    LESS_THAN_EQUAL,
    GREATER_THAN_EQUAL,
    EQUAL_TO,
    NOT_EQUAL,

    // value carrying
    NUMBER,
    IDENTIFIER,

    // keywords
    KNOW,
    SUPPOSE,
    DOOM,
    CRIME,

    OTHERWISE,
    END,

    END_OF_FILE
};

struct Token {
    TokenType token_type;
    std::string lexeme;
};
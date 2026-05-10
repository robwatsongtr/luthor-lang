#include "lexer.h"
#include "tokens.h"

#include <optional>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>

Lexer::Lexer(std::string stream) : stream(stream), pos(0) {}

const std::unordered_map<std::string, TokenType> Lexer::single_char_map = {
    { "+", TokenType::PLUS },
    { "-", TokenType::MINUS },
    { "*", TokenType::MULTIPLY },
    { "/", TokenType::DIVIDE },
    { "(", TokenType::L_PARENS },
    { ")", TokenType::R_PARENS },
    { ">", TokenType::GREATER_THAN },
    { "<", TokenType::LESS_THAN }
};

const std::vector<std::string> Lexer::multi_start = { "<", ">", "=", "!" };

const std::unordered_map<std::string, TokenType> Lexer::keyword_map = {
    { "know", TokenType::KNOW },
    { "suppose", TokenType::SUPPOSE },
    { "otherwise", TokenType::OTHERWISE },
    { "end", TokenType::END },
    { "doom", TokenType::DOOM },
    { "crime", TokenType::CRIME }
};

void Lexer::advance() {
    pos++;
}

void Lexer::advance_twice() {
    pos += 2; 
}

// helper func to wrap cast for std::isspace because char can be signed
bool Lexer::is_space(char c) {
    return std::isspace(static_cast<unsigned char>(c));
}

std::optional<char> Lexer::peek() {
    if (pos < stream.size()) {
        return stream[pos];
    } else {
        return std::nullopt;
    }
}

std::optional<char> Lexer::peek_next() {
    if ((pos + 1) < stream.size()) {
        return stream[pos + 1];
    } else {
        return std::nullopt;
    }
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (true) {
        if (!peek()) {
            Token token{ "", TokenType::END_OF_FILE }; 
            tokens.push_back(token);
            // we're done!
            return tokens;

        } else if (is_space(peek().value())) {
            advance(); 

        } else if (contains(multi_start, peek().value()) && peek_next().value() == '=') {
            if (peek().value() == '<') {
                std::string lexeme = "<=";
                Token token{ lexeme, TokenType::LESS_THAN_EQUAL };
                tokens.push_back(token);
                advance_twice();
            }    
        }




    }
}


// std::find(multi_start.begin(), multi_start.end(), peek().value()) != multi_start.end() 
// && peek_next().value() == '='
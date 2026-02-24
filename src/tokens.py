from enum import Enum, auto

class TokenType(Enum):
    NUMBER = auto()
    PLUS = auto()
    MINUS = auto()
    MULTIPLY = auto()
    DIVIDE = auto()
    L_PARENS = auto()
    R_PARENS = auto()
    EOF = auto()


class Token:
    def __init__(self, lexeme, token_type):
        self.token_type = token_type
        self.lexeme = lexeme 

    def __repr__(self):
        return f"Token(token_type='{self.token_type}', lexeme='{self.lexeme}')"
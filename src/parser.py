import operator
from .tokens import TokenType
from .nodes import BinaryOpNode, NumberNode


class Parser:
    def __init__(self, token_stream):
        self.tok_stream = token_stream
        self.tok_pos = 0

    def advance(self):
        self.tok_pos += 1

    def token_peek(self):
        token = self.tok_stream[self.tok_pos]

        return token if token.token_type != TokenType.EOF else None 

    def consume(self, expected_token):
        token = self.token_peek()

        if token.token_type == expected_token:
            self.advance()

            return token 
        else:
            raise ValueError(
                f"Unexpected token '{token.token_type}' at {self.tok_pos}"
            )

    # ------------ Build the Parse Tree, Recursive Descent ------------

    """
    expression → term
        term       → factor (('+' | '-') factor)*
        factor     → primary (('*' | '/') primary)*
        primary    → NUMBER | '(' expression ')'    
    """

    def expression(self):
        root = self.term()

        return root  

    def term(self):
        root = self.factor()
 
        while self.token_peek() and (
            self.token_peek().token_type in (TokenType.PLUS, TokenType.MINUS)
        ):
            op = self.token_peek()
            self.consume(op.token_type) # does validation and advances
            r_node = self.factor()
            root = BinaryOpNode(op, root, r_node)

        return root 

        
    def factor(self):
        root = self.primary()

        while self.token_peek() and (
            self.token_peek().token_type in (TokenType.MULTIPLY, TokenType.DIVIDE)
        ):
            op = self.token_peek()
            self.consume(op.token_type) 
            r_node = self.primary()
            root = BinaryOpNode(op, root, r_node)

        return root 


    def primary(self):
        if self.token_peek().token_type == TokenType.NUMBER:
            num = self.token_peek()
            self.consume(num.token_type)

            return NumberNode(float(num.lexeme))
        else:
            # handle parens, creating a nested parse of everything inside them
            if self.token_peek().token_type == TokenType.L_PARENS:
                self.consume(TokenType.L_PARENS)
                result = self.expression()
                self.consume(TokenType.R_PARENS)

                return result
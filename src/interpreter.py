import operator
from tokens import TokenType
from nodes import NumberNode


class Interpreter:
    def __init__(self, root):
        self.root = root

    op_map = {
        TokenType.PLUS: operator.add,
        TokenType.MINUS: operator.sub,
        TokenType.MULTIPLY: operator.mul,
        TokenType.DIVIDE: operator.truediv
    }

    def evaluate(self):
        # leaf will always be a number node so its our base case check 
        if isinstance(self.root, NumberNode):
            return self.root.number 
        
        left = self.evaluate(self.root.left)
        right = self.evaluate(self.root.right)

        # the call stack unwinding does the operations
        return self.op_map[self.root.op_type.token_type](left, right)
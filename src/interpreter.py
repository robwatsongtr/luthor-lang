import operator
from .tokens import TokenType
from .nodes import NumberNode


class Interpreter:
    def __init__(self, root):
        self.root = root

    op_map = {
        TokenType.PLUS: operator.add,
        TokenType.MINUS: operator.sub,
        TokenType.MULTIPLY: operator.mul,
        TokenType.DIVIDE: operator.truediv
    }

    def evaluate(self, node=None):
        if node is None:
            node = self.root

        # leaf will always be a number node so its our base case check
        if isinstance(node, NumberNode):
            return node.number

        left = self.evaluate(node.left)
        right = self.evaluate(node.right)

        # the call stack unwinding does the operations
        return self.op_map[node.op_type.token_type](left, right)
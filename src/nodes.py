class BinaryOpNode:
    def __init__(self, op_type=None, left=None, right=None):
        self.op_type = op_type
        self.left = left
        self.right = right

    def __repr__(self):
        return f"BinaryOp({self.op_type.lexeme}, {self.left}, {self.right})"


class NumberNode:
    def __init__(self, number=0):
        self.number = number

    def __repr__(self):
        return f"Num({self.number})"
class BinaryOpNode:
    def __init__(self, op_type=None, left=None, right=None):
        self.op_type = op_type
        self.left = left
        self.right = right


class NumberNode:
    def __init__(self, number=0):
        self.number = number 
import operator
from .tokens import TokenType
from .nodes import (
    NumberNode,
    BinaryOpNode,
    IdentifierNode,
    AssignNode,
    BlockNode,
    ConditionalNode,
    PrintNode,
    ProgramNode
)


class Interpreter:
    def __init__(self, program):
        self.program = program
        self.symbol_table = {}

    op_map = {
        TokenType.PLUS: operator.add,
        TokenType.MINUS: operator.sub,
        TokenType.MULTIPLY: operator.mul,
        TokenType.DIVIDE: operator.truediv
    }

    def run(self):
        for statement in self.program.statements:
            self.evaluate(statement)


    def evaluate(self, node):
        if isinstance(node, NumberNode):
            return node.number 
        
        elif isinstance(node, IdentifierNode):
            if node.identifier in self.symbol_table:
                return self.symbol_table[node.identifier]
            else:
                raise ValueError(
                    f"ERROR: '{node.identifier}' does not exist"
                )
            
        elif isinstance(node, BinaryOpNode):
            pass

    

    # def evaluate(self, node=None):
    #     if node is None:
    #         node = self.program

    #     # leaf will always be a number node so its our base case check
    #     if isinstance(node, NumberNode):
    #         return node.number

    #     left = self.evaluate(node.left)
    #     right = self.evaluate(node.right)

    #     # the call stack unwinding does the operations
    #     return self.op_map[node.op_type.token_type](left, right)
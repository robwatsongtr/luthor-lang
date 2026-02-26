from src.lex_luthor import Lexer
from src.parser import Parser
from src.interpreter import Interpreter


def main():
    # Expression to evaluate
    expression = '3 + 8 - (2 + 12) * 2'
    print(f"Expression: {expression}")
    print()

    print("Step 1: Lexical Analysis (Tokenization)")
    print()
    lexer = Lexer(expression)
    tokens = lexer.tokenize()

    for token in tokens:
        print(f"  {token}")
    print()

    print("Step 2: Syntax Analysis (Parsing)")
    parser = Parser(tokens)
    ast = parser.expression()
    print(f"  AST root: {ast}")
    print()

    print("Step 3: Evaluation (Interpretation)")
    interpreter = Interpreter(ast)
    result = interpreter.evaluate()
    print(f"  Result: {result}")
    print()


if __name__ == '__main__':
    main()

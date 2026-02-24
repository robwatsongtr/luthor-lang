from src.lex_luthor import Lexer
from src.parser import Parser
from src.interpreter import Interpreter


def main():
    # Expression to evaluate
    expression = '3 + 4 - (2/3)'

    print(f"Input expression: {expression}")
    print()

    # Step 1: Lexical Analysis
    print("Step 1: Lexical Analysis (Tokenization)")
    print("-" * 40)
    lexer = Lexer(expression)
    tokens = lexer.tokenize()

    for token in tokens:
        print(f"  {token}")
    print()

    # Step 2: Syntax Analysis (Parsing)
    print("Step 2: Syntax Analysis (Parsing)")
    print("-" * 40)
    parser = Parser(tokens)
    ast = parser.expression()
    print(f"  AST root: {ast}")
    print()

    # Step 3: Evaluation (Interpretation)
    print("Step 3: Evaluation (Interpretation)")
    print("-" * 40)
    interpreter = Interpreter(ast)
    result = interpreter.evaluate()
    print(f"  Result: {result}")
    print()

    # Display final answer
    print("=" * 40)
    print(f"{expression} = {result}")
    print("=" * 40)


if __name__ == '__main__':
    main()

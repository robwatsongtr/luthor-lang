from src.lexer import Lexer
from src.parser import Parser
from src.interpreter import Interpreter
# from fixtures.lexer_examples import lex_examples


def main():

    source = """

    know x 3
    suppose x > 5
        doom 100
    end
    otherwise
        doom 200
    end

    """

    source_loop_test = """

    know x 0
    crime x < 5
      doom x
      know x x + 1
    end

    """

    print(f"Expression: {source_loop_test}")
    print()

    print("Step 1: Lexical Analysis (Tokenization)")
    print()
    lexer = Lexer(source_loop_test)
    tokens = lexer.tokenize()

    for token in tokens:
        print(f"  {token}")
    print()

    print("Step 2: Syntax Analysis (Parsing)")
    parser = Parser(tokens)
    tree = parser.program()
    print(f"root: {tree}")
    print()

    print("Step 3: Evaluation (Interpretation)")
    interpreter = Interpreter(tree)
    output = interpreter.run()
    print(output)
    print()


if __name__ == '__main__':
    main()

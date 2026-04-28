from src.lexer import Lexer
from src.parser import Parser
from src.interpreter import Interpreter
# from fixtures.lexer_examples import lex_examples


def main():

    quadratic = """
    know i 0
    crime i < 1000
        know j 0
        crime j < 1000
            know result i * j
            know j j + 1
        end
        know i i + 1
    end
    doom i

    """

    source = """

    know x 3
    suppose x > 5
        doom 100
    end
    otherwise
        doom 200
    end

    """

    source2 = """

    know x 0
    crime x < 5
      doom x
      know x x + 1
    end

    """

    source3 = """

    know x -10
    doom x

    doom -5

    doom -(3 + 2)

    know y 20
    doom y + -5 

    """

    print(f"Program: {source3}")
    print()

    print("Step 1: Lexical Analysis (Tokenization)")
    print()
    lexer = Lexer(source3)
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

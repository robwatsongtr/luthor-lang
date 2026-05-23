#include "src/interpreter.h"
#include "src/lexer.h"
#include "src/parser.h"
#include "src/runner.h"

#include <string> 
#include <iostream>

/*
Example, to pass in an Interpreter as a visitor:
                                                                                                            
  Interpreter interp;                                                                                                                       
  Runner runner(std::move(program));                                                                                                      
  runner.run(interp);

*/

int main () {
    std::string fib =  R"(                                                                                                                  
        know i 0                                                                                                                                  
        know a 0
        know b 1                                                                                                                                  
        crime i < 10    
            doom a                                                                                                                                
            know temp b 
            know b a + b                                                                                                                          
            know a temp
            know i i + 1                                                                                                                          
        end         
    )";

    std::cout << "Program: " << fib << "\n";
    std::cout << "\n"; 

    std::cout << "Step 1: Lexical Analysis (Tokenization)"<< "\n";
    std::cout << "\n";
    Lexer lexer(fib); 
    auto tokens = lexer.tokenize();

    for (auto tok : tokens) {
        std::cout << " " << tok.toString() << "\n";
    }
    std::cout << "\n";

    std::cout << "Step 2: Syntax Analysis (Parsing)"<< "\n";
    std::cout << "\n";
    Parser parser(tokens); 
    auto ast = parser.program();
    std::cout << " " << ast->toString() << "\n";

    std::cout << "Step 3: Interpreter evaluation"<< "\n";
    std::cout << "\n";
    Interpreter interpreter; 
    Runner runner(std::move(ast));
    runner.run(interpreter);

}
#pragma once 
#include "interpreter.h"

/*
Example, to pass in an Interpreter as a visitor:
                                                                                                            
  Interpreter interp;                                                                                                                       
  Runner runner(std::move(program));                                                                                                      
  runner.run(interp);

*/

class Runner {
public:
    Runner(std::unique_ptr<ProgramNode> program);

    void run(Visitor&);
private:
    std::unique_ptr<ProgramNode> program;

};
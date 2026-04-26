# Luthor Language — Project Context

## Overview
Luthor is a custom interpreted programming language built in Python as a learning project. The goal is to understand the core source-to-output pipeline: lexing, parsing, AST construction, and tree-walking interpretation. Keywords are themed after Lex Luthor, inspired by the fact that a core language component is called a *lexer*.

AGENTS / LLM : DO NOT GIVE CODE, JUST GUIDANCE LIKE A TEACHER.

---

## Architecture

The pipeline is: **source string → Lexer → token stream → Parser → AST → Interpreter → output**

### Files
- `tokens.py` — `TokenType` enum and `Token` class
- `lexer.py` — `Lexer` class
- `nodes.py` — AST node classes
- `parser.py` — `Parser` class (recursive descent)
- `interpreter.py` — `Interpreter` class (tree walker)

---

## What's Done

### Tokens (`tokens.py`)
- Arithmetic: `PLUS`, `MINUS`, `MULTIPLY`, `DIVIDE`
- Grouping: `L_PARENS`, `R_PARENS`
- Comparison: `LESS_THAN`, `GREATER_THAN`, `LESS_THAN_EQUAL`, `GREATER_THAN_EQUAL`, `EQUAL_TO`, `NOT_EQUAL`
- Values: `NUMBER`, `IDENTIFIER`
- Keywords: `KNOW` (assignment), `SUPPOSE` (if), `OTHERWISE` (else), `END` (block delimiter), `DOOM` (print), `CRIME` (while loop)
- `EOF` 

### Lexer (`lexer.py`)
- Handles whitespace, single-char tokens via `single_char_map`
- Multi-character comparison tokens via `peek`/`peek_next` state transition
- Keywords via `keyword_map`, falls back to `IDENTIFIER`
- Numeric literals
- Raises `ValueError` on unexpected characters

### Parser (`parser.py`)
- Recursive descent
- Precedence chain: `expression → comparison → term → factor → primary`
- `primary` handles `NUMBER`, `IDENTIFIER`, and parenthesized expressions
- `comparison` handles all six comparison operators via class-level `comparison_tokens` list
- `assignment` method — consumes `KNOW`, `IDENTIFIER`, then parses expression; not part of precedence chain
- `block` method — loops collecting statements until `END`, returns `BlockNode`
- `consume` does validation and advances in one step; includes `None` guard for unexpected EOF
- `conditional` method — consumes `SUPPOSE`, parses condition expression, then-block, optional `OTHERWISE` else-block
- `while_statement` method — consumes `CRIME`, parses condition expression and body block, returns `WhileNode`
- `print_statement` method — consumes `DOOM`, parses expression, returns `PrintNode`
- `statement` method — dispatcher; peeks at current token and routes to `assignment`, `conditional`, `while_statement`, `print_statement`, or `expression`
- `program` method — entry point; loops collecting statements until EOF, returns `ProgramNode`

### Nodes (`nodes.py`)
- `BinaryOpNode(op, left, right)` — binary operations
- `NumberNode(number)` — numeric literals
- `IdentifierNode(identifier)` — leaf node for variable references
- `AssignNode(var_name, expression)` — stores variable name and expression to assign
- `BlockNode(statements)` — container for a list of statement nodes
- `ConditionalNode(condition, then_block, else_block)` — conditional branching; else_block can be `None`
- `WhileNode(condition, body_block)` — while loop; re-evaluates condition each iteration
- `PrintNode(expression)` — wraps an expression to print
- `ProgramNode(statements)` — top-level container for all statements

### Interpreter (`interpreter.py`)
- Tree walker using `isinstance` dispatch chain
- `symbol_table` — plain dict for variable storage, initialized in `__init__`
- `op_map` — maps `TokenType` to Python `operator` functions (arithmetic + comparison operators)
- `run()` method — entry point; loops through `program.statements` and calls `evaluate()` on each
- `evaluate(node)` method — type-based dispatch that handles all node types:
  - `NumberNode` — returns the numeric value (base case)
  - `IdentifierNode` — looks up variable in symbol table, raises error if undefined
  - `BinaryOpNode` — recursively evaluates left/right children, applies operator
  - `AssignNode` — evaluates expression, stores result in symbol table (mutation enables loops)
  - `PrintNode` — evaluates expression, prints result to console
  - `BlockNode` — loops through statements, evaluates each
  - `ConditionalNode` — evaluates condition, branches to then/else blocks based on truthiness
  - `WhileNode` — evaluates condition, loops body while truthy, re-evaluates condition each iteration

---

## Current EBNF

```
program              → statement*
statement            → assignment | conditional | while_statement | print_statement | expression_statement
assignment           → 'know' IDENTIFIER expression
conditional          → 'suppose' expression block ('otherwise' block)?
while_statement      → 'crime' expression block
print_statement      → 'doom' expression
block                → statement* 'end'
expression_statement → expression
expression           → comparison
comparison           → term (('==' | '!=' | '<' | '>' | '<=' | '>=') term)*
term                 → factor (('+' | '-') factor)*
factor               → unary (('*' | '/') unary)*
unary                → '-' unary | primary 
primary              → NUMBER | IDENTIFIER | '(' expression ')'
```

---

## Completed Implementation ✓

**The interpreter is fully functional and Turing complete.** All core features have been implemented:

1. ~~**Extend `primary`** to handle `IDENTIFIER` tokens → needs `IdentifierNode`~~ ✓
2. ~~**Add `comparison` method** to parser, update `expression` to call it~~ ✓
3. ~~**Add `AssignNode`**, implement `assignment` parser method~~ ✓
4. ~~**Add `BlockNode`**, implement `block` parser method~~ ✓
5. ~~**Add `ConditionalNode`**, implement `conditional` parser method~~ ✓
6. ~~**Add `PrintNode`**, add `DOOM` keyword/token, implement `print_statement`~~ ✓
7. ~~**Add `statement` and `program` methods** to parser~~ ✓
8. ~~**Add symbol table** (plain dict) to interpreter for variable state~~ ✓
9. ~~**Extend interpreter** with isinstance branches for all new node types~~ ✓
10. ~~**Add `WhileNode` and `crime` keyword for looping**~~ ✓

### Current Capabilities

The language now supports:
- **Variable assignment** — `know x 10` stores values in the symbol table
- **Arithmetic operations** — `+`, `-`, `*`, `/` with correct precedence
- **Comparison operations** — `<`, `>`, `<=`, `>=`, `==`, `!=`
- **Conditional branching** — `suppose`/`otherwise`/`end` blocks with optional else
- **While loops** — `crime` keyword for iteration with condition checking
- **Print statements** — `doom` outputs expression results
- **Nested expressions** — parentheses and arbitrary nesting depth
- **Block scoping** — statements grouped in blocks for control flow

**The language is Turing complete** — with variables, conditionals, and loops, it can compute any computable function.

**Total implementation: ~500 lines of Python**

### Example Programs

**Conditional:**
```
know x 10
know y 5
suppose x > y
    doom x
end
otherwise
    doom y
end
```
Output: `> 10.0`

**Loop:**
```
know x 0
crime x < 5
    doom x
    know x x + 1
end
```
Output: `> 0.0` `> 1.0` `> 2.0` `> 3.0` `> 4.0`

---

## Future Additions

Potential enhancements for further learning:

- **Functions** — define reusable code blocks with parameters and return values; requires call stack and scope management
- **Strings** — add string literals, concatenation, and string operations
- **Boolean literals** — explicit `true`/`false` keywords (currently relying on numeric truthiness)
- **Logical operators** — `and`, `or`, `not` for boolean logic
- **Arrays/Lists** — data structures for collections
- **For loops** — syntactic sugar for common iteration patterns
- **Unary operators** — support `-x` (negation) by adding unary rule to grammar
- **Better error messages** — line numbers, better diagnostics, stack traces
- **Visitor pattern refactor** — formalize dispatch with visitor pattern; enables multiple passes (interpreter, compiler, type checker) over the same AST
- **Bytecode compiler + VM** — natural next step; compile AST to bytecode, interpret bytecode in a virtual machine (faster than tree walking)
- **Standard library** — built-in functions for I/O, math, string manipulation

---

## Notes
- `=` alone is not currently a token (assignment uses `know`, no `=` needed)
- Interpreter currently uses `isinstance` chaining — acceptable for this scale, refactor to visitor pattern before adding a bytecode backend
- This is intentionally a learning project; scope is kept tight to understand fundamentals before adding complexity
- **Unary minus is not supported** — `-5` or `know x -5` will fail because `-` is only defined as a binary operator between two terms. To fix, add a `unary` rule between `factor` and `primary` that checks for a leading `-` and wraps the following primary in a `UnaryOpNode`. Not in current scope but worth knowing before hitting it at runtime.

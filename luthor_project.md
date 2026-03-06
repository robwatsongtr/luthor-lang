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
- Keywords: `KNOW` (assignment), `SUPPOSE` (if), `OTHERWISE` (else), `END` (block delimiter)
- `EOF`
- 'DOOM' for print 

### Lexer (`lexer.py`)
- Handles whitespace, single-char tokens via `single_char_map`
- Multi-character comparison tokens via `peek`/`peek_next` state transition
- Keywords via `keyword_map`, falls back to `IDENTIFIER`
- Numeric literals
- Raises `ValueError` on unexpected characters

### Parser (`parser.py`)
- Recursive descent
- Currently implements: `expression → term → factor → primary`
- `primary` handles `NUMBER` and parenthesized expressions
- `consume` does validation and advances in one step

### Nodes (`nodes.py`)
- `BinaryOpNode(op, left, right)`
- `NumberNode(number)`

### Interpreter (`interpreter.py`)
- Tree walker using `isinstance` checks
- `op_map` maps `TokenType` to Python `operator` functions
- Handles `BinaryOpNode` and `NumberNode`

---

## Current EBNF

```
program              → statement*
statement            → assignment | conditional | print_statement | expression_statement
assignment           → 'know' IDENTIFIER expression
conditional          → 'suppose' expression block ('otherwise' block)?
print_statement      → 'doom' expression
block                → statement* 'end'
expression_statement → expression
expression           → comparison
comparison           → term (('==' | '!=' | '<' | '>' | '<=' | '>=') term)*
term                 → factor (('+' | '-') factor)*
factor               → primary (('*' | '/') primary)*
primary              → NUMBER | IDENTIFIER | '(' expression ')'
```

---

## Current Scope

Arithmetic operations, variable assignment, conditional branching, and print. In rough implementation order:

1. **Extend `primary`** to handle `IDENTIFIER` tokens → needs `IdentifierNode`
2. **Add `comparison` method** to parser, update `expression` to call it
3. **Add `AssignNode`**, implement `assignment` parser method
4. **Add `BlockNode`**, implement `block` parser method
5. **Add `ConditionalNode`**, implement `conditional` parser method
6. **Add `PrintNode`**, add `DOOM` keyword/token, implement `print_statement`
7. **Add `statement` and `program` methods** to parser
8. **Add symbol table** (plain dict) to interpreter for variable state
9. **Extend interpreter** with isinstance branches for all new node types

### Key design note — symbol table
The symbol table is a plain Python dictionary (`{'x': 5}` etc.) that lives on the interpreter. All nodes that read or write variables (`IdentifierNode`, `AssignNode`) reference this shared dict.

---

## Future Additions

- **Looping** — while-style loop (`crime` keyword) is the next planned feature after current scope is complete. Fits naturally into the grammar as `while_statement → 'crime' expression block`. The symbol table makes this meaningful — the loop re-evaluates its condition and re-walks its body nodes each iteration, relying on assignments inside the loop mutating shared state.
- **Visitor pattern refactor** — worth doing before a bytecode compiler; each node gets `accept(visitor)`, interpreter becomes a visitor class with `visit_*` methods; enables multiple passes (interpreter, compiler, type checker) over the same node types without duplicating dispatch logic
- **Bytecode compiler** — natural next step after the tree walker is solid; understanding what the walker does at runtime makes the leap to a VM much easier
- **For/repeat loop** — fixed iteration count, simple extension once while is done

---

## Notes
- `=` alone is not currently a token (assignment uses `know`, no `=` needed)
- Interpreter currently uses `isinstance` chaining — acceptable for this scale, refactor to visitor pattern before adding a bytecode backend
- This is intentionally a learning project; scope is kept tight to understand fundamentals before adding complexity
- **Unary minus is not supported** — `-5` or `know x -5` will fail because `-` is only defined as a binary operator between two terms. To fix, add a `unary` rule between `factor` and `primary` that checks for a leading `-` and wraps the following primary in a `UnaryOpNode`. Not in current scope but worth knowing before hitting it at runtime.

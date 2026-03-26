# Luthor Language

A simple, Turing-complete interpreted programming language with Lex Luthor-themed keywords. Built in Python as a learning project to understand lexing, parsing, AST construction, and interpretation.

> *The name is a pun on "lexer"*

## Features

- **Variables** — `know x 10`
- **Arithmetic** — `+`, `-`, `*`, `/` with proper precedence
- **Comparisons** — `<`, `>`, `<=`, `>=`, `==`, `!=`
- **Conditionals** — `suppose`/`otherwise`/`end`
- **Loops** — `crime` (while loops)
- **Output** — `doom` (print)

## Quick Start

```python
python3 main.py
```

## Example Programs

### Hello World (sort of)
```
doom 42
```
Output: `> 42.0`

### Variables and Arithmetic
```
know x 10
know y 5
doom x + y * 2
```
Output: `> 20.0`

### Conditionals
```
know age 25
suppose age >= 18
    doom 1
end
otherwise
    doom 0
end
```
Output: `> 1.0`

### Loops
```
know counter 0
crime counter < 5
    doom counter
    know counter counter + 1
end
```
Output: `> 0.0` `> 1.0` `> 2.0` `> 3.0` `> 4.0`

## Language Reference

### Keywords
- `know` — variable assignment
- `suppose` — if statement
- `otherwise` — else clause
- `crime` — while loop
- `doom` — print statement
- `end` — block terminator

### Operators
- Arithmetic: `+`, `-`, `*`, `/`
- Comparison: `<`, `>`, `<=`, `>=`, `==`, `!=`
- Grouping: `(`, `)`

### Syntax Rules
- Blocks must end with `end`
- Expressions use standard precedence (multiplication before addition, etc.)
- Variables are dynamically typed (currently only numbers)
- Whitespace is mostly ignored (except newlines vs spaces)

## Architecture

**Pipeline:** `source → Lexer → tokens → Parser → AST → Interpreter → output`

- **Lexer** (`src/lexer.py`) — tokenizes source text
- **Parser** (`src/parser.py`) — recursive descent parser, builds AST
- **Interpreter** (`src/interpreter.py`) — tree-walking interpreter with symbol table
- **Nodes** (`src/nodes.py`) — AST node definitions
- **Tokens** (`src/tokens.py`) — token types and definitions


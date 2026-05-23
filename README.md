# Luthor Language

An interpreted programming language with Lex Luthor-themed keywords. 

Features a a lexer, recursive descent parser, symbol table and interpreter that runs as a visitor dispatch.
...all in a bit over 1k lines of C++.

Compact, readable, not over-engineered. 

> *The name is a pun on "lexer"*

## Features

- **Variables** — `know x 10`
- **Arithmetic** — `+`, `-`, `*`, `/` with proper precedence
- **Unary negation** — `-x`, `-5`, `-(expr)`
- **Comparisons** — `<`, `>`, `<=`, `>=`, `==`, `!=`
- **Conditionals** — `suppose`/`otherwise`/`end`
- **Loops** — `crime` (while loops)
- **Output** — `doom` (print)

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

### Unary Negation
```
know x 5
doom -x
doom -(x + 3)
```
Output: `> -5.0` `> -8.0`

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

### Fibonacci Sequence
```
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
```
Output: `> 0` `> 1` `> 1` `> 2` `> 3` `> 5` `> 8` `> 13` `> 21` `> 34`

## Building and Running

**Build** (requires `make` and `clang++`):
```
cd cpp
make
```

**Run**:
```
./luthor source.lut
```

Source files use the `.lut` extension by convention — the interpreter doesn't enforce it.

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
- Unary: `-` (negation)
- Comparison: `<`, `>`, `<=`, `>=`, `==`, `!=`
- Grouping: `(`, `)`

### Syntax Rules
- Blocks must end with `end`
- Expressions use standard precedence (multiplication before addition, etc.)
- Variables are dynamically typed (currently only numbers)
- Whitespace is mostly ignored (except newlines vs spaces)


Essentially all hand-coded: LLM's used for guidance and teaching,
a tedious switch statement, and moving the accept methods out of the nodes. 

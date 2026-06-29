# Compiler

A simple custom compiler/interpreter written in **C**, with a modular structure (lexer, parser, interpreter, symbol table, and function table).

## 📁 Project Structure

```text
.
├── Makefile
├── compiler
├── include
│   ├── console.h
│   ├── functionTable.h
│   ├── interpreter.h
│   ├── lexer.h
│   ├── parser.h
│   ├── symboltable.h
│   └── token.h
└── src
    ├── console.c
    ├── functionTable.c
    ├── interpreter.c
    ├── lexer.c
    ├── main.c
    ├── parser.c
    ├── symboltable.c
    └── token.c
```

## ⚙️ Build

### Requirements
- `gcc`
- `make`

### Compile

```bash
make
```

This creates the executable file **`compiler`**.

## ▶️ Run

```bash
./compiler
```

> If your program expects input files or command-line arguments, add a concrete example here.

## 🧩 Components

- **lexer.c / lexer.h**  
  Converts source code into tokens.

- **parser.c / parser.h**  
  Performs syntax analysis on the token stream.

- **token.c / token.h**  
  Defines token types and token handling.

- **interpreter.c / interpreter.h**  
  Executes parsed structures/statements.

- **symboltable.c / symboltable.h**  
  Manages variables/symbols.

- **functionTable.c / functionTable.h**  
  Manages function definitions and lookup.

- **console.c / console.h**  
  Console output and utility helpers.

- **main.c**  
  Entry point and pipeline orchestration.

## 🧹 Clean

```bash
make clean
```

Removes the generated `compiler` binary.

## 🚀 Suggested Next Improvements

- Add compiler warning flags (`-Wall -Wextra -Wpedantic`)
- Add a debug build target (`-g`)
- Add a test directory + automated tests (`make test`)
- Add example source files + concrete usage examples
- Add a license (e.g. MIT)

## 📄 License

No license has been added yet.

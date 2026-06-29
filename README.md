# Compiler

Ein einfacher, eigener Compiler/Interpreter in **C** mit modularem Aufbau (Lexer, Parser, Interpreter, Symboltabelle, Funktionsverwaltung).

## 📁 Projektstruktur

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

### Voraussetzungen
- `gcc`
- `make`

### Kompilieren

```bash
make
```

Dadurch wird die ausführbare Datei **`compiler`** erzeugt.

## ▶️ Ausführen

```bash
./compiler
```

> Falls dein Programm Eingabedateien oder Argumente erwartet, ergänze hier ein konkretes Beispiel.

## 🧩 Komponenten

- **lexer.c / lexer.h**  
  Zerlegt den Quelltext in Tokens.

- **parser.c / parser.h**  
  Analysiert die Token-Sequenz syntaktisch.

- **token.c / token.h**  
  Definition und Handling von Token-Typen.

- **interpreter.c / interpreter.h**  
  Führt geparste Strukturen/Anweisungen aus.

- **symboltable.c / symboltable.h**  
  Verwaltung von Variablen/Symbolen.

- **functionTable.c / functionTable.h**  
  Verwaltung von Funktionen.

- **console.c / console.h**  
  Konsolen-Ausgabe/Utility-Funktionen.

- **main.c**  
  Programmeinstieg und Orchestrierung der Pipeline.

## 🧹 Clean

```bash
make clean
```

Entfernt die erzeugte Binärdatei `compiler`.

## 🚀 Nächste sinnvolle Verbesserungen

- Compiler-Warnflags ergänzen (`-Wall -Wextra -Wpedantic`)
- Debug-Build-Target hinzufügen (`-g`)
- Test-Ordner + automatische Tests (`make test`)
- Kurze Beispieldateien + Usage-Section mit konkreten Inputs/Outputs
- Lizenzdatei hinzufügen (z. B. MIT)

## 📄 Lizenz

Aktuell ist keine Lizenz hinterlegt.

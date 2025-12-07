# C Lexical Analyzer

A simple **lexical analyzer** in C that reads a `.c` source file and identifies different tokens such as keywords, identifiers, operators, symbols, special characters, numbers (decimal, hexadecimal, binary, octal), string literals, and character constants.  

It also detects arrays, complex operators (`==`, `!=`, `&&`, `||`, `<<`, `>>`), and prints errors for invalid literals or escape sequences. This project is designed for educational purposes to understand how lexical analysis works in C programming.

## Features

- Detects C keywords, identifiers, operators, symbols, and special characters.
- Recognizes decimal, hexadecimal, octal, and binary numbers.
- Supports string literals and character constants.
- Handles arrays and complex operators.
- Prints informative errors for invalid tokens or escape sequences.

## Usage

1. Compile the project:
   ```bash
   gcc *.c
   
2. to run
   ```bash
   ./a.out sample.c

## Output
```bash
sample.c file opened successfully
int        :is a keyword
test       :is an identifier
(          :is a special character
)          :is a special character
{          :is a symbol
int        :is a keyword
a          :is an identifier
,          :is a special character
b          :is an identifier
;          :is a special character
int        :is a keyword
c          :is an identifier
=          :is an assignment operator
a          :is an identifier
+          :is an operator
b          :is an identifier
;          :is a special character
return     :is a keyword
c          :is an identifier
;          :is a special character
}          :is a symbol


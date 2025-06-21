StAb - A General Purpose, Imperative, Static Typed Programming Language.

This repository hosts the compiler for the StAb programming language.

# Building StAb

## Prerequisite
- LLVM >= 21
- Clang >= 17
- make

## Build using make
The `Compiler` directory contains a Makefile, from this directory run:
```bash
make
```
On successfull build, an executable named `stab` is generated in the same directory which is the compiler.

# Compiling StAb Program

To compile your program `test.st` run:
```bash
stab test.st
```
To also see the generated LLVM IR use the `-emit-llvm-ir` flag.

```bash
stab -emit-llvm-ir test.st
```
By default the executable is named `a.out` and `a.ll` for emitted LLVM IR. It can be overridden by `-o` flag as:
```bash
stab -emit-llmv-ir test.st -o test
```
This generates two files `test.ll` and `test`.

# Hello World

```
 fn main() {
    println("Hello, World")
 }
```

# Basic Syntax

## Variable Declaration
 - Only supports `int` type as of now.
```
 int x;
```

## While Loop

```
fn main() {
  int x = 5;
  while x {
    x = x - 1;
  }
}
```

## loop : Infinite looping construct 

```
fn main() { 
 // infinite loop
 loop {
    println("Hello,World");
  }
}
```
## For Loop
- The following snippets prints numbers from 0 to 500
```
 for i in 0 to 500 {
  println("{}", i);
 }
```
## If Statement
```
int x = 5;

if x < 50 {
  x = x + 50;
}
```

## User Defined Function

```
fn factorial(int n) -> int {
  
}
```

## Reading input from the console

```
//Use the inbuilt input function
int x;
// Read the value into x
input(x);
```
For more see the [examples](https://github.com/Abhilekhgautam/StAb/tree/main/examples) .

# Current Implementation Status 

 - `int`as a type.
 - Support for `for`, `while` and `loop` construct.
 - Support for Array.
 - Supports printing to standard output using `println` and `print`
 - Supports reading input from the console using `input`.
 - Support for `if else` statement


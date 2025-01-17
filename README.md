StAb - A General Purpose, Imperative, Static Typed Programming Language.

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
fn main() -> void{
  int x = 5;
  while x {
    x = x - 1;
  }
}
```

## loop : Infinite looping construct 

```
fn main() -> void{ 
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

# Current Implementation Status 

 - `int`as a type.
 - Support for `for`, `while` and `loop` construct.
 - Support for Array.
 - Supports printing to standard output using `println`
 - Supports reading input from the console using `input`
 - Support for `if else` statement


StAb - A General Purpose, Imperative, Static Typed Programming Language.

# Hello World

```
 fn main() -> void {
    // println adds a new line automatically
    println("Hello, World")
 }
```

# Basic Syntax

## Variable Declaration
 - Only supports `int`and `void` type as of now.
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
  println("%d", i);
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

# Current Implementation Status 

 - Function can take args now.
 - No concept of Scope ( will be implemented next)
 - `int` , `string` and `void` as a type.
 - Support `for` loop added
 - No class or struct (struct will be implementd)
 - No Array (will be implemented)
 - Has very poor error message
 - Doesn't generate Native Code, only generates LLVM IR as of now 
 - Supports printint to standard output using println
 - Checks for the existence of the main function
 - support for `if else` statement

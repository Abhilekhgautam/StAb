StAb - A General Purpose, Imperative, Static Typed Programming Language.

# Probable Hello World

```
 fn main() -> void {
    // println adds a new line automatically
    println("Hello, World")
 }
```

# Basic Syntax

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

## Variable Declaration
 - Only supports `int`and `void` type as of now.
```
 int x;
```

## User Defined Function

```
fn factorial(int n) -> int {
  
}
```

# Current Implementation Status 

 - Function can take args now.
 - No concept of Scope ( will be implemented next)
 - Only `int` and `void` as a type.
 - No `for` loop yet, (will be implemented)
 - No class or struct (struct will be implementd)
 - No Array (will be implemented)
 - Has very poor error message
 - Doesn't generate Native Code, only generates LLVM IR as of now 
 - No Support for println yet.
 - Checks for the existence of the main function

STAB - A General Purpose, Imperative, Static Typed Programming Language.

# Probable Hello World

```
 fn main(){
    // println adds a new line automatically
    println("Hello, World")
 }
```

# Basic Syntax

## While Loop

```
fn main(){
  int x = 5;
  while x {
    x = x - 1;
  }
}
```

## loop : Infinite looping construct 

```
fn main(){ 
 // infinite loop
 loop {
    println("Hello,World");
  }
}
```

## Variable Declaration
 - Only supports `int` type as of now.
```
 int x;
```

## User Defined Function

```
fn factorial(int n) -> int {
  
}
```

# Current Implementation Status 

 - Function cannot take args 
 - No concept of Scope ( will be implemented next)
 - Variable Referencing don't check if the var exists (needs scope)
 - Only `int` as a type 
 - No `for` loop yet, (will be implemented)
 - No class or struct (struct will be implementd)
 - No Array (will be implemented)
 - Has very poor error message
 - Don't generate Native Code, only generates LLVM IR as of now 
 - No Support for println yet.

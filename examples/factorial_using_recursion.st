fn factorial(int n) -> int {
  if n == 0 {
    return 1;
  }
  else {  
    return (n * factorial(n - 1));
  }
}

fn main() -> void {
  int result = factorial(0);

  println("The factorial of 5 is %d", result);
}

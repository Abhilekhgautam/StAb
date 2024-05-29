fn factorial(int n) -> int {
  println("I am Called");
  if n == 0 {
    return 1;
  }
  else{
    return n * factorial(n - 1);
  }
}

fn main() -> void {
  int result = factorial(5);

  println("The factorial of 5 is %d", result);
}

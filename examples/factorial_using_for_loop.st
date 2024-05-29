fn factorial(int n) -> int {
  int result = 1;

  for i in 2 to n {
     result = result * i;
  }

  return result;
}

fn main() -> void {
   int fact = factorial(5);

   println("The factorial of 5 is %d", fact);
}

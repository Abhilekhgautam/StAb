fn factorial(int n) -> int {
  int result = 1;

  for i in 2 to n {
    result = result * i;
  }

  return result;
}

fn main () -> void {
    int x;
    println("Enter the number:");
    // Read input from the console
    input(x)
    
    println("The factorial of {} is {} ", x, factorial(x));

}

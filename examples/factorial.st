fn factorial(int n)->int{
   int result = 1;
   int count = 1;
    
   while count <= n {
      println("%d",n);
      result = result * count;
      count = count + 1;
   }

   return result;
}

fn main() -> void{
    int result = factorial(0);
    println("The factorial of 0 is %d", result);
}


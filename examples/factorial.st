int x = 5;
int y = 6;

fn factorial(int n)->int{
   int result = 1;
   int count = 1;
    
   while count <= n {
      result = result * count;
      count = count + 1;
   }

   return result;
}

fn main() -> int{
    int z = factorial(5);
    return z;
}


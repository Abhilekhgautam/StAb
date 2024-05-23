fn factorial(int n)->int{
   int result = 1;
   int count = 1;
    
   while count <= n {
      result = result * count;
      count = count + 1;
   }

   return result;
}

fn test() -> void {
   int y = factoria(5);
}

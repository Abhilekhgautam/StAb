fn add(int x, int y) -> int{
   return x + y;
}

fn main() -> void {
   int a = 5;
   int b = 6;
   int c = add(a, b);

   println("{} + {} =  {}", a, b, c);
}

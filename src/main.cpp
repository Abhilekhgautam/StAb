#include <cstring>
#include <iostream>
#include "./lexer/lexer.hpp"
#include "./parser/parser.hpp"


int main(int argc, char* argv[]){
  const bool debug = argc > 1 && std::strcmp(argv[1], "--debug") == 0;

  STAB::Lexer lexer(std::cin, debug);
  STAB::Parser parser(lexer, debug);

  return parser();
}

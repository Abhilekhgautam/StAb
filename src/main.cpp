#include <cstring>
#include <iostream>
#include "./lexer/lexer.hpp"
#include <map>
#include <string>
#include <memory>

#include <llvm/IR/Value.h>
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"

#include <llvm/IR/Instructions.h>
#include "globals.h"

std::unique_ptr<llvm::LLVMContext> TheContext;
std::unique_ptr<llvm::IRBuilder<>> Builder;
std::map<std::string, llvm::Type*> NamedLLVMType;
std::unique_ptr<llvm::Module> TheModule;
llvm::Function* mainFunction;
std::map<std::string, llvm::AllocaInst *> NamedValues;

int main(int argc, char* argv[]){
  const bool debug = argc > 1 && std::strcmp(argv[1], "--debug") == 0;

  initializeModule();
  STAB::Lexer lexer(std::cin, debug);
  STAB::Parser parser(lexer, debug);

  // print the generated code..
  TheModule->print(llvm::errs(), nullptr);

  return parser();
}

#include <cstring>
#include <iostream>
#include "./lexer/lexer.hpp"
#include "includes/scope.h"
#include <map>
#include <string>
#include <memory>
#include <fstream>
#include <filesystem>

#include <llvm/IR/Value.h>
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"

#include <llvm/IR/Instructions.h>
#include <vector>
#ifndef STAB_GLOBAL_H
#include "globals.h"
#endif
#ifndef STAB_SCOPE_H
#include "./includes/scope.h"
#endif

std::unique_ptr<llvm::LLVMContext> TheContext;
std::unique_ptr<llvm::IRBuilder<>> Builder;
std::map<std::string, llvm::Type*> NamedLLVMType;
std::unique_ptr<llvm::Module> TheModule;
llvm::Function* mainFunction;
std::map<std::string, llvm::AllocaInst *> NamedValues;
std::vector<STAB::Scope*> scopes;

STAB::Scope* globalScope = nullptr;
STAB::Scope* currentScope = globalScope;

namespace fs = std::filesystem;

int main(int argc, char* argv[]){
  const bool debug = argc > 1 && std::strcmp(argv[1], "--debug") == 0;

  if (argc != 2){
     std::cerr << "Invalid Command Usage\n";
     std::cerr << "Usage: " << argv[0] << " <file name>\n";
     return -1;
  }

  if (!fs::exists(argv[1])){
     std::cerr << "No such file: " << argv[1] << " exists\n";
     return -1;
  }

  std::fstream source_file(argv[1]);

  initializeModule();
  STAB::Lexer lexer(source_file, debug);
  STAB::Parser parser(lexer, debug);

  // print the generated code..
  // TheModule->print(llvm::errs(), nullptr);

  parser();

}

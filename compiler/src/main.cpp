#include <cstring>
#include <iostream>
#include "./lexer/lexer.hpp"
#include "includes/scope.hpp"
#include <llvm-18/llvm/ADT/ArrayRef.h>
#include <llvm-18/llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm-18/llvm/Support/CodeGen.h>
#include <llvm-18/llvm/Target/TargetOptions.h>

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
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"
#include <vector>
#ifndef STAB_GLOBAL_H
#include "globals.h"
#endif
#ifndef STAB_SCOPE_HPP
#include "./includes/scope.h"
#endif

#ifndef HIGHLIGHT_TERM_
#include "includes/highlight-term.hpp"
#endif

std::unique_ptr<llvm::LLVMContext> TheContext;
std::unique_ptr<llvm::IRBuilder<>> Builder;
std::map<std::string, llvm::Type*> NamedLLVMType;
std::unique_ptr<llvm::Module> TheModule;
std::map<std::string, llvm::AllocaInst *> NamedValues;
std::vector<STAB::Scope*> scopes;

std::vector<llvm::Function*> fnBlocks;
STAB::FunctionAST* __start__fn;
STAB::Scope* globalScope = new STAB::Scope(nullptr);
STAB::Scope* currentScope = globalScope;
namespace fs = std::filesystem;

int main(int argc, char* argv[]){
  const bool debug = argc > 1 && std::strcmp(argv[1], "--debug") == 0;

  if (argc != 2){
     color("red","Invalid Command Usage", true);
     color("green","Usage: ");
     color("blue", std::string(argv[0]) +" <file name>", true);
     return -1;
  }

  if (!fs::exists(argv[1])){
     color("red", "Error: ");
     color("blue", "No such file: ");
     color("blue",std::string(argv[1])+ " exists", true);
     return -1;
  }

  std::fstream source_file(argv[1]);

  initializeModule();
  STAB::Lexer lexer(source_file, debug);
  lexer.initSourceLine();
  STAB::Parser parser(lexer, debug);

  parser();

  init_builtins();

  if(__start__fn){
       __start__fn->codegen(nullptr);

      // Get the main function 
      auto main = TheModule->getFunction("main");

      if (!main){
          color("red","Error: ");
	  color("blue","No main function defined.\nStAb requires at least a \"main\" function for execution",true);     
	  return -1;
      }
      LLVMInitializeAllTargetInfos();
      LLVMInitializeAllTargets();
      LLVMInitializeAllTargetMCs();
      LLVMInitializeAllAsmParsers();
      LLVMInitializeAllAsmPrinters();
      auto TargetTriple = LLVMGetDefaultTargetTriple();
      std::string Error;
      auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);

      if(!Target){
	 llvm::errs() << Error;
	 return 1;
      }

      auto CPU = "generic";
      auto Features = "";
      llvm::TargetOptions opt;

      auto TargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, llvm::Reloc::PIC_);

      TheModule->setDataLayout(TargetMachine->createDataLayout());
      TheModule->setTargetTriple(TargetTriple);

      auto Filename = "output.o";
      std::error_code EC;
      llvm::raw_fd_ostream dest(Filename, EC, llvm::sys::fs::OF_None);

      if (EC) {
	 llvm::errs() << "Could not open file: " << EC.message();
         return 1;
       }

       llvm::legacy::PassManager pass;
       auto FileType = llvm::CodeGenFileType::ObjectFile;

       if (TargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)){
	       llvm:: errs() << "TargetMachine can't emit a file of this type";
	  return 1;
       }
       pass.run(*TheModule);
       dest.flush();
       const char* command = "clang output.o -o output";

       std::system(command);
  }
}

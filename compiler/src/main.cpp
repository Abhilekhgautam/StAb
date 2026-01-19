/*

TODO: Yuck.. I always believe main function should
act as an entry point and I hope to refactor this
soon

*/

#include "./lexer/lexer.hpp"
#include "includes/scope.hpp"
#include <cstring>
#include <llvm/ADT/ArrayRef.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/IR/PassManager.h>
#include <llvm/Passes/OptimizationLevel.h>
#include <llvm/Support/CodeGen.h>
#include <llvm/Target/TargetOptions.h>
#include <format>
#include <filesystem>
#include <fstream>
#include <map>
#include <memory>
#include <string>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/TargetParser/Triple.h"
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>
#include <llvm/Passes/PassBuilder.h>
#include <vector>
#include <cstdlib>

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
std::map<std::string, llvm::Type *> NamedLLVMType;
std::unique_ptr<llvm::Module> TheModule;
std::map<std::string, llvm::AllocaInst *> NamedValues;
std::vector<STAB::Scope *> scopes;

std::vector<llvm::Function *> fnBlocks;
STAB::FunctionAST *__start__fn;
STAB::Scope *globalScope = new STAB::Scope(nullptr);
STAB::Scope *currentScope = globalScope;
namespace fs = std::filesystem;

const std::string LIB_PATH = std::getenv("STAB_IO_LIB");

void displayHelp(){
   std::cout << "Missing Source filename." << '\n';
   std::cout << "Usage: stab [options] <filename>" << '\n';
   std::cout << "Options:\n";
   std::cout << "-emit-llvm-ir: view the generated llvm IR code\n";
   std::cout << "-o <output_file_name>: provide the output file name\n";
}

int main(int argc, char *argv[]) {
  const bool debug = argc > 1 && std::strcmp(argv[1], "--debug") == 0;

  bool shouldEmitIR = false;
  // Default output filename
  std::string outputFileName = "a.out";
  std::string sourceFileName;

  if (argc <= 1) {
    displayHelp();
    return 0;
  }
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-emit-llvm-ir")
      shouldEmitIR = true;
    else if (arg == "-o") {
      if (i + 1 > argc) {
        color("red", "Missing output filename after -o", true);
        displayHelp();
        return 0;
      } else {
        outputFileName = argv[++i];
      }
    } else if (sourceFileName.empty()) {
      sourceFileName = arg;
    } else {
      color("red", "Invalid argument", false);
      color("blue", arg, true);
      displayHelp();
      return 0;
    }
  }

  if (!fs::exists(sourceFileName)) {
    color("red", "Error: ");
    color("blue", "No such file: ");
    color("blue", sourceFileName + " exists", true);
    return -1;
  }

  std::fstream source_file(sourceFileName);

  initializeModule();
  STAB::Lexer lexer(source_file, debug);
  lexer.initSourceLine();
  STAB::Parser parser(lexer, debug);

  parser();

  init_builtins();

  if (__start__fn) {
    __start__fn->codegen(nullptr);

    // Get the main function
    auto main = TheModule->getFunction("main");

    if (!main) {
      color("red", "Error: ");
      color("blue",
            "No main function defined.\nStAb requires at least a \"main\" "
            "function for execution",
            true);
      return -1;
    }
    std::filesystem::path p(outputFileName);


    LLVMInitializeAllTargetInfos();
    LLVMInitializeAllTargets();
    LLVMInitializeAllTargetMCs();
    LLVMInitializeAllAsmParsers();
    LLVMInitializeAllAsmPrinters();

    auto TargetTriple = LLVMGetDefaultTargetTriple();
    std::string Error;

    auto triple = llvm::Triple(TargetTriple);

    auto Target = llvm::TargetRegistry::lookupTarget(triple, Error);

    if (!Target) {
      llvm::errs() << "IDK" << Error;
      return 1;
    }

    auto CPU = "generic";
    auto Features = "";
    llvm::TargetOptions opt;
    
    
    auto TargetMachine = Target->createTargetMachine(
        triple, CPU, Features, opt, llvm::Reloc::PIC_);

    TheModule->setDataLayout(TargetMachine->createDataLayout());
    TheModule->setTargetTriple(llvm::Triple(TargetTriple));

    auto Filename = p.stem().string() + ".o";
    std::error_code EC;
    llvm::raw_fd_ostream dest(Filename, EC, llvm::sys::fs::OF_None);

    if (EC) {
      llvm::errs() << "Could not open file: " << EC.message();
      return 1;
    }

    llvm::LoopAnalysisManager LAM;
    llvm::FunctionAnalysisManager FAM;
    llvm::CGSCCAnalysisManager CGAM;
    llvm::ModuleAnalysisManager MAM;

     // Create the new pass manager builder.
     // Take a look at the PassBuilder constructor parameters for more
    // customization, e.g. specifying a TargetMachine or various debugging
    // options.
    llvm::PassBuilder PB;

    // Register all the basic analyses with the managers.
    PB.registerModuleAnalyses(MAM);
    PB.registerCGSCCAnalyses(CGAM);
    PB.registerFunctionAnalyses(FAM);
    PB.registerLoopAnalyses(LAM);
    PB.crossRegisterProxies(LAM, FAM, CGAM, MAM);

   // Create the pass manager.
   // This one corresponds to a typical -O2 optimization pipeline.
    llvm::ModulePassManager MPM = PB.buildPerModuleDefaultPipeline(llvm::OptimizationLevel::O2);
   // Optimize the IR!
   MPM.run(*TheModule, MAM);
   if (shouldEmitIR) {
      std::error_code EC;
      std::string llPath = p.stem().string();
      // Write IR to .ll file
      llvm::raw_fd_ostream dest(llPath + ".ll", EC, llvm::sys::fs::OF_None);
      TheModule->print(dest, nullptr);
      return 0;
    }

    llvm::legacy::PassManager pass;
    auto FileType = llvm::CodeGenFileType::ObjectFile;

    if (TargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
      llvm::errs() << "TargetMachine can't emit a file of this type";
      return 1;
    }

    pass.run(*TheModule);
    dest.flush();
    std::string command = std::format("clang {} {} -o {}", LIB_PATH, Filename, outputFileName);

    int val = std::system(command.c_str());
    std::filesystem::remove(Filename);
  }
}

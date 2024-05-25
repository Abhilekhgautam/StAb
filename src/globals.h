#pragma once

#ifndef STAB_GLOBAL_H
#define STAB_GLOBAL_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <memory>

#include <llvm/IR/Value.h>
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Function.h>

#include "./includes/scope.hpp"
#include "./simple-ast/ast.h"

namespace STAB{
    class Scope;
    class FunctionAST;
}

extern std::unique_ptr<llvm::LLVMContext> TheContext;
extern std::unique_ptr<llvm::IRBuilder<>> Builder;
extern std::unique_ptr<llvm::Module> TheModule;
extern std::map<std::string, llvm::Type*> NamedLLVMType;
extern std::map<std::string, llvm::AllocaInst *> NamedValues;
extern STAB::Scope* globalScope;
extern STAB::Scope* currentScope;
extern STAB::FunctionAST* __start__fn;
extern std::vector<llvm::Function*> fnBlocks;
/*
void addNewScope(Scope* s){
   scopes.emplace_back(s);	
}
*/
inline void initializeModule(){
    // Open a new context and module.
    TheContext = std::make_unique<llvm::LLVMContext>();
    TheModule = std::make_unique<llvm::Module>("STAB", *TheContext);

     // Create a new builder for the module.
     Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);
     std::vector<llvm::Type* > argTypes;
}

#endif 

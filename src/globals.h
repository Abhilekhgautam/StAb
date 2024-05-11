#pragma once

#include <llvm-18/llvm/IR/GlobalValue.h>
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

extern std::unique_ptr<llvm::LLVMContext> TheContext;
extern std::unique_ptr<llvm::IRBuilder<>> Builder;
extern std::unique_ptr<llvm::Module> TheModule;
extern std::map<std::string, llvm::Type*> NamedLLVMType;
extern std::map<std::string, llvm::AllocaInst *> NamedValues;
extern llvm::Function* mainFunction;

inline void initializeModule(){
    // Open a new context and module.
    TheContext = std::make_unique<llvm::LLVMContext>();
    TheModule = std::make_unique<llvm::Module>("STAB", *TheContext);

     // Create a new builder for the module.
     Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);
     std::vector<llvm::Type* > argTypes;
     llvm::FunctionType *ftype = llvm::FunctionType::get(llvm::Type::getVoidTy(*TheContext), argTypes, false);
     mainFunction = llvm::Function::Create(ftype,llvm::GlobalValue::InternalLinkage, "main", *TheModule);
}
/// CreateEntryBlockAlloca - Create an alloca instruction in the entry block of
/// the function.  This is used for mutable variables etc.
static llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction,
                                          const std::string &VarName) {
	llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
                 TheFunction->getEntryBlock().begin());
  return TmpB.CreateAlloca(llvm::Type::getDoubleTy(*TheContext), nullptr,
                           VarName);
}
#endif 

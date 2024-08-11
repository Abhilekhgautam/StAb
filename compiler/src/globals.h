#pragma once

#ifndef STAB_GLOBAL_H
#define STAB_GLOBAL_H

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../src/lib/lib.h"
#include "./includes/scope.hpp"
#include "./simple-ast/ast.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/DynamicLibrary.h"
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

namespace STAB {
class Scope;
class FunctionAST;
} // namespace STAB

extern std::unique_ptr<llvm::LLVMContext> TheContext;
extern std::unique_ptr<llvm::IRBuilder<>> Builder;
extern std::unique_ptr<llvm::Module> TheModule;
extern std::map<std::string, llvm::Type *> NamedLLVMType;
extern std::map<std::string, llvm::AllocaInst *> NamedValues;
extern STAB::Scope *globalScope;
extern STAB::Scope *currentScope;
extern std::vector<llvm::Function *> fnBlocks;
extern STAB::FunctionAST *__start__fn;
/*
void addNewScope(Scope* s){
   scopes.emplace_back(s);
}
*/
inline void initializeModule() {
  // Open a new context and module.
  TheContext = std::make_unique<llvm::LLVMContext>();
  TheModule = std::make_unique<llvm::Module>("STAB", *TheContext);

  // Create a new builder for the module.
  Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);
  std::vector<llvm::Type *> argTypes;
}

inline void init_builtins() {
  // Declare the printf function
  llvm::FunctionType *printfType = llvm::FunctionType::get(
      llvm::IntegerType::getInt32Ty(*TheContext),
      {llvm::PointerType::get(llvm::Type::getInt8Ty(*TheContext), 0)}, true);
  llvm::Function *printfFunc = llvm::Function::Create(
      printfType, llvm::Function::ExternalLinkage, "printf", TheModule.get());

  // Declare and define the println function
  llvm::FunctionType *printlnType = llvm::FunctionType::get(
      llvm::Type::getVoidTy(*TheContext),
      {llvm::PointerType::get(llvm::Type::getInt8Ty(*TheContext), 0)}, true);
  llvm::Function *printlnFunc = llvm::Function::Create(
      printlnType, llvm::Function::ExternalLinkage, "println", TheModule.get());

  llvm::Function *printFunc = llvm::Function::Create(
      printlnType, llvm::Function::ExternalLinkage, "print", TheModule.get());

  llvm::FunctionType *scanfType = llvm::FunctionType::get(
      llvm::IntegerType::getInt32Ty(*TheContext),
      {llvm::PointerType::get(llvm::Type::getInt8Ty(*TheContext), 0)}, true);
  llvm::Function *scanfFunc = llvm::Function::Create(
      scanfType, llvm::Function::ExternalLinkage, "scanf", TheModule.get());

  llvm::FunctionType *inputType = llvm::FunctionType::get(
      llvm::IntegerType::getInt32Ty(*TheContext),
      {llvm::PointerType::get(llvm::Type::getInt8Ty(*TheContext), 0),
       llvm::PointerType::get(llvm::Type::getInt32Ty(*TheContext), 0)},
      false);
  llvm::Function *inputFunc = llvm::Function::Create(
      inputType, llvm::Function::ExternalLinkage, "input", TheModule.get());

  llvm::BasicBlock *entryBlock =
      llvm::BasicBlock::Create(*TheContext, "entry", printlnFunc);
  Builder->SetInsertPoint(entryBlock);

  // Get the function arguments
  auto args = printlnFunc->arg_begin();
  llvm::Value *strArg = args++;

  // Call printf inside println
  Builder->CreateCall(printfFunc, {strArg});
  Builder->CreateRetVoid();

  llvm::BasicBlock *printEntryBlock =
      llvm::BasicBlock::Create(*TheContext, "entry", printFunc);
  Builder->SetInsertPoint(printEntryBlock);

  // Get the function arguments
  auto printArgs = printFunc->arg_begin();
  llvm::Value *strArgVal = printArgs++;

  // Call printf inside printl
  Builder->CreateCall(printfFunc, {strArgVal});
  Builder->CreateRetVoid();

  llvm::BasicBlock *inputEntryBlock =
      llvm::BasicBlock::Create(*TheContext, "inputentry", inputFunc);
  Builder->SetInsertPoint(inputEntryBlock);

  // Get the function arguments
  auto inputArgs = inputFunc->arg_begin();
  llvm::Value *inputFormatArg = inputArgs++;
  llvm::Value *inputIntPtrArg = inputArgs++;
  // Call scanf inside input
  Builder->CreateCall(scanfFunc, {inputFormatArg, inputIntPtrArg});
  Builder->CreateRet(Builder->getInt32(0));

  // llvm::Type *i8Type = llvm::Type::getInt8Ty(*TheContext);
  // std::vector<llvm::Type*> argTypesInt8Ptr(1, llvm::PointerType::get(i8Type,
  // 0)); llvm::FunctionType* ft =
  // llvm::FunctionType::get(llvm::Type::getVoidTy(*TheContext),
  // argTypesInt8Ptr, true); llvm::Function* f = llvm::Function::Create(ft,
  // llvm::Function::ExternalLinkage,"println", TheModule.get());

  // auto i = f->arg_begin();
  // if (i != f->arg_end())
  //	  i->setName("String");

  printlnFunc->setCallingConv(llvm::CallingConv::C);
  printFunc->setCallingConv(llvm::CallingConv::C);
  inputFunc->setCallingConv(llvm::CallingConv::C);
  fnBlocks.emplace_back(printfFunc);
  fnBlocks.emplace_back(printlnFunc);
  fnBlocks.emplace_back(printFunc);
  fnBlocks.emplace_back(scanfFunc);
  fnBlocks.emplace_back(inputFunc);
}
#endif

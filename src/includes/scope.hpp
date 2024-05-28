#pragma once

#ifndef STAB_SCOPE_HPP
#define STAB_SCOPE_HPP

#include <map>

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include <llvm/IR/Function.h>

namespace STAB{
    class Scope {
       std::map<std::string, llvm::AllocaInst*> SymbolTable;
       std::string name;
       llvm::Function* F;
      public:
        Scope* prev;
       Scope(Scope* e = nullptr, std::string name = ""):name(name), prev(e){}

       void setFnBlock(llvm::Function* Fn);

       void createFnBlock();

       llvm::Function* getFnBlock();
       std::string getName() const;

       // install variable name to the idTable
       void installID(std::string key, llvm::AllocaInst*  value);

       // check if a variable name already exists within the current scope
       llvm::AllocaInst* getID(std::string id) const;

 };
}
#endif

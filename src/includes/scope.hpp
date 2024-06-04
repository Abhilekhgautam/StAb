#pragma once

#include <llvm-18/llvm/IR/SymbolTableListTraits.h>
#include <variant>
#include <optional>
#ifndef STAB_SCOPE_HPP
#define STAB_SCOPE_HPP

#include <map>
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include <llvm/IR/Function.h>

namespace STAB{ 
      using valType = std::variant<llvm::AllocaInst*, llvm::GlobalVariable*>;
    class Scope {
       std::map<std::string, valType> SymbolTable;
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
       void installID(std::string key, valType value);

       // check if a variable name already exists within the current scope
       std::optional<valType> getID(std::string id) const;

 };

}
#endif

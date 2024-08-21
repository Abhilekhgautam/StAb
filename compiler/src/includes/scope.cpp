//
// Created by abhilekh on 5/23/24.
//

#include "scope.hpp"
#include "../globals.h"
#include <llvm-18/llvm/IR/BasicBlock.h>
#include <optional>

namespace STAB {
void STAB::Scope::setFnBlock(llvm::Function *Fn) { F = Fn; }

void STAB::Scope::createFnBlock() {
  F = Builder->GetInsertBlock()->getParent();
}

llvm::Function *STAB::Scope::getFnBlock() { return F; }
std::string STAB::Scope::getType() const { return type; }

// install variable name to the idTable
void STAB::Scope::installID(std::string key, valType value) {
  SymbolTable.insert({key, value});
}

void STAB::Scope::setExitBlock(llvm::BasicBlock* block){
    exitBlock = block;
}

llvm::BasicBlock* STAB::Scope::getExitBlock(){return exitBlock;}
bool STAB::Scope::BreakableOrSkippable(){
    if(getType() == "loop") return true;
    return false;
}

void STAB::Scope::setEntryBlock(llvm::BasicBlock* block){
    entryBlock = block;
}

llvm::BasicBlock* STAB::Scope::getEntryBlock(){
    return entryBlock;
}

bool STAB::Scope::IsBreakableOrSkippable(){
  if(getType() == "loop") return true;
  Scope *tempScope = prev;
  while(tempScope != nullptr){
      if (tempScope->getType() == "loop") return true;
      tempScope = tempScope->prev;
  }
  return false;
}


std::optional<class Scope*> STAB::Scope::getNearestBreakableOrSkippableScope(){
    if(getType() == "loop") return this;
      Scope *tempScope = prev;
      while(tempScope != nullptr){
          if (tempScope->getType() == "loop") return tempScope;
          tempScope = tempScope->prev;
      }
      return std::nullopt;
}

// check if a variable name already exists within the current scope
std::optional<valType> STAB::Scope::getIdCurrentScope(std::string id) const {
  auto found = SymbolTable.find(id);
  if (found != SymbolTable.end()) {
    return found->second;
  }
  return std::nullopt;
}

// check if a variable name already exists within the reachable scope
std::optional<valType> STAB::Scope::getID(std::string id) const {
  Scope *prevScope = this->prev;
  auto found = SymbolTable.find(id);
  if (found != SymbolTable.end()) {
    return found->second;
  }
  if (prevScope) {
    auto symTable = prevScope->SymbolTable;
    while (prevScope) {
      auto found = symTable.find(id);
      if (found != symTable.end()) {
        return found->second;
      }
      prevScope = prevScope->prev;
      if (prevScope)
        symTable = prevScope->SymbolTable;
    }
  }
  return std::nullopt;
}
void Scope::set_break(){
    found_break = true;
}
bool Scope::break_found(){
    return found_break;
}

void Scope::set_skip(){
    found_skip = true;
}

bool Scope::skip_found(){
    return found_skip;
}
} // namespace STAB

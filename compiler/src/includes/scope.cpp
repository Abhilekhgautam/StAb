//
// Created by abhilekh on 5/23/24.
//

#include "scope.hpp"
#include "../globals.h"
#include <optional>

namespace STAB {
void STAB::Scope::setFnBlock(llvm::Function *Fn) { F = Fn; }

void STAB::Scope::createFnBlock() {
  F = Builder->GetInsertBlock()->getParent();
}

llvm::Function *STAB::Scope::getFnBlock() { return F; }
std::string STAB::Scope::getName() const { return name; }

// install variable name to the idTable
void STAB::Scope::installID(std::string key, valType value) {
  SymbolTable.insert({key, value});
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
  Scope *prevScope = prev;
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
} // namespace STAB

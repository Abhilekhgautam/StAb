#pragma once

#ifndef STAB_SCOPE_HPP
#define STAB_SCOPE_HPP

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include <llvm/IR/Function.h>
#include <llvm/IR/SymbolTableListTraits.h>
#include <map>
#include <optional>
#include <variant>

namespace STAB {
using valType = std::variant<llvm::AllocaInst *, llvm::GlobalVariable *>;
class Scope {
  std::map<std::string, valType> SymbolTable;
  // Whether a fn scope, loop scope or conditional scope
  std::string type;
  llvm::BasicBlock* exitBlock = nullptr;
  llvm::BasicBlock* entryBlock = nullptr;
  llvm::Function* F = nullptr;
  bool found_break;
  bool found_skip;
public:
  Scope *prev;
  Scope(Scope *e = nullptr, std::string type = "fn")
  : type(type), found_break(false), prev(e) {}

  void setFnBlock(llvm::Function *Fn);

  void createFnBlock();

  llvm::Function *getFnBlock();
  std::string getType() const;

  void setExitBlock(llvm::BasicBlock*);
  llvm::BasicBlock* getExitBlock();

  void setEntryBlock(llvm::BasicBlock*);
  llvm::BasicBlock* getEntryBlock();
  // install variable name to the idTable
  void installID(std::string key, valType value);

  // check if the current scope is breakable or skippable - doesn't check for its parent.
  bool BreakableOrSkippable();
  // check if the current scope is breakable or skippable
  // or has a breakable or skippable parent
  bool IsBreakableOrSkippable();
  std::optional<Scope*> getNearestBreakableOrSkippableScope();

  // check if a variable name already exists within the reachable scope
  std::optional<valType> getID(std::string id) const;
  std::optional<valType> getIdCurrentScope(std::string id) const;

  bool break_found();
  void set_break();

  bool skip_found();
  void set_skip();
};

} // namespace STAB
#endif

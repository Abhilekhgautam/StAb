//
// Created by abhilekh on 5/23/24.
//

#include "./ast.h"
#include <cstdlib>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/Support/Casting.h>

namespace STAB {
llvm::Value *STAB::VariableExprAST::codegen(Scope *s) {
  // llvm::AllocaInst* var = NamedValues[Name];
  std::optional<valType> var = s->getID(Name);
  // todo: better error handling later
  if (!var.has_value()) {
    color("red", "Error: ");
    color("blue", "No Such variable ");
    std::cout << Name;
    color("blue", " in the current scope", true);
    std::exit(0);
  }
  if (auto val = std::get_if<llvm::AllocaInst *>(&var.value())) {
    return Builder->CreateLoad((*val)->getAllocatedType(), *val, Name.c_str());
  }

  if (auto gVar = (std::get_if<llvm::GlobalVariable *>(&var.value()))) {
    return Builder->CreateLoad((*gVar)->getValueType(), *gVar);
  }
  return nullptr;
}
} // namespace STAB

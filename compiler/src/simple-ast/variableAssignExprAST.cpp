//
// Created by abhilekh on 5/23/24.
//

#include "./ast.h"
#include <cstdlib>

namespace STAB {
llvm::Value *STAB::VariableAssignExprAST::codegen(Scope *s) {
  // todo:  check if the variable exists
  auto varInst = s->getID(Name);
  if (!varInst.has_value()) {
    color("red", "Error: ");
    color("blue", "No such variable " + Name + " in the current scope", true);
    exit(0);
  }
  if (RHS->getType() != "int") {
    color("red", "Error: ");
    color("blue", "Expected value of ");
    std::cout << "int ";
    color("blue", "got ");
    std::cout << RHS->getType() << '\n';
  }
  llvm::Value *val = RHS->codegen(s);
  // llvm::AllocaInst* var = NamedValues[Name];
  if (auto var = std::get_if<llvm::AllocaInst *>(&(varInst.value())))
    return Builder->CreateStore(val, *var);

  std::cout << "Returning nullptr\n";
  return nullptr;
}
} // namespace STAB

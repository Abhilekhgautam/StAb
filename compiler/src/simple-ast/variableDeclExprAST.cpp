//
// Created by abhilekh on 5/23/24.
//

#include "./ast.h"
#include <cstdlib>

namespace STAB {
llvm::Value *STAB::VariableDeclExprAST::codegen(Scope *s) {
  llvm::IntegerType *type = nullptr;
  if (getType() == "string")
    type = llvm::Type::getInt8Ty(*TheContext);
  else
    type = llvm::Type::getInt32Ty(*TheContext);

  if (s == globalScope) {
    std::cerr << "\nGlobal Var " << Name << " initialized\n";
    llvm::Module *module = Builder->GetInsertBlock()->getModule();
    llvm::GlobalVariable *val = new llvm::GlobalVariable(
        *module, type, false, llvm::GlobalValue::ExternalLinkage, nullptr,
        Name);
    valType v = val;
    s->installID(Name, v);
    return val;
  }

  if (getType() == "string")
    type = llvm::Type::getInt8Ty(*TheContext);
  else
    type = llvm::Type::getInt32Ty(*TheContext);

  llvm::AllocaInst *var = Builder->CreateAlloca(type, nullptr, Name);
  valType v = var;
  if (!s->getIdCurrentScope(Name)) {
    s->installID(Name, v);
  } else {
    color("red", "Error:");
    color("blue", "Variable " + Name + " already declared", true);

    std::exit(0);
  }

  return var;
}
} // namespace STAB

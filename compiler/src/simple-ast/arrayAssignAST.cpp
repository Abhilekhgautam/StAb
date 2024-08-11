#include "ast.h"

namespace STAB {
llvm::Value *ArrayAssignAST::codegen(Scope *s) {
  if (index->getType() == "int") {
    if (val->getType() == "int") {
      auto arrayVarOptional = s->getID(name);

      // get llvm::AllocaInst* out of optional
      auto arrayVar =
          std::get_if<llvm::AllocaInst *>(&(arrayVarOptional.value()));

      std::vector<llvm::Value *> indices;
      llvm::Value *zeroIndex =
          llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0));
      indices.emplace_back(zeroIndex);         // Array pointer
      indices.emplace_back(index->codegen(s)); // Index

      llvm::Value *elementPtr = Builder->CreateGEP(
          (*arrayVar)->getAllocatedType(), *arrayVar, indices, "elementPtr");

      // Store the value at the given index.
      return Builder->CreateStore(val->codegen(s), elementPtr);

    } else {
      std::cerr << "\nAssigned Type is not int\n";
      return nullptr;
    }
  } else {
    std::cerr << "\nNon int index\n" << '\n';
    return nullptr;
  }
}
} // namespace STAB

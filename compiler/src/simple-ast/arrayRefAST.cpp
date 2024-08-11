#include "ast.h"
#include <variant>

namespace STAB {
llvm::Value *ArrayRefAST::codegen(Scope *s) {
  if (expr->getType() == "int") {
    auto arrayVarOptional = s->getID(name);

    auto arrayVar =
        std::get_if<llvm::AllocaInst *>(&(arrayVarOptional.value()));

    std::vector<llvm::Value *> indices;
    llvm::Value *zeroIndex =
        llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0));
    indices.emplace_back(zeroIndex);        // Array pointer
    indices.emplace_back(expr->codegen(s)); // Index

    llvm::Value *elementPtr = Builder->CreateGEP(
        (*arrayVar)->getAllocatedType(), *arrayVar, indices, "elementPtr");
    return Builder->CreateLoad(llvm::Type::getInt32Ty(*TheContext), elementPtr);
  } else {
    std::cerr << "\nNon Integer Index\n";
    return nullptr;
  }
}
} // namespace STAB

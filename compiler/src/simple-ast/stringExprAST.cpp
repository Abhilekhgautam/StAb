//
// Created by abhilekh on 5/26/24.
//

#include "./ast.h"

namespace STAB {
llvm::Value *STAB::StringExprAST::codegen(Scope *s) {
  return Builder->CreateGlobalString(val);
}
} // namespace STAB

//
// Created by abhilekh on 5/29/24.
//

#include "./ast.h"

namespace STAB {
llvm::Value *STAB::ElseStatementAST::codegen(Scope *s) {
  llvm::Function *F = s->getFnBlock();
  if (!F) {
    std::cout << "\nnullptr encountered\n";
    return nullptr;
  }

  // generate code for else-if body
  for (const auto elt : elseBody){
    if(s->break_found()) {
        Builder->SetInsertPoint(s->getExitBlock());
        return F;
    } else if (s->skip_found()){
        return F;
    } else {
        elt->codegen(s);
    }
  }

  return F;
}
} // namespace STAB

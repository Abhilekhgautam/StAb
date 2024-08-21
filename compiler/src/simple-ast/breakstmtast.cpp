#include "ast.h"

namespace STAB {
llvm::Value *STAB::BreakStatementAST::codegen(Scope *s) {
  llvm::Function *F = s->getFnBlock();
  if (!F) {
    std::cout << "\nnullptr encountered\n";
    return nullptr;
  }
  if (!s->IsBreakableOrSkippable()){
      color("red", "Error: ");
      color("white", "break ");
      color("blue", "Statement not within any breakable construct.", true);
  } else {
      // break is directly within the loop body.
      if (s->BreakableOrSkippable()){
          Builder->CreateBr(s->getExitBlock());
          s->set_break();
      }
      else{
          Scope *breakableScope = s->getNearestBreakableOrSkippableScope().value();
          //Safety: guaranteed to be a breakable scope
          auto exitBlock = breakableScope->getExitBlock();

          Builder->CreateBr(exitBlock);
          s->set_break();
      }

  }
  return F;
}
} // namespace STAB

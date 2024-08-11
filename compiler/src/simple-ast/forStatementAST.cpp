#include "./ast.h"

namespace STAB {
llvm::Value *ForStatementAST::codegen(Scope *s) {
  llvm::Function *F = s->getFnBlock();
  if (!F) {
    std::cout << "\nnullptr encountered\n";
    return nullptr;
  }

  auto forScope = new Scope(s);

  forScope->setFnBlock(F);

  auto loopStart = range->getStart()->codegen(forScope);
  auto loopEnd = range->getEnd()->codegen(forScope);
  auto loopStep = range->getStep()->codegen(forScope);

  std::string operation;

  if (loopStart >= loopEnd) {
    return F;
  }
  operation = "Add";

  // Set the value for iteration variable
  iterationVariable->codegen(forScope);

  auto var = forScope->getID(iterationVariable->getName());

  if (!var) {
    color("red", "Error: ");
    color("blue", "No Such variable ");
    std::cout << iterationVariable->getName();
    color("blue", " in the current scope", true);
    std::exit(0);
  }

  auto val = std::get_if<llvm::AllocaInst *>(&var.value());
  Builder->CreateStore(loopStart, *val);

  llvm::BasicBlock *loopBody =
      llvm::BasicBlock::Create(*TheContext, "loopBody", F);
  llvm::BasicBlock *afterLoop =
      llvm::BasicBlock::Create(*TheContext, "afterLoop", F);

  // go inside loop body
  Builder->CreateBr(loopBody);
  Builder->SetInsertPoint(loopBody);

  llvm::Value *currentVal =
      Builder->CreateLoad(llvm::Type::getInt32Ty(*TheContext), *val);

  // Create condition for loop execution
  llvm::Value *cond = Builder->CreateICmpSLT(currentVal, loopEnd);

  // Setup loop body
  Builder->SetInsertPoint(loopBody);

  // generate code for loop body
  for (const auto elt : body) {
    elt->codegen(forScope);
  }
  llvm::Value *nextVal;
  if (operation == "Add") {
    nextVal = Builder->CreateAdd(currentVal, loopStep, "nextvar");
  } else {
    nextVal = Builder->CreateSub(currentVal, loopStep);
  }
  Builder->CreateStore(nextVal, *val);

  // compare the expr with 0
  cond = Builder->CreateICmpSLE(nextVal, loopEnd);

  Builder->CreateCondBr(cond, loopBody, afterLoop);
  Builder->SetInsertPoint(afterLoop);

  return F;
}
} // namespace STAB

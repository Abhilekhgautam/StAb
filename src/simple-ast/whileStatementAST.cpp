//
// Created by abhilekh on 5/23/24.
//

#include "./ast.h"

namespace STAB{
llvm::Value* STAB::WhileStatementAST::codegen(Scope* s) {
    llvm::Function* F = s->getFnBlock();
    if (!F) {
        std::cout << "\nnullptr encountered\n";
        return nullptr;
    }

    auto whileScope = new Scope(s);
    whileScope->setFnBlock(F);

    llvm::BasicBlock* loopBody = llvm::BasicBlock::Create(*TheContext, "loopBody", F);
    llvm::BasicBlock* afterLoop = llvm::BasicBlock::Create(*TheContext, "afterLoop", F);
    llvm::BasicBlock* checkCond = llvm::BasicBlock::Create(*TheContext, "checkCond", F);

    // Initial jump to condition check block
    Builder->CreateBr(checkCond);
    Builder->SetInsertPoint(checkCond);

    // Generate code for condition expression
    llvm::Value* cond = expr->codegen(s);

    // Compare the expr with 0 (loop continues if condition is non-zero)
    cond = Builder->CreateICmpNE(cond, llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true)));

    // Create conditional branch
    Builder->CreateCondBr(cond, loopBody, afterLoop);

    // Generate code for loop body
    Builder->SetInsertPoint(loopBody);
    for (const auto& elt : body) {
        elt->codegen(whileScope);
    }

    // After loop body, jump back to condition check
    Builder->CreateBr(checkCond);

    // Set insert point to afterLoop
    Builder->SetInsertPoint(afterLoop);

    return F;
  }

}

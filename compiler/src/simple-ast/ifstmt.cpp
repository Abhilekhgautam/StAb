//
// Created by abhilekh on 5/29/24.
//

#include "./ast.h"

namespace STAB {
llvm::Value *STAB::IfStatementAST::codegen(Scope *s) {
  llvm::Function *F = s->getFnBlock();
  if (!F) {
    std::cout << "\nnullptr encountered\n";
    return nullptr;
  }

  // Evaluate the expression for if
  auto cond = ifStmt->getCond()->codegen(s);

  if (!cond)
    return nullptr;

  // compare the expr with 0
  cond = Builder->CreateICmpEQ(
      cond, llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true)));

  if (elseStmt) {

    // don't want ifBody to be shadowed.
    llvm::BasicBlock *if_Body =
        llvm::BasicBlock::Create(*TheContext, "ifBody", F);
    llvm::BasicBlock *else_Body =
        llvm::BasicBlock::Create(*TheContext, "elseBody", F);
    llvm::BasicBlock *afterIfelse =
        llvm::BasicBlock::Create(*TheContext, "afterIfelse", F);

    Builder->CreateCondBr(cond, else_Body, if_Body);

    Builder->SetInsertPoint(if_Body);

    Scope* ifScope = new Scope(s, "cond");

    ifScope->setFnBlock(F);
    // generate code for if body
    ifStmt->codegen(ifScope);

    if(!ifScope->break_found() and !ifScope->skip_found()) Builder->CreateBr(afterIfelse);

    // Codegen of 'ifBody' can change the current block, update ifBody for the
    // PHI.
    if_Body = Builder->GetInsertBlock();
    /*
    if(ifScope->break_found()){
        Builder->SetInsertPoint(afterIfelse);
        return F;
    } else if(ifScope->skip_found()){
        Builder->SetInsertPoint(afterIfelse);
        return F;
    }
    */
    Builder->SetInsertPoint(else_Body);

    Scope* elseScope = new Scope(s, "cond");
    elseScope->setFnBlock(F);
    // generate code for else body
    elseStmt->codegen(elseScope);

    if(elseScope->break_found()){
        Builder->SetInsertPoint(afterIfelse);
        return F;
    } else if(elseScope->skip_found()){
        Builder->SetInsertPoint(afterIfelse);
        return F;
    }
    Builder->CreateBr(afterIfelse);

    Builder->SetInsertPoint(afterIfelse);

    return F;
  } else {
    // don't want ifBody to be shadowed.
    llvm::BasicBlock *if_Body =
        llvm::BasicBlock::Create(*TheContext, "ifBody", F);
    llvm::BasicBlock *afterIf =
        llvm::BasicBlock::Create(*TheContext, "afterIf", F);

    Builder->CreateCondBr(cond, afterIf, if_Body);

    Builder->SetInsertPoint(if_Body);

    Scope* ifScope = new Scope(s, "cond");

    ifScope->setFnBlock(F);
    ifScope->setExitBlock(afterIf);

    // generate code for if body
    ifStmt->codegen(ifScope);
    if(ifScope->break_found()){
        Builder->SetInsertPoint(afterIf);
        return F;
    } else if(ifScope->skip_found()){
        Builder->SetInsertPoint(afterIf);
        return F;
    }
    Builder->CreateBr(afterIf);

    // Codegen of 'ifBody' can change the current block, update ifBody for the
    // PHI.
    if_Body = Builder->GetInsertBlock();

    Builder->SetInsertPoint(afterIf);

    return F;
  }

  // return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*TheContext));
}
} // namespace STAB

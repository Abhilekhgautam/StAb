//
// Created by abhilekh on 5/29/24.
//

#include "./ast.h"
#include <cstdio>
#include <llvm-18/llvm/IR/BasicBlock.h>

namespace STAB{
    llvm::Value* STAB::IfStatementAST::codegen(Scope* s){
        llvm::Function* F = s->getFnBlock();
        if (!F){
            std::cout << "\nnullptr encountered\n";
            return nullptr;
        }

	// Evaluate the expression for if
	auto cond = ifStmt->getCond()->codegen(s);

	if (!cond) return nullptr;

        // compare the expr with 0
        cond = Builder->CreateICmpEQ(cond, llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true)));

	// don't want ifBody to be shadowed.
        llvm::BasicBlock* if_Body = llvm::BasicBlock::Create(*TheContext,"ifBody", F);
        llvm::BasicBlock* else_Body = llvm::BasicBlock::Create(*TheContext, "elseBody", F);
	llvm::BasicBlock* afterIfelse = llvm::BasicBlock::Create(*TheContext, "afterIfelse", F);

        Builder->CreateCondBr(cond, if_Body, else_Body);

	Builder->SetInsertPoint(if_Body);
	
        // generate code for if body
        auto ifValue =  ifStmt->codegen(s);

	Builder->CreateBr(afterIfelse);

	// Codegen of 'ifBody' can change the current block, update ifBody for the PHI.
        if_Body = Builder->GetInsertBlock();

	F->insert(F->end(), else_Body);
	Builder->SetInsertPoint(else_Body);

	// generate code for else body
	auto elseValue = elseStmt->codegen(s);

	Builder->CreateBr(afterIfelse);

	F->insert(F->end(), afterIfelse);

        Builder->SetInsertPoint(afterIfelse);

	return F;

        //return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*TheContext));
    }
}

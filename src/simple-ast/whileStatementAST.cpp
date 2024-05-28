//
// Created by abhilekh on 5/23/24.
//

#include "./ast.h"

namespace STAB{
    llvm::Value* STAB::WhileStatementAST::codegen(Scope* s){
        llvm::Function* F = s->getFnBlock();
        if (!F){
            std::cout << "\nnullptr encountered\n";
            return nullptr;
        }
        llvm::BasicBlock* loopBody = llvm::BasicBlock::Create(*TheContext,"loopBody", F);
        llvm::BasicBlock* afterLoop = llvm::BasicBlock::Create(*TheContext, "afterLoop", F);

        // go inside loop body
        Builder->CreateBr(loopBody);
        Builder->SetInsertPoint(loopBody);

        // generate code for loop body
        for(const auto elt: body){
            elt->codegen(s);
        }

        llvm::Value* cond = expr->codegen(s);

        // compare the expr with 0
        cond = Builder->CreateICmpEQ(cond, llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true)));

        Builder->CreateCondBr(cond, loopBody, afterLoop);
        Builder->SetInsertPoint(afterLoop);

        return F;

        //return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*TheContext));
    }
}

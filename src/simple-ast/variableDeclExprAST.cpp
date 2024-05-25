//
// Created by abhilekh on 5/23/24.
//

#include "./ast.h"

namespace STAB{
    llvm::Value* STAB::VariableDeclExprAST::codegen(Scope* s){
        llvm::BasicBlock* bblock = llvm::BasicBlock::Create(*TheContext, s->getName(), s->getFnBlock(), 0);

        auto type = llvm::Type::getInt32Ty(*TheContext);
        Builder->SetInsertPoint(bblock);
        llvm::AllocaInst* var = Builder->CreateAlloca(type,nullptr, Name);
        s->installID(Name, var);
        //NamedValues[Name] = var;
        //NamedLLVMType[Name] = type;

        return Builder->CreateLoad(type, var);
    }
}

//
// Created by abhilekh on 5/23/24.
//

#include "./ast.h"

namespace STAB{
    llvm::Value* STAB::NumberExprAST::codegen(Scope* s){
        return llvm::ConstantInt::get(*TheContext, llvm::APInt(32, val, true));
    }
}

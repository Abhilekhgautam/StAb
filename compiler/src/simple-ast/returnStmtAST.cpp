//
// Created by abhilekh on 5/23/24.
//

#include "./ast.h"

namespace STAB{
    llvm::Value* STAB::ReturnStmtAST::codegen(Scope* s){
        auto retVal = expr->codegen(s);
        return Builder->CreateRet(retVal);
    }
}


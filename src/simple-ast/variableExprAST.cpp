//
// Created by abhilekh on 5/23/24.
//

#include "./ast.h"

namespace STAB{
    llvm::Value* STAB::VariableExprAST::codegen(Scope* s){
        //llvm::AllocaInst* var = NamedValues[Name];
        auto var = s->getID(Name);
        // todo: better error handling later
        if (!var){
            std::cout << "No such variable " << Name << " in the current scope\n";
        }
        return Builder->CreateLoad(var->getAllocatedType(), var, Name.c_str());
    }
}

//
// Created by abhilekh on 5/23/24.
//

#include "./ast.h"

namespace STAB{
    llvm::Value* STAB::VariableAssignExprAST::codegen(Scope* s){
        // todo:  check if the variable exists
        auto varInst = s->getID(Name);
        if (!varInst){
            std::cout << "No such variable " << Name << " initialized in the current scope\n";
        }
        llvm::Value* val = RHS->codegen(s);
        //llvm::AllocaInst* var = NamedValues[Name];
        return Builder->CreateStore(val, varInst);
    }
}

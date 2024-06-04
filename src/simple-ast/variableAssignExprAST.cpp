//
// Created by abhilekh on 5/23/24.
//

#include "./ast.h"
#include <llvm-18/llvm/IR/Instructions.h>

namespace STAB{
    llvm::Value* STAB::VariableAssignExprAST::codegen(Scope* s){
        // todo:  check if the variable exists
        auto varInst = s->getID(Name);
        if (!varInst){
            std::cout << "No such variable " << Name << " initialized in the current scope\n";
        }
        llvm::Value* val = RHS->codegen(s);
        //llvm::AllocaInst* var = NamedValues[Name];
	if (auto var = std::get_if<llvm::AllocaInst*>(&(varInst.value())))
            return Builder->CreateStore(val, *var);

        return nullptr;
    }
}

//
// Created by abhilekh on 5/23/24.
//

#include "./ast.h"

namespace STAB{
    llvm::Value* STAB::VariableDeclAssignExprAST::codegen(Scope* s){
        varDecl->codegen(s);
        auto var = s->getID(varDecl->getName());
        //auto var = NamedValues[varDecl->getName()];
        auto va = val->codegen(s);

        return Builder->CreateStore(va, var);
    }
}

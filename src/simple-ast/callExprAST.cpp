//
// Created by abhilekh on 5/23/24.
//

#include "./ast.h"

namespace STAB{
    llvm::Value* STAB::CallExprAST::codegen(Scope* s){
        llvm::Function* calleeFn = TheModule->getFunction(Callee);
        if (!calleeFn){
            std::cerr << "\nNo Such function exist\n";
            return nullptr;
        }
        // check the number of arguments passed
        if(calleeFn->arg_size() != Args.size()){
            std::cerr << "\n Function " << Callee << " expects " << calleeFn->arg_size() << " but " << Args.size() << " were passed\n";
            return nullptr;
        }
        std::vector<llvm::Value*> args;
        for(const auto expr: Args){
            args.emplace_back(expr->codegen(s));
        }
        return Builder->CreateCall(calleeFn, args, "calltmp");
    }
}

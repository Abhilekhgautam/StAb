//
// Created by abhilekh on 5/23/24.
//

#include "./ast.h"
#include <llvm-18/llvm/IR/GlobalVariable.h>
#include <llvm-18/llvm/IR/Instructions.h>
#include <llvm-18/llvm/Support/Casting.h>

namespace STAB{
    llvm::Value* STAB::VariableExprAST::codegen(Scope* s){
        //llvm::AllocaInst* var = NamedValues[Name];
	std::optional<valType> var = s->getID(Name);
        // todo: better error handling later
        if (!var.has_value()){
            std::cout << "No such variable " << Name << " in the current scope\n";
	    return nullptr;
        }
	if (auto val = std::get_if<llvm::AllocaInst*>(&var.value())){
	  return Builder->CreateLoad((*val)->getAllocatedType(), *val, Name.c_str());
	}

	if (auto gVar = (std::get_if<llvm::GlobalVariable*>(&var.value()))){
          return Builder->CreateLoad((*gVar)->getValueType(), *gVar);                             		
	}
	return nullptr;
    }
}

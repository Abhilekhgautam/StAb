//
// Created by abhilekh on 5/23/24.
//

#include "./ast.h"
#include <llvm-18/llvm/IR/DerivedTypes.h>

namespace STAB{
    llvm::Value* STAB::VariableDeclExprAST::codegen(Scope* s){

        llvm::IntegerType* type = nullptr;

	if(getType() == "string")
          type = llvm::Type::getInt8Ty(*TheContext);	  	
	else 
          type = llvm::Type::getInt32Ty(*TheContext);
        
        llvm::AllocaInst* var = Builder->CreateAlloca(type,nullptr, Name);
        s->installID(Name, var);
        //NamedValues[Name] = var;
        //NamedLLVMType[Name] = type;

        return Builder->CreateLoad(type, var);
    }
}

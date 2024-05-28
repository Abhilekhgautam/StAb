//
// Created by abhilekh on 5/23/24.
//

#include "./ast.h"

namespace STAB{
    llvm::Value* STAB::CallExprAST::codegen(Scope* s){
        llvm::Function* calleeFn = TheModule->getFunction(Callee);
	if (Callee == "println"){
	  auto printlnFunc = TheModule->getOrInsertFunction("printf", llvm::FunctionType::get(llvm::IntegerType::getInt32Ty(*TheContext), llvm::PointerType::get(llvm::Type::getInt8Ty(*TheContext), 0), true));
	  std::vector<llvm::Value*> ArgsV;
          for (unsigned i = 0, e = Args.size(); i != e; ++i)
             ArgsV.push_back(Args[i]->codegen(s));

          return Builder->CreateCall(printlnFunc, ArgsV, "printlnCall");
	}

        if (!calleeFn){
            std::cerr << "\nNo function" << Callee << "exist\n";
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

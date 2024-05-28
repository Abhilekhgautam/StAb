//
// Created by abhilekh on 5/26/24.
//

#include "./ast.h"

namespace STAB{
    llvm::Value* STAB::CallStatementAST::codegen(Scope* s){
        llvm::Function* calleeFn = TheModule->getFunction(Callee);
        if (Callee == "println"){
	     auto printlnFunc = TheModule->getOrInsertFunction("println", llvm::FunctionType::get(llvm::IntegerType::getInt32Ty(*TheContext), llvm::PointerType::get(llvm::Type::getInt8Ty(*TheContext), 0), true));
	     std::vector<llvm::Value*> ArgsV;
             for (unsigned i = 0, e = Args.size(); i != e; ++i){
		  if(i == 0 && Args[0]->getType() == "string"){
	              STAB::StringExprAST* strVal = reinterpret_cast<STAB::StringExprAST*>(Args[0]);
		      std::string val = strVal->getVal();
		      val += '\n';
		      Args[0] = new STAB::StringExprAST(val);
		  }
		  // add new line for println
                  auto temp = Args[i]->codegen(s);
		  temp->print(llvm::errs());
		  ArgsV.push_back(temp);
	     }

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

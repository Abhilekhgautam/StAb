
#include "./ast.h"

namespace STAB{
    llvm::Function* STAB::FunctionAST::codegen(class Scope* s){
        std::vector<llvm::Type*> params(Proto->getArgSize(), llvm::Type::getInt32Ty(*TheContext));
        llvm::FunctionType* FT;
        if (Proto->getReturnType() == "void") {
            FT = llvm::FunctionType::get(llvm::Type::getVoidTy(*TheContext), params, false);
        }else {
            FT =  llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext), params, false);
        }
        
	// Check if such function already exists 
	llvm::Function* F = TheModule->getFunction(Proto->getName());

	if (F) {
          std::cerr << "\nError: Cannot have 2 functions with the same name\n.Function " << Proto->getName() << " already defined\n";
	  return nullptr;
	}

	if(Proto->getName() == "__start__"){
            // Check if __start__fn already exists
            F = TheModule->getFunction("__start__");
            if (!F) {
                F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "__start__", TheModule.get());
                llvm::BasicBlock* fnBlock = llvm::BasicBlock::Create(*TheContext, "entry", F);
                 Builder->SetInsertPoint(fnBlock);
             } else {
               // Set the insert point to the end of the existing __start__fn function
               llvm::BasicBlock &lastBlock = F->back();
               Builder->SetInsertPoint(&lastBlock);
             }	   	
	} else {
          F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, Proto->getName(), TheModule.get());
          llvm::BasicBlock* fnBlock = llvm::BasicBlock::Create(*TheContext, Proto->getName(), F);
          Builder->SetInsertPoint(fnBlock);		
	}

        fnBlocks.emplace_back(F);

        Scope->setFnBlock(F);
       // llvm::BasicBlock* fnBlock = llvm::BasicBlock::Create(*TheContext, Proto->getName(), F);
       // Builder->SetInsertPoint(fnBlock);

        for(const auto params: declVars){
             params->codegen(Scope);
        }
        for(const auto body: Body){
           body->codegen(Scope);
        }
        // Check for proper termination
        bool hasReturn = false;
        llvm::BasicBlock* lastBlock = nullptr;
        for (auto &BB : *F) {
            if (BB.getTerminator()) {
                if (llvm::isa<llvm::ReturnInst>(BB.getTerminator()) && Proto->getReturnType() == "void") {
                    std::cerr << "\nError: Void Function cannot have a return statement\n";
                    return nullptr;
                } else {
                    hasReturn = true;
                }
                lastBlock = &BB;
            }
        }
        if(lastBlock)
            Builder->SetInsertPoint(lastBlock);

        if (Proto->getReturnType() == "void") {
            Builder->CreateRetVoid();
        }
        // If no return statement was found and the function is non-void, this is an error.
        if (!hasReturn && Proto->getReturnType() != "void") {
            std::cerr << "\nError: Non-void function does not have a return statement\n";
            return nullptr;
        }

        llvm::verifyFunction(*F);
        // just to check the generated IR
        // todo: Change to actual thing that will be returned
        return F;
    }
}

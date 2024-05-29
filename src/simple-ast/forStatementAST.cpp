#include "./ast.h"
#include <llvm-18/llvm/IR/Type.h>

namespace STAB {
    llvm::Value* ForStatementAST::codegen(Scope* s){
      llvm::Function* F = s->getFnBlock();
        if (!F){
            std::cout << "\nnullptr encountered\n";
            return nullptr;
        }

        auto loopStart = range->getStart()->codegen(s);
        auto loopEnd = range->getEnd()->codegen(s);
        auto loopStep = range->getStep()->codegen(s);

	std::string operation;

	if(loopStart == loopEnd){
	  return F;	
	}

	if (loopStart < loopEnd){
          operation = "Add";
	} else {
	  operation = "Sub";	
	}
	
        // Set the value for iteration variable
        auto temp = iterationVariable->codegen(s);
        Builder->CreateStore(loopStart, s->getID(iterationVariable->getName()));

        llvm::BasicBlock* loopBody = llvm::BasicBlock::Create(*TheContext,"loopBody", F);
        llvm::BasicBlock* afterLoop = llvm::BasicBlock::Create(*TheContext, "afterLoop", F);


        // go inside loop body
        Builder->CreateBr(loopBody);
        Builder->SetInsertPoint(loopBody);

	llvm::Value* currentVal = Builder->CreateLoad(llvm::Type::getInt32Ty(*TheContext), s->getID(iterationVariable->getName()));
	
        // generate code for loop body
        for(const auto elt: body){
            elt->codegen(s);
        }
	llvm::Value* nextVal;
        if (operation == "Add"){
	  nextVal = Builder->CreateAdd(currentVal, loopStep, "nextvar");	
	} else {
           nextVal = Builder->CreateSub(currentVal, loopStep);		
	}
        Builder->CreateStore(nextVal, s->getID(iterationVariable->getName()));

        // compare the expr with 0
	llvm::Value* cond = Builder->CreateICmpSLE(nextVal, loopEnd);

        Builder->CreateCondBr(cond, loopBody, afterLoop);
        Builder->SetInsertPoint(afterLoop);

        return F;


    } 
}

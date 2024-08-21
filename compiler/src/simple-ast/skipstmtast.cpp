#include "ast.h"

namespace STAB {
    llvm::Value* SkipStatementAST::codegen(Scope* s){
        llvm::Function* F = s->getFnBlock();
        if(!F){
            std::cout << "\nnullptr encountered";
            return nullptr;
        }
        if(!s->IsBreakableOrSkippable()){
            color("red", "Error ");
            color("white", "skip ");
            color("blue", "statment not within any skippable constructs");
        } else {
            // skip directly within the loop
            if(s->BreakableOrSkippable()){
                s->set_skip();
            }
            else {
                Scope* skippableScope = s->getNearestBreakableOrSkippableScope().value();
                //Builder->SetInsertPoint(skippableScope->getEntryBlock());
                Builder->CreateBr(skippableScope->getEntryBlock());

                s->set_skip();
            }
        }
        return F;
    }
}

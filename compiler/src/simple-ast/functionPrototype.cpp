
#include "./ast.h"

namespace STAB{
    llvm::Function* STAB::PrototypeAST::codegen(Scope* s){
         // check for the return type
        // Make the function type:  double(double,double) etc.
        std::vector<llvm::Type*> Ints(Args.size(), llvm::Type::getInt32Ty(*TheContext));
        llvm::FunctionType* FT;
        if (RetType == "void") {
            FT = llvm::FunctionType::get(llvm::Type::getVoidTy(*TheContext), Ints, false);
        }else {
            FT =  llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext), Ints, false);
        }
        llvm::Function *F =
                llvm::Function::Create(FT, llvm::Function::ExternalLinkage, Name, TheModule.get());

        //Set names for all arguments.
        unsigned Idx = 0;
        for (auto &Arg : F->args())
            Arg.setName(Args[Idx++]);

        return F;
    }
}


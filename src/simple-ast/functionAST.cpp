
#include "./ast.h"
#include <llvm-18/llvm/IR/Instructions.h>
#include <llvm-18/llvm/IR/Value.h>

namespace STAB{
llvm::Function* STAB::FunctionAST::codegen(class Scope* s) {
    std::vector<llvm::Type*> params(Proto->getArgSize(), llvm::Type::getInt32Ty(*TheContext));
    llvm::FunctionType* FT;

    // Determine the function return type
    if (Proto->getReturnType() == "void") {
        FT = llvm::FunctionType::get(llvm::Type::getVoidTy(*TheContext), params, false);
    } else {
        FT = llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext), params, false);
    }
    
    // Check if such function already exists 
    llvm::Function* F = TheModule->getFunction(Proto->getName());

    if (F) {
        std::cerr << "\nError: Cannot have 2 functions with the same name\n.Function " << Proto->getName() << " already defined\n";
        return nullptr;
    }

    if (Proto->getName() == "__start__") {
        F = TheModule->getFunction("__start__");
        if (!F) {
            F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "__start__", TheModule.get());
            llvm::BasicBlock* fnBlock = llvm::BasicBlock::Create(*TheContext, "entry", F);
            Builder->SetInsertPoint(fnBlock);
        } else {
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

    std::vector<std::string> names;
    // Codegen for function parameters5
    for(const auto params: declVars) {
	auto name = params->getName();
	std::cerr << "\nOk got a " << name << " param baby\n";
	params->codegen(Scope);
	names.emplace_back(name);
    }

    // Store each function argument
    unsigned idx = 0;
    for (auto &Arg : F->args()) {
        Builder->CreateStore(&Arg, Scope->getID(names[idx]));
	++idx;
    }

    // Codegen for function body
    for(const auto body: Body) {
        body->codegen(Scope);
    }

    // Ensure a return statement if none exists
    llvm::BasicBlock* currentBlock = Builder->GetInsertBlock();
    if (!currentBlock->getTerminator()) {
        if (Proto->getReturnType() == "void") {
            Builder->CreateRetVoid();
        } else {
            std::cerr << "\nError: Non-void function does not have a return statement\n";
            return nullptr;
        }
    }
    // Special case for __start__
    if (Proto->getName() == "__start__") {
        llvm::BasicBlock* lastBlock = Builder->GetInsertBlock();
        if (!lastBlock->getTerminator()) {
            Builder->CreateRetVoid();
        }
    }

    llvm::verifyFunction(*F);
    return F;
 }

}

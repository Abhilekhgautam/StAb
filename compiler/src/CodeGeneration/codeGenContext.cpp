//
// Created by abhilekh on 5/8/24.
//
#include "codeGenContext.h"
#include "llvm/Support/TargetSelect.h"

namespace STAB {
    codeGenContext::codeGenContext(std::ostream& out):out(out) {
      llvm::InitializeNativeTarget();
      llvm::InitializeNativeTargetAsmParser();
      llvm::InitializeNativeTargetAsmPrinter();

      module = new llvm::Module("STAB", context);
    }

    // bacis setups
    void codeGenContext::setupBuiltIns() {
        intType = llvm::IntegerType::get(context, 32);
        llvmTypeMap["int"] = intType;

        auto int8Ty = llvm::Type::getIntNTy(getLLVMContext(), 8);
        auto int8PtrTy = llvm::PointerType::get(int8Ty, 0);
        std::vector<llvm::Type*> argTypesInt8Ptr(1, int8PtrTy);
        // create a function type which returns an int and takes int as parameters
        llvm::FunctionType* Ft = llvm::FunctionType::get(llvm::Type::getVoidTy(getLLVMContext()), argTypesInt8Ptr, false);

        llvm::Function* F = llvm::Function::Create(Ft, llvm::Function::ExternalLinkage, "println", getModule());

        builtIns.emplace_back({F, (void*)println})
    }
}
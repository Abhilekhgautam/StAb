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
}
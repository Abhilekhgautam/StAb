//
// Created by abhilekh on 5/23/24.
//

#include "./ast.h"

namespace STAB {
llvm::Value *STAB::CallExprAST::codegen(Scope *s) {
  llvm::Function *calleeFn = TheModule->getFunction(Callee);
  if (Callee == "println") {
    auto printlnFunc = TheModule->getOrInsertFunction(
        "printf",
        llvm::FunctionType::get(llvm::IntegerType::getInt32Ty(*TheContext),
                                llvm::PointerType::get(*TheContext, 0), true));
    std::vector<llvm::Value *> ArgsV;
    for (unsigned i = 0, e = Args.size(); i != e; ++i)
      ArgsV.push_back(Args[i]->codegen(s));

    return Builder->CreateCall(printlnFunc, ArgsV, "printlnCall");
  }

  if (!calleeFn) {
    color("red", "Error: ");
    color("blue", "No function ");
    std::cout << Callee;
    color("blue", " defined", true);
    std::exit(0);
  }
  // check the number of arguments passed
  if (calleeFn->arg_size() != Args.size()) {
    color("red", "Error: ");
    color("blue", "Function ");
    std::cout << Callee;
    color("blue", " expects ");
    std::cout << calleeFn->arg_size();
    color("blue", " arguments but ");
    std::cout << Args.size();
    color("blue", " were provided", true);
    std::exit(0);
  }

  std::vector<llvm::Value *> args;
  for (const auto expr : Args) {
    args.emplace_back(expr->codegen(s));
  }
  return Builder->CreateCall(calleeFn, args, "calltmp");
}
} // namespace STAB

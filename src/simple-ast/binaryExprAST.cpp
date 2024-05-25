//
// Created by abhilekh on 5/23/24.
//

#include "./ast.h"

namespace STAB{
    llvm::Value* STAB::BinaryExprAST::codegen(Scope* s){
        llvm::Value *L = LHS->codegen(s);
        llvm::Value *R = RHS->codegen(s);
        if (!L || !R)
            return nullptr;

        const char* temp = Op.c_str();
        char op = temp[0];

        switch (op) {
            case '+':
                return Builder->CreateAdd(L, R, "addtmp");
            case '-':
                return Builder->CreateSub(L, R, "subtmp");
            case '*':
                return Builder->CreateMul(L, R, "multmp");
            case '<':
                L = Builder->CreateICmpULT(L, R, "cmplt");
                return Builder->CreateZExt(L, llvm::Type::getInt32Ty(*TheContext), "int32Val");
            case '>':
                L = Builder->CreateICmpUGT(L, R, "cmpgt");
                return Builder->CreateZExt(L, llvm::Type::getInt32Ty(*TheContext), "int32Val");
            case 'l':
                L = Builder->CreateICmpUGT(L, R, "cmplte");
                return Builder->CreateZExt(L, llvm::Type::getInt32Ty(*TheContext), "int32Val");
            case 'g':
                L = Builder->CreateICmpSGE(L, R, "cmpgte");
                return Builder->CreateZExt(L, llvm::Type::getInt32Ty(*TheContext), "int32Val");
            case 'e':
                L = Builder->CreateICmpEQ(L, R, "cmpeq");
                return Builder->CreateZExt(L, llvm::Type::getInt32Ty(*TheContext), "int32Val");
            case 'n':
                L = Builder->CreateICmpNE(L, R, "cmpne");
                return Builder->CreateZExt(L, llvm::Type::getInt32Ty(*TheContext), "int32Val");

            default:
                std::cout << "invalid binary operator";
                return nullptr;
        }
    }
}


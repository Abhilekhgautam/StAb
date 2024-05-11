//
// Created by abhilekh on 5/11/24.
//
#pragma once

#include <llvm-18/llvm/IR/BasicBlock.h>
#include <llvm-18/llvm/IR/Instructions.h>
#include <llvm-18/llvm/IR/Metadata.h>
#ifndef STAB_AST_H
#define STAB_AST_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <memory>

#include <llvm/IR/Value.h>
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"

#ifndef STAB_GLOBAL_H
#include "../globals.h"
#endif 

namespace STAB{
    class ExprAST{
    public:
        virtual ~ExprAST() = default;
        virtual llvm::Value *codegen() = 0;
    };

    class NumberExprAST: public ExprAST{
        int val;
    public:
        NumberExprAST(int val):val(val){}
    };

    class VariableDeclExprAST: public ExprAST {
       std::string Type;
       std::string Name;
     public:
       VariableDeclExprAST(std::string& Type, std::string& Name):
	       Type(Type), Name(Name){}
       llvm::Value* codegen() override{
	 llvm::BasicBlock* bblock = llvm::BasicBlock::Create(*TheContext, "entry", mainFunction, 0);
         
	 auto type = llvm::Type::getInt32Ty(*TheContext);
	 Builder->SetInsertPoint(bblock);
	 llvm::AllocaInst* var = Builder->CreateAlloca(type,nullptr, Name);
	 NamedValues.insert({Name, var});
	 NamedLLVMType.insert({Name, type});
	 
	 return Builder->CreateLoad(type, var);
       }
    };

// VariableExprAST - Expression class for referencing a variable, like "a".
    class VariableExprAST : public ExprAST {
        std::string Name;

    public:
        VariableExprAST(const std::string &Name) : Name(Name) {}
    };

// BinaryExprAST - Expression class for a binary operator.
    class BinaryExprAST : public ExprAST {
        // char would have worked but
        // kinda hard to integrate with YACC
        std::string Op;
        ExprAST* LHS;
        ExprAST* RHS;

    public:
        BinaryExprAST(std::string Op, ExprAST* LHS,
                      ExprAST* RHS)
                : Op(Op), LHS(LHS), RHS(RHS) {}
        ~BinaryExprAST(){
            delete LHS;
            delete RHS;
        }
        llvm::Value* codegen() override{
            llvm::Value *L = LHS->codegen();
            llvm::Value *R = RHS->codegen();
            if (!L || !R)
                return nullptr;

            char op = Op[0];

            switch (op) {
                case '+':
                    return Builder->CreateFAdd(L, R, "addtmp");
                case '-':
                    return Builder->CreateFSub(L, R, "subtmp");
                case '*':
                    return Builder->CreateFMul(L, R, "multmp");
                case '<':
                    L = Builder->CreateFCmpULT(L, R, "cmptmp");
                    // Convert bool 0/1 to double 0.0 or 1.0
                    return Builder->CreateUIToFP(L, llvm::Type::getDoubleTy(*TheContext),
                                                 "booltmp");
                default:
                    std::cout << "invalid binary operator";
            }
        }
    };

// CallExprAST - Expression class for function calls.
//    class CallExprAST : public ExprAST {
//        std::string Callee;
//        std::vector<ExprAST*> Args;
//
//    public:
//        CallExprAST(const std::string &Callee,
//                    std::vector<ExprAST*> Args)
//                : Callee(Callee), Args(std::move(Args)) {}
//        llvm::Value* codegen() override;
//    };

// PrototypeAST - This class represents the "prototype" for a function,
// which captures its name, and its argument names (thus implicitly the number
// of arguments the function takes).
    class PrototypeAST {
        std::string RetType;
        std::string Name;
        std::vector<std::string> Args;

    public:
        PrototypeAST(const std::string& RetType,const std::string &Name, std::vector<std::string> Args)
                : RetType(RetType),Name(Name), Args(std::move(Args)) {}

        const std::string &getName() const { return Name; }

        llvm::Function* codegen(){
	    // check for the return type 
            // Make the function type:  double(double,double) etc.
            //std::vector<llvm::Type*> Ints(0, llvm::Type::getInt32Ty(*TheContext));
	    llvm::FunctionType* FT;
	    if (RetType == "void") {
	       FT = llvm::FunctionType::get(llvm::Type::getVoidTy(*TheContext), {}, false);	    
	    }else {
               FT =  llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext), {}, false);
            }
            llvm::Function *F =
                    llvm::Function::Create(FT, llvm::Function::ExternalLinkage, Name, TheModule.get());
            
            //Set names for all arguments.
            unsigned Idx = 0;
            for (auto &Arg : F->args())
                Arg.setName(Args[Idx++]);

            return F;
        }

    };

// FunctionAST - This class represents a function definition itself.
    class FunctionAST {
        PrototypeAST* Proto;
        ExprAST* Body;

    public:
        FunctionAST(PrototypeAST* Proto,
                    ExprAST* Body)
                : Proto(Proto), Body(Body) {}
    };
}


#endif //STAB_AST_H

//
// Created by abhilekh on 5/11/24.
//
#pragma once

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

#include <llvm/ADT/APInt.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Metadata.h>

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
	llvm::Value* codegen() override {
	 return llvm::ConstantInt::get(*TheContext, llvm::APInt(32, val, true));
	}
    };
    // base class for all statements
    class StatementAST {
       public:
	  virtual llvm::Value* codegen() = 0;
	    
    };


    class VariableDeclExprAST: public StatementAST {
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

    class VariableExprAST : public ExprAST {
      std::string Name;

      public:
        VariableExprAST(const std::string &Name) : Name(Name) {}
	llvm::Value* codegen() override {
           llvm::AllocaInst* var = NamedValues[Name];		
	   // todo: better error handling later 
	   if (!var){
	    std::cout << "nullptr deref baby\n";	   
	   }
	   return Builder->CreateLoad(var->getAllocatedType(), var, Name.c_str());
	}
    };


    class VariableAssignExprAST: public StatementAST {
       std::string Name;
       // just int for now.
       ExprAST* RHS;
       public:
        VariableAssignExprAST(std::string Name, ExprAST* val):
	    Name(Name), RHS(val){}
	llvm::Value* codegen() override {
              // todo:  check if the variable exists
	      llvm::Value* val = RHS->codegen();
	      llvm::AllocaInst* var = NamedValues[Name];
	      return Builder->CreateStore(val, var);
	}
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
    class PrototypeAST: public StatementAST {
        std::string RetType;
        std::string Name;
        std::vector<std::string> Args;

    public:
        PrototypeAST(const std::string& RetType,const std::string &Name, std::vector<std::string> Args)
                : RetType(RetType),Name(Name), Args(std::move(Args)) {}

        const std::string &getName() const { return Name; }

        llvm::Function* codegen() override{
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
    class FunctionAST: public StatementAST {
        PrototypeAST* Proto;
        StatementAST* Body;

    public:
        FunctionAST(PrototypeAST* Proto,
                    StatementAST* Body)
                : Proto(Proto), Body(Body) {}
	// did this just for my code to compile
	// todo: add the actual implementation
	llvm::Function* codegen() override{
	  llvm::FunctionType* FT;
	  llvm::Function* F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, Proto->getName(), TheModule.get());	
	}
    };
}


#endif //STAB_AST_H

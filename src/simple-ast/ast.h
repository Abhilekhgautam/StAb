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
#include "llvm/IR/Verifier.h"
#include <llvm/IR/Constant.h>
#include <llvm/IR/Function.h>
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
        virtual llvm::Value *codegen(Scope* s) = 0;
	virtual std::string getType() = 0;
    };

    class NumberExprAST: public ExprAST{
        int val;
    public:
        NumberExprAST(int val):val(val){}
	llvm::Value* codegen(Scope* s) override {
	 return llvm::ConstantInt::get(*TheContext, llvm::APInt(32, val, true));
	}
	// just for now
	std::string getType() override{return "int";}
    };
    // base class for all statements
    class StatementAST {
       public:
	  virtual ~StatementAST() = default;
	  virtual llvm::Value* codegen(Scope* s) = 0;
	    
    };

    // int x;
    class VariableDeclExprAST: public StatementAST {
       std::string Type;
       std::string Name;
     public:
       VariableDeclExprAST(std::string& Type, std::string& Name):
	       Type(Type), Name(Name){}
       std::string getType()const {return Type;}
       std::string getName() const {return Name;}
       llvm::Value* codegen(Scope* s) override{
	 llvm::BasicBlock* bblock = llvm::BasicBlock::Create(*TheContext, s->getName(), s->getFnBlock(), 0);
         
	 auto type = llvm::Type::getInt32Ty(*TheContext);
	 Builder->SetInsertPoint(bblock);
	 llvm::AllocaInst* var = Builder->CreateAlloca(type,nullptr, Name);
	 s->installID(Name, var);
	 //NamedValues[Name] = var;
	 //NamedLLVMType[Name] = type;
	 
	 return Builder->CreateLoad(type, var);
       }
    };

    // int x = 5;
    class VariableDeclAssignExprAST: public StatementAST {
	VariableDeclExprAST* varDecl;
	// type is int for now
	ExprAST* val;

	public: 
	   VariableDeclAssignExprAST(VariableDeclExprAST* varDecl, ExprAST* val):
		   varDecl(varDecl), val(val){}
           llvm::Value* codegen(Scope* s) override {
               varDecl->codegen(s);
	       auto var = s->getID(varDecl->getName());
               //auto var = NamedValues[varDecl->getName()];
	       auto va = val->codegen(s);
	      
	       return Builder->CreateStore(va, var);
	   }
    };
    // while loop 
    // while cond {
    //
    // }
    class WhileStatementAST: public StatementAST {
      ExprAST* expr;
      std::vector<StatementAST*> body;
      public: 
         WhileStatementAST(ExprAST* expr, std::vector<StatementAST*> body)
		 : expr(expr), body(std::move(body)){}
	 llvm::Value* codegen(Scope* s) override {
	    llvm::Function* F = s->getFnBlock();
	    if(F == mainFunction){
	        std::cout << "Both are same\n";
	    }
	    if (!F){
	      std::cout << "nullptr encountered";
	      return nullptr;
	    }
	    llvm::BasicBlock* loopBody = llvm::BasicBlock::Create(*TheContext,"loopBody", F);
            llvm::BasicBlock* afterLoop = llvm::BasicBlock::Create(*TheContext, "afterLoop", F);

            // go inside loop body 
	    Builder->CreateBr(loopBody);
	    Builder->SetInsertPoint(loopBody);

	    // generate code for loop body 
	    for(const auto elt: body){
	       auto temp = elt->codegen(s);
	       temp->print(llvm::errs());
	    }

	    llvm::Value* cond = expr->codegen(s);

	    // compare the expr with 0
	    cond = Builder->CreateICmpEQ(cond, llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true)));

	    Builder->CreateCondBr(cond, afterLoop, loopBody);
	    Builder->SetInsertPoint(afterLoop);

	    return F;

	    //return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*TheContext));
           }
    };

    /// A class for infinite loop
    /// loop {}
    class LoopStatementAST: public StatementAST{
	    std::vector<StatementAST*> body;
       public: 
          LoopStatementAST(std::vector<StatementAST*> body): body(std::move(body)){}
	  llvm::Value* codegen(Scope* s) override {
            llvm::Function* F = s->getFnBlock();
	    // block to insert the code for loop body
	    llvm::BasicBlock* loopBody = llvm::BasicBlock::Create(*TheContext, "loopBody", F);
	    // block to insert the code after the loop ends;
	    llvm::BasicBlock* afterLoop = llvm::BasicBlock::Create(*TheContext, "afterLoop", F);

	    // get into loop body 
	    Builder->CreateBr(loopBody);
	    Builder->SetInsertPoint(loopBody);

	    for (const auto elt: body){
	      elt->codegen(s);	    
	    }
            
	    // this is an infinte loop 
	    // again enter the loop body 
	    Builder->CreateCondBr(llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 1, true)),loopBody, afterLoop);
	    Builder->SetInsertPoint(afterLoop);

	    return F;
            
	  }
    };
    // Represents referencing of variables..
    class VariableExprAST : public ExprAST {
      std::string Name;

      public:
        VariableExprAST(const std::string &Name) : Name(Name) {}
	llvm::Value* codegen(Scope* s) override {
           //llvm::AllocaInst* var = NamedValues[Name];
	   auto var = s->getID(Name);
	   // todo: better error handling later 
	   if (!var){
	    std::cout << "No such variable " << Name << " in the current scope\n";	   
	   }
	   return Builder->CreateLoad(var->getAllocatedType(), var, Name.c_str());
	}
	// todo: look into sym table 
	std::string getType() override {return "int";}
    };


    // x = 5, x must be declared previously with stmt like int x;
    class VariableAssignExprAST: public StatementAST {
       std::string Name;
       // just int for now.
       ExprAST* RHS;
       public:
        VariableAssignExprAST(std::string Name, ExprAST* val):
	    Name(Name), RHS(val){}
	llvm::Value* codegen(Scope* s) override {
              // todo:  check if the variable exists
	      auto varInst = s->getID(Name);
	      if (!varInst){
		std::cout << "No such variable " << Name << " initialized in the current scope\n";      
	      }
	      llvm::Value* val = RHS->codegen(s);
	      //llvm::AllocaInst* var = NamedValues[Name];
	      return Builder->CreateStore(val, varInst);
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
	std::string getType() override{ return "int";}
        llvm::Value* codegen(Scope* s) override{
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
    };

    class ReturnStmtAST: public StatementAST {
	ExprAST* expr;
	public: 
	   ReturnStmtAST(ExprAST* expr): expr(expr){}
	   llvm::Value* codegen(Scope* s) override{
	      auto retVal = expr->codegen(s); 
	      Builder->CreateRet(retVal);
	      return nullptr;
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

        const std::string getName() const { return Name; }
        const std::string getReturnType() const {return RetType;}
        int getArgSize(){return Args.size();}
        llvm::Function* codegen(Scope* s) override{
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
            //unsigned Idx = 0;
            //for (auto &Arg : F->args())
             //   Arg.setName(Args[Idx++]);

            return F;
        }

    };

// FunctionAST - This class represents a function definition itself.
    class FunctionAST: public StatementAST {
        PrototypeAST* Proto;
        std::vector<STAB::VariableDeclExprAST*> declVars;
	std::vector<StatementAST*> Body;
    public:
        FunctionAST(PrototypeAST* Proto,
		    std::vector<STAB::VariableDeclExprAST*> declVars,
                    std::vector<StatementAST*> Body)
                : Proto(Proto), declVars(std::move(declVars)), Body(std::move(Body)) {}
	// did this just for my code to compile
	// todo: add the actual implementation
	llvm::Function* codegen(Scope* s) override{
	  std::vector<llvm::Type*> params(Proto->getArgSize(), llvm::Type::getInt32Ty(*TheContext));
	  llvm::FunctionType* FT;
	  if (Proto->getReturnType() == "void") {
	       FT = llvm::FunctionType::get(llvm::Type::getVoidTy(*TheContext), params, false);	    
	    }else {
               FT =  llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext), params, false);
            }
            
          llvm::Function* F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, Proto->getName(), TheModule.get());	
	  s->setFnBlock(F);
	  llvm::BasicBlock* fnBlock = llvm::BasicBlock::Create(*TheContext, Proto->getName(), F);
	  Builder->SetInsertPoint(fnBlock);
	  
          for(const auto params: declVars){
	     params->codegen(s);	  
	  }
	  for(const auto body: Body){
             body->codegen(s);		  
	  }
	  // Check for proper termination
          bool hasReturn = false;
          for (auto &BB : *F) {
            if (BB.getTerminator()) {
                if (llvm::isa<llvm::ReturnInst>(BB.getTerminator()) && Proto->getReturnType() == "void") {
		   std::cerr << "\nError: Void Function cannot have a return statement\n";
		   return nullptr;
                } else {
		  hasReturn = true;	
		}
            } else {
                Builder->SetInsertPoint(&BB);
                if (Proto->getReturnType() == "void") {
                    Builder->CreateRetVoid();
                } 
              }
          }

        // If no return statement was found and the function is non-void, this is an error.
        if (!hasReturn && Proto->getReturnType() != "void") {
            std::cerr << "\nError: Non-void function does not have a return statement\n";
            return nullptr;
        }

	  llvm::verifyFunction(*F);
	  // just to check the generated IR
	  // todo: Change to actual thing that will be returned
	  return F;
	}
    };
}
#endif //STAB_AST_H

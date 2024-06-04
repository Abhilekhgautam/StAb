//
// Created by abhilekh on 5/11/24.
//
#pragma once

#include <fstream>
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
#include <llvm-18/llvm/IR/GlobalValue.h>
#include <llvm-18/llvm/IR/CallingConv.h>

#ifndef STAB_GLOBAL_H
#include "../globals.h"
#endif

#include "../includes/scope.hpp"

namespace STAB{
    class ExprAST{
    public:
        virtual ~ExprAST() = default;
        virtual llvm::Value* codegen(STAB::Scope* s) = 0;
        virtual std::string getType() = 0;
    };

    class StatementAST {
    public:
        virtual ~StatementAST() = default;
        virtual llvm::Value* codegen(STAB::Scope* s) = 0;
    };

    class NumberExprAST: public ExprAST{
        int val;
    public:
        NumberExprAST(int val):val(val){}
        llvm::Value* codegen(STAB::Scope* s) override;
        // just for now
        std::string getType() override{return "int";}
	int getVal(){return val;}
    };

    class StringExprAST: public ExprAST{
	std::string val;
    public:
        StringExprAST(std::string val):val(val){}
        llvm::Value* codegen(STAB::Scope* s) override;
        // just for now
        std::string getType() override{return "string";}
	std::string getVal() {return val;}
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
       llvm::Value* codegen(STAB::Scope* s) override;
    };

    // int x = 5;
    class VariableDeclAssignExprAST: public StatementAST {
	VariableDeclExprAST* varDecl;
	// type is int for now
	ExprAST* val;

	public:
	   VariableDeclAssignExprAST(VariableDeclExprAST* varDecl, ExprAST* val):
		   varDecl(varDecl), val(val){}
           llvm::Value* codegen(STAB::Scope* s) override;
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
	 llvm::Value* codegen(STAB::Scope* s) override;
    };

    /// A class for infinite loop
    /// loop {}
    class LoopStatementAST: public StatementAST{
	    std::vector<StatementAST*> body;
       public:
          LoopStatementAST(std::vector<StatementAST*> body): body(std::move(body)){}
	  llvm::Value* codegen(STAB::Scope* s) override;
    };

    class CondStatementAST: public StatementAST {
       ExprAST* condExpr;
       std::vector<StatementAST*> body; 	    

       public:
         CondStatementAST(ExprAST* cond, std::vector<StatementAST*> body): condExpr(cond), body(std::move(body)){}
	 ExprAST* getCond(){return condExpr;};
	 llvm::Value* codegen(Scope* s) override;
    };

    class ElseStatementAST: public StatementAST {
        std::vector<StatementAST*> elseBody;
	public:
	  ElseStatementAST(std::vector<StatementAST*> body): elseBody(std::move(body)){}
	  llvm::Value* codegen(Scope* s) override;
    };

    // Represents if else ladder
    class IfStatementAST: public StatementAST {
       CondStatementAST* ifStmt;
       CondStatementAST* elseifStmt;
       ElseStatementAST* elseStmt;
    public:
       IfStatementAST(CondStatementAST* ifStmt,CondStatementAST* elseifStmt, ElseStatementAST* elseStmt):
	       ifStmt(ifStmt), elseifStmt(elseifStmt), elseStmt(elseStmt){}
       llvm::Value* codegen(Scope* s) override;
    };

    class RangeStatementAST{
	ExprAST* start;
	ExprAST* end;
	ExprAST* step;
      public:
	RangeStatementAST(ExprAST* start, ExprAST* end, ExprAST* step = new NumberExprAST(1)):
		start(start), end(end), step(step){}
	ExprAST* getStart(){return start;}
	ExprAST* getEnd(){return end;}
	ExprAST* getStep(){return step;}
    };

    class ForStatementAST: public StatementAST {
	 VariableDeclExprAST* iterationVariable;
	 RangeStatementAST* range;
         std::vector<StatementAST*> body;
     public:
	 ForStatementAST(VariableDeclExprAST* var, RangeStatementAST* range, std::vector<StatementAST*> body):
		 iterationVariable(var), range(range), body(body){}
	 llvm::Value* codegen(Scope* s) override;
    };

    // Represents referencing of variables..
    class VariableExprAST : public ExprAST {
      std::string Name;

      public:
        VariableExprAST(const std::string &Name) : Name(Name) {}
	llvm::Value* codegen(Scope* s) override;
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
        llvm::Value* codegen(STAB::Scope* s) override;
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
    llvm::Value* codegen(Scope* s) override;

    };

    // Statements like, return a;
    class ReturnStmtAST: public StatementAST {
	ExprAST* expr;
	public:
	   ReturnStmtAST(ExprAST* expr): expr(expr){}
	   llvm::Value* codegen(Scope* s) override;
    };

// CallExprAST - Expression class for function calls.
    class CallExprAST : public ExprAST {
        std::string Callee;
        std::vector<ExprAST*> Args;

    public:
        CallExprAST(const std::string &Callee,
                    std::vector<ExprAST*> Args)
                : Callee(Callee), Args(std::move(Args)) {}
	    std::string getFnName() const {return Callee;}
	    std::vector<ExprAST*> getArgs(){return Args;}
        llvm::Value* codegen(Scope* s) override;
	    std::string getType() override {return "";}
    };

    class CallStatementAST : public StatementAST {
	 std::string Callee;
        std::vector<ExprAST*> Args;

    public:
        CallStatementAST(const std::string &Callee,
                    std::vector<ExprAST*> Args)
                : Callee(Callee), Args(std::move(Args)) {}
	std::string getFnName() const {return Callee;}
	std::vector<ExprAST*> getArgs(){return Args;}
        llvm::Value* codegen(Scope* s) override;
    
    };

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
        llvm::Function* codegen(Scope* s) override;
    };

// FunctionAST - This class represents a function definition itself.
    class FunctionAST: public StatementAST{
        std::vector<STAB::VariableDeclExprAST*> declVars;
	    std::vector<StatementAST*> Body;
	    STAB::Scope* Scope;
    public:
        PrototypeAST* Proto;
        FunctionAST(PrototypeAST* Proto,
		    std::vector<STAB::VariableDeclExprAST*> declVars,
                    std::vector<StatementAST*> Body, STAB::Scope* s)
                  :declVars(std::move(declVars)), Body(std::move(Body)),Scope(s),Proto(Proto){}
	     std::vector<StatementAST*>& getBody(){return Body;}

	     llvm::Function* codegen(class Scope* s) override;
    };
}
#endif //STAB_AST_H

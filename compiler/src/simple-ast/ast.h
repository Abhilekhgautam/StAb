//
// Created by abhilekh on 5/11/24.
//
#pragma once

#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <llvm-18/llvm/Support/Casting.h>
#include <stdexcept>
#ifndef STAB_AST_H
#define STAB_AST_H

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <llvm/ADT/APInt.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Metadata.h>
#include <llvm/IR/Value.h>

#ifndef STAB_GLOBAL_H
#include "../globals.h"
#endif

#include "../includes/scope.hpp"
#ifndef HIGHLIGHT_TERM_
#include "../includes/highlight-term.hpp"
#endif
#ifndef STAB_LOCATION_H
#include "../includes/location.hpp"
#endif

namespace STAB {
class ExprAST {
public:
  virtual ~ExprAST() = default;
  virtual llvm::Value *codegen(STAB::Scope *s) = 0;
  virtual std::string getType() = 0;
};

class StatementAST {
public:
  virtual ~StatementAST() = default;
  virtual llvm::Value *codegen(STAB::Scope *s) = 0;
};

class BreakStatementAST : public StatementAST {
    public:
       BreakStatementAST(STAB::location loc):loc(loc){}
       virtual llvm::Value *codegen(STAB::Scope *s) override;
    private:
       STAB::location loc;
};

class SkipStatementAST : public StatementAST {
    public:
       SkipStatementAST(STAB::location loc):loc(loc){};
       virtual llvm::Value* codegen(STAB::Scope* s) override;
    private:
       STAB::location loc;
};

class NumberExprAST : public ExprAST {
public:
  NumberExprAST(std::string val, STAB::location loc) : str_val(val), loc(loc) {
      try{
          val = std::stoi(str_val);
      } catch(std::out_of_range& exp){
          color("red", "Error ");
          color("blue", "Number ");
          color("white", str_val);
          color("blue", " not within 32-bit integer range", true);
          std::exit(0);
      }
  }
  llvm::Value *codegen(STAB::Scope *s) override;
  // just for now
  std::string getType() override { return "int"; }
  int getVal() { return val; }
 private:
  std::string str_val;
  int val;
  STAB::location loc;
};

class StringExprAST : public ExprAST {
  std::string val;

public:
  StringExprAST(std::string val, STAB::location loc) : val(val), loc(loc) {}
  llvm::Value *codegen(STAB::Scope *s) override;
  // just for now
  std::string getType() override { return "string"; }
  std::string getVal() { return val; }

  private:
    STAB::location loc;
};

class ArrayAST : public StatementAST {
  std::string type;
  std::string name;
  ExprAST *size;

public:
  ArrayAST(std::string type, std::string name, ExprAST *size, STAB::location loc)
      : type(type), name(name), size(size), loc(loc) {}
  std::string getType() const { return type; }
  std::string getName() const { return name; }
  llvm::Value *codegen(STAB::Scope *s) override;
  private:
    STAB::location loc;
};

class ArrayAssignAST : public StatementAST {
  std::string name;
  ExprAST *index;
  ExprAST *val;

public:
  ArrayAssignAST(std::string name, ExprAST *index, ExprAST *val, STAB::location loc)
      : name(name), index(index), val(val), loc(loc) {}
  llvm::Value *codegen(Scope *s) override;
  private:
   STAB::location loc;
};

class ArrayRefAST : public ExprAST {
  std::string name;
  ExprAST *expr;

public:
  ArrayRefAST(std::string name, ExprAST *expr, STAB::location loc) : name(name), expr(expr), loc(loc) {}
  llvm::Value *codegen(Scope *s) override;
  // only int for now.
  std::string getType() override { return "int"; }
  private:
    STAB::location loc;
};
// int x;
class VariableDeclExprAST : public StatementAST {

public:
  VariableDeclExprAST(std::string &Type, std::string &Name, STAB::location loc)
      : Type(Type), Name(Name), loc(loc) {}
  std::string getType() const { return Type; }
  std::string getName() const { return Name; }
  llvm::Value *codegen(STAB::Scope *s) override;
  private:
    std::string Type;
    std::string Name;
    STAB::location loc;
};

// int x = 5;
class VariableDeclAssignExprAST : public StatementAST {
  VariableDeclExprAST *varDecl;
  // type is int for now
  ExprAST *val;
  STAB::location loc;
public:
  VariableDeclAssignExprAST(VariableDeclExprAST *varDecl, ExprAST *val, STAB::location loc)
      : varDecl(varDecl), val(val), loc(loc) {}
  llvm::Value *codegen(STAB::Scope *s) override;
};
// while loop
// while cond {
//
// }
class WhileStatementAST : public StatementAST {
  ExprAST *expr;
  std::vector<StatementAST *> body;

  STAB::location loc;
public:
  WhileStatementAST(ExprAST *expr, std::vector<StatementAST *> body, STAB::location loc)
      : expr(expr), body(std::move(body)), loc(loc) {}
  llvm::Value *codegen(STAB::Scope *s) override;
};

/// A class for infinite loop
/// loop {}
class LoopStatementAST : public StatementAST {
  std::vector<StatementAST *> body;
  STAB::location loc;
public:
  LoopStatementAST(std::vector<StatementAST *> body, STAB::location loc)
    : body(std::move(body)),loc(loc) {}
  llvm::Value *codegen(STAB::Scope *s) override;
};

class CondStatementAST : public StatementAST {
  ExprAST *condExpr;
  std::vector<StatementAST *> body;

  STAB::location loc;
public:
  CondStatementAST(ExprAST *cond, std::vector<StatementAST *> body, STAB::location loc)
      : condExpr(cond), body(std::move(body)), loc(loc) {}
  ExprAST *getCond() { return condExpr; };
  llvm::Value *codegen(Scope *s) override;
};

class ElseStatementAST : public StatementAST {
  std::vector<StatementAST *> elseBody;

  STAB::location loc;
public:
  ElseStatementAST(std::vector<StatementAST *> body, STAB::location loc)
      : elseBody(std::move(body)), loc(loc) {}
  llvm::Value *codegen(Scope *s) override;
};

// Represents if else ladder
class IfStatementAST : public StatementAST {
  CondStatementAST *ifStmt;
  CondStatementAST *elseifStmt;
  ElseStatementAST *elseStmt;

  STAB::location loc;
public:
  IfStatementAST(CondStatementAST *ifStmt, CondStatementAST *elseifStmt,
                 ElseStatementAST *elseStmt, STAB::location loc)
      : ifStmt(ifStmt), elseifStmt(elseifStmt), elseStmt(elseStmt), loc(loc) {}
  llvm::Value *codegen(Scope *s) override;
};

class RangeStatementAST {
  ExprAST *start;
  ExprAST *end;
  ExprAST *step;

  STAB::location loc;
public:
  RangeStatementAST(ExprAST *start, ExprAST *end,
                    ExprAST *step = nullptr, STAB::location loc ={0, 0})
      : start(start), end(end), step(step), loc(loc) {
          step = new NumberExprAST("1", loc);

      }
  ExprAST *getStart() { return start; }
  ExprAST *getEnd() { return end; }
  ExprAST *getStep() { return step; }
};

class ForStatementAST : public StatementAST {
  VariableDeclExprAST *iterationVariable;
  RangeStatementAST *range;
  std::vector<StatementAST *> body;
  STAB::location loc;
public:
  ForStatementAST(VariableDeclExprAST *var, RangeStatementAST *range,
                  std::vector<StatementAST *> body, STAB::location loc)
      : iterationVariable(var), range(range), body(body), loc(loc) {}
  llvm::Value *codegen(Scope *s) override;
};

// Represents referencing of variables..
class VariableExprAST : public ExprAST {
  std::string Name;

  STAB::location loc;
public:
  VariableExprAST(const std::string &Name, STAB::location loc) : Name(Name), loc(loc) {}
  llvm::Value *codegen(Scope *s) override;
  // todo: look into sym table
  std::string getName() { return Name; }
  std::string getType() override { return "int"; }
};

// x = 5, x must be declared previously with stmt like int x;
class VariableAssignExprAST : public StatementAST {
  std::string Name;
  // just int for now.
  ExprAST *RHS;

  STAB::location loc;
public:
  VariableAssignExprAST(std::string Name, ExprAST *val, STAB::location loc)
      : Name(Name), RHS(val), loc(loc) {}
  llvm::Value *codegen(STAB::Scope *s) override;
};
// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST {
  // char would have worked but
  // kinda hard to integrate with YACC
  std::string Op;
  ExprAST *LHS;
  ExprAST *RHS;

  STAB::location loc;
public:
  BinaryExprAST(std::string Op, ExprAST *LHS, ExprAST *RHS, STAB::location loc)
      : Op(Op), LHS(LHS), RHS(RHS), loc(loc) {}
  ~BinaryExprAST() {
    delete LHS;
    delete RHS;
  }
  std::string getType() override { return "int"; }
  llvm::Value *codegen(Scope *s) override;
};

// Statements like, return a;
class ReturnStmtAST : public StatementAST {
  ExprAST *expr;

  STAB::location loc;
public:
  ReturnStmtAST(ExprAST *expr, STAB::location loc) : expr(expr), loc(loc) {}
  llvm::Value *codegen(Scope *s) override;
};

// CallExprAST - Expression class for function calls.
class CallExprAST : public ExprAST {
  std::string Callee;
  std::vector<ExprAST *> Args;

  STAB::location loc;
public:
  CallExprAST(const std::string &Callee, std::vector<ExprAST *> Args, STAB::location loc)
      : Callee(Callee), Args(std::move(Args)), loc(loc) {}
  std::string getFnName() const { return Callee; }
  std::vector<ExprAST *> getArgs() { return Args; }
  llvm::Value *codegen(Scope *s) override;
  std::string getType() override { return "fn"; }
};

class CallStatementAST : public StatementAST {
  std::string Callee;
  std::vector<ExprAST *> Args;

  STAB::location loc;
public:
  CallStatementAST(const std::string &Callee, std::vector<ExprAST *> Args, STAB::location loc)
      : Callee(Callee), Args(std::move(Args)), loc(loc) {}
  std::string getFnName() const { return Callee; }
  std::vector<ExprAST *> getArgs() { return Args; }
  llvm::Value *codegen(Scope *s) override;
};

// PrototypeAST - This class represents the "prototype" for a function,
// which captures its name, and its argument names (thus implicitly the number
// of arguments the function takes).
class PrototypeAST : public StatementAST {
  std::string RetType;
  std::string Name;
  std::vector<std::string> Args;

  STAB::location loc;
public:
  PrototypeAST(const std::string &RetType, const std::string &Name,
               std::vector<std::string> Args, STAB::location loc)
      : RetType(RetType), Name(Name), Args(std::move(Args)), loc(loc) {}

  const std::string getName() const { return Name; }
  const std::string getReturnType() const { return RetType; }
  int getArgSize() { return Args.size(); }
  llvm::Function *codegen(Scope *s) override;
};

// FunctionAST - This class represents a function definition itself.
class FunctionAST : public StatementAST {
  std::vector<STAB::VariableDeclExprAST *> declVars;
  std::vector<StatementAST *> Body;
  STAB::Scope *Scope;

  STAB::location loc;
public:
  PrototypeAST *Proto;
  FunctionAST(PrototypeAST *Proto,
              std::vector<STAB::VariableDeclExprAST *> declVars,
              std::vector<StatementAST *> Body, STAB::Scope *s, STAB::location loc)
      : declVars(std::move(declVars)), Body(std::move(Body)), Scope(s),
        loc(loc), Proto(Proto){}
  std::vector<StatementAST *> &getBody() { return Body; }

  llvm::Function *codegen(class Scope *s) override;
};
} // namespace STAB
#endif // STAB_AST_H

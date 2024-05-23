#pragma once

#ifndef STAB_SCOPE_H
#define STAB_SCOPE_H

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <map>

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include <llvm/IR/Function.h>

#ifndef STAB_GLOBAL_H
#include "../globals.h"
#endif

namespace STAB{

class Scope {
   std::map<std::string, llvm::AllocaInst*> SymbolTable;
   std::string name;
   llvm::Function* F;
  public: 
   Scope(Scope* e = nullptr, std::string name = ""):name(name), prev(e){}

   void setFnBlock(llvm::Function* Fn){
      F = Fn;	   
   }

   void createFnBlock(){
      F = Builder->GetInsertBlock()->getParent(); 
   }

   llvm::Function* getFnBlock(){return F;}
   std::string getName() const {return name;}
   // points to its parent scope, 
   // for nested scope
   Scope* prev;
   // install variable name to the idTable
   void installID(std::string key, llvm::AllocaInst*  value){
	SymbolTable.insert({key, value});
   }

   // check if a variable name already exists within the current scope
   llvm::AllocaInst* getID(std::string id) const{
     auto found = SymbolTable.find(id);
     if (found != SymbolTable.end()){
	return found->second;     
     }
     return nullptr;

   }

 };
}
#endif

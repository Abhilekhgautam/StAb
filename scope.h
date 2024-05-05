#ifndef SCOPE_H
#define SCOPE_H

#include <iostream>
#include <vector>
#include "AST.h"
class Scope {
  public: 
   // no need for data hiding
   Scope(Scope* e = nullptr){
     symbolTable = {}; 
     prev = e;
   }
   std::vector<ExprAST*> symbolTable;
   // points to its parent scope, 
   // for nested scope
   Scope* prev;
   /*
   friend std::ostream& operator << (std::ostream& out, Scope* e){
    while(e != nullptr){
      for(auto elt: e->symbolTable){
        out << elt << " "; 
      }
      e = e->prev;
    }
    return out;
   }
   */
 };

#endif

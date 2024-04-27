#ifndef SCOPE_H
#define SCOPE_H

#include <iostream>
#include <string>
#include <vector>
class Scope {
  public: 
   // no need for data hiding
   Scope(Scope* e = nullptr){
     symbolTable = {}; 
     numberTable = {};
     prev = e;
   }
   std::vector<std::string> symbolTable;
   std::vector<std::string> numberTable;
   // points to its parent scope, 
   // for nested scope
   Scope* prev;

   friend std::ostream& operator << (std::ostream& out, Scope* e){
    while(e != nullptr){
      for(auto elt: e->symbolTable){
        out << elt << " "; 
      }
      for(auto elt: e->numberTable){
        out << elt << " "; 
      }
      e = e->prev;
    }
    return out;
   }
 };

#endif

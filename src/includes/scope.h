#ifndef SCOPE_H
#define SCOPE_H

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <map>

struct FnTable{
  std::string fnName;
  std::string retType;
  // key: variable, value: type
  std::map<std::string, std::string> args;

  std::string getFnName(){ return fnName;}
  std::string getretType(){return retType;}
  const std::map<std::string, std::string>& getArgs() const{
   return args;
  }
};

class Scope {
  public: 
   // no need for data hiding
   Scope(Scope* e = nullptr){
     IdTable = {}; 
     fnTable = {};
     prev = e;
   }
   std::map<std::string, std::string> IdTable;
   std::vector<FnTable> fnTable;
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
   // install variable name to the idTable
   void installID(std::string key, std::string value){
      IdTable.emplace(std::make_pair(key, value));
   }

   // check if a variable name already exists within the current scope
   bool idExists(std::string id) const{
     return !(IdTable.find(id) == IdTable.end());
   }

   // install function to the funciton Table
   void installFn(std::string name, std::string type, std::map<std::string, std::string> args){
    FnTable newEntry = {
	 name,
	 type,
	 args
    };
    fnTable.emplace_back(newEntry);
   }

   // check if a function with similar signature already exists or not
   bool FnExists(std::string id) const{
     for (const auto& elt: fnTable){
	if(elt.fnName == id) return true;     
     } 
     return false;
   }


 };

#endif

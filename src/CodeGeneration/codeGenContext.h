//
// Created by abhilekh on 5/8/24.
//
#ifndef STAB_CODEGENCONTEXT_H
#define STAB_CODEGENCONTEXT_H


#include "llvm/IR/Module.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/ExecutionEngine/GenericValue.h"

#include <map>
#include <list>
#include <ostream>

#include "../AST/AST.h"

namespace STAB {
    enum ScopeType {
        Func,
        Global
    };
    // mapping of a variable name to its corresponding AllocaInst*
    using VariableAllocateMap = std::map<std::string, llvm::AllocaInst*>;
    // mapping of a variable name to its type
    using VariableTypeMap = std::map<std::string, std::string>;
    // context of a scope block
    class codeGenBlock {
    public:
        //ctor
        codeGenBlock(llvm::BasicBlock* b): basicBlock(b){}
        ~codeGenBlock() = default;
        // getters
        llvm::BasicBlock* getCurrentBlock() {return basicBlock;}
        VariableTypeMap&  getVariableTypeMap(){return varTypes;}
        VariableAllocateMap& getVariableAllocationMap(){return localVars;}
    private:
        llvm::BasicBlock* basicBlock{nullptr};
        VariableAllocateMap localVars;
        VariableTypeMap varTypes;
    };
    // context of the current compilation process
    class codeGenContext {
    public:
        codeGenContext(std::ostream& out);
        ~codeGenContext() = default;

        llvm::Module* getModule(){return module;}
        llvm::LLVMContext* getLLVMContext(){return context;}

        // execute the AST Code
        llvm::GenericValue runCode();

        void createNewScope(llvm::BasicBlock* b, ScopeType scope_type);
        // end the current scope
        void endScope(llvm::BasicBlock);

        ScopeType getCurrentScopeType(){return currentScopeType;}

        void incrementError(){++numOfErrors;}

    private:
        // all the code blocks in the source code.
        std::list<codeGenBlock*> codeBlocks;
        codeGenBlock* currentBlock{nullptr};
        // LLVM's Symbol Table
        llvm::Module* module{nullptr};
        // LLVM"s context
        llvm::LLVMContext* context{nullptr};

        // number of errors obtained while code generation
        int numOfErrors{0};
        llvm::Type* intType{nullptr};
        // maps var type to llvm's type
        llvm::Function* mainFn{nullptr};

        std::map<std::string, llvm::Type> llvmTypeMap;
        ScopeType currentScopeType{ScopeType::Global};

        std::string getType(std::string name);
        // return type based on identifier
        llvm::Type* typeOf(const class Identifier& id);
        // return type based on name
        llvm::Type* typeOf(std::string name);
        // returns type of llvm
        std::string typeOfLLVM(llvm::Type*);
    private:
        struct BuildInfo{
            llvm::Function* fn{nullptr};
            // sorry: generics baby :)
            void* address{nullptr};
        };
        std::vector<BuildInfo> builtInfos;
        std::ostream& out;
    };
} //namespace STAB
#endif //STAB_CODEGENCONTEXT_H
//
// Created by abhilekh on 5/23/24.
//

#include "./ast.h"

namespace STAB{
    llvm::Value* STAB::VariableDeclAssignExprAST::codegen(Scope* s){
	if (s == globalScope){
            llvm::Constant* initializer = nullptr;
	    ExprAST* initValue = val;
	    llvm::IntegerType* type = nullptr;
             if(varDecl->getType() == "string"){
                 type = llvm::Type::getInt8Ty(*TheContext);
	     }
             else{ 
                 type = llvm::Type::getInt32Ty(*TheContext);
		 NumberExprAST* valToInt = dynamic_cast<NumberExprAST*>(initValue);
		 initializer = llvm::ConstantInt::get(type, valToInt->getVal());
	     }

              llvm::Module* module = Builder->GetInsertBlock()->getModule();
              llvm::GlobalVariable* value = new llvm::GlobalVariable(
                  *module, 
                  type, 
                  false, 
                  llvm::GlobalValue::ExternalLinkage, 
                  initializer, 
                  varDecl->getName()
              );
	      valType v = value;
	      s->installID(varDecl->getName(), v);
             return value;
	   	
         }
        auto generatedVal = varDecl->codegen(s);
        auto var = s->getID(varDecl->getName());
        //auto var = NamedValues[varDecl->getName()];
        auto va = val->codegen(s);

	if (auto allocaVar = std::get_if<llvm::AllocaInst*>(&var.value())) {
           return Builder->CreateStore(va, *allocaVar);
        }

      return nullptr;
	
    }
}

#include "ast.h"
#include "llvm/IR/DerivedTypes.h"

namespace STAB{
  llvm::Value* ArrayAST::codegen(STAB::Scope* s){
   llvm::IntegerType* type = nullptr;
       if(getType() == "string")
          type = llvm::Type::getInt8Ty(*TheContext);	  	
       else 
          type = llvm::Type::getInt32Ty(*TheContext);
 
	if (s == globalScope){
	    std::cerr << "\nGlobal Var " << name << " initialized\n";
	    llvm::Module* module = Builder->GetInsertBlock()->getModule();
            llvm::GlobalVariable* val = new llvm::GlobalVariable(
                *module, 
                type, 
                false, 
                llvm::GlobalValue::ExternalLinkage, 
                nullptr,
                name
            );
	    valType v = val;
	    s->installID(name, v);
            return val;
	}

	if(getType() == "string")
          type = llvm::Type::getInt8Ty(*TheContext);	  	
	else 
          type = llvm::Type::getInt32Ty(*TheContext);


	auto sizeVal = dynamic_cast<STAB::NumberExprAST*>(size);

	llvm::ArrayType* array = llvm::ArrayType::get(type, sizeVal->getVal());
	llvm::AllocaInst* allocArray = Builder->CreateAlloca(array, nullptr, "myArray");

	s->installID(name, allocArray);

	return allocArray;
  }
}

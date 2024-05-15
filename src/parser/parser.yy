%require "3.8"
%language "c++"

%code requires {
  #include "../includes/location.hpp"
  #include "../parser/parser.hpp"
  #ifndef STAB_AST_H
  #include "../simple-ast/ast.h"
  #endif
  namespace STAB{
    class Lexer;
  }
}

%define api.namespace {STAB}
%define api.parser.class {Parser}
%define api.value.type variant 
%define api.token.raw
%define api.location.type {location}

%locations
%define parse.error custom
%define parse.trace 

%header
%verbose 

%parse-param {Lexer& lexer}
%parse-param {const bool debug}

%initial-action{
  #if YYDEBUG != 0 
    set_debug_level(debug);
  #endif
};

%code {
  #include "../lexer/lexer.hpp"
  namespace STAB {
    template <typename RHS>
    void calcLocation(location& current, const RHS& rhs, const std::size_t n);
  }
  #define YYLLOC_DEFAULT(Cur, Rhs, N) calcLocation(Cur, Rhs, N)
  #define yylex lexer.yylex

}

%token MOD FN
%token LBRACE RBRACE LCURLY RCURLY LBIG RBIG ASSIGN
%token IF ELSE ELSE_IF LOOP FOR WHILE AND OR XOR MATCH
%token IMPORT IN CONTROL_FLOW COMMA FN_ARROW MATCH_ARROW
%token RETURN BREAK SKIP
%token SEMI_COLON
%token<std::string> PLUS MINUS TIMES DIV GT LT GE LE NE EQ "op"
%token<std::string> ID "identifier"
%token<std::string> DATA_TYPE "type"
%token<std::string> NUMBER "num"

%type<StatementAST*> stmt functionPrototype functionDefinition varDeclaration assignExpr while loop 
%type<std::vector<std::string>> paramList params
%type<STAB::VariableDeclAssignExprAST*> varInitialization
%type<ExprAST*> expr
%type<std::vector<ExprAST*>> argList args 
%type<std::vector<STAB::VariableDeclExprAST*>> paramListWithVar  paramsWithVar
%start stmt

%left PLUS MINUS
%left TIMES DIV
%left GT LT GE LE EQ NE
%%
 
 functionPrototype: FN ID LBRACE paramList RBRACE FN_ARROW DATA_TYPE SEMI_COLON {
                       std::vector<std::string> Args;
		       for(const auto elt: $4){
		         Args.emplace_back(elt);
		       }
                       $$ = new STAB::PrototypeAST($7, $2, Args);
                       auto FnIR = $$->codegen();
                       FnIR->print(llvm::errs());
                   }
                   | FN ID LBRACE paramList RBRACE SEMI_COLON{
                      std::vector<std::string> Args;
		      for (const auto elt: $4){
		        Args.emplace_back(elt);
		      }
                      $$ = new STAB::PrototypeAST("void", $2, Args);
                      auto FnIR = $$->codegen();
                      FnIR->print(llvm::errs());
                   }

 functionDefinition: FN ID LBRACE paramListWithVar RBRACE FN_ARROW DATA_TYPE LCURLY stmt RCURLY{
                        std::vector<std::string> argTypes;
			std::vector<STAB::VariableDeclExprAST*> declVars;
                        for(const auto elt: $4){
			  argTypes.emplace_back(elt->getType());
			  declVars.emplace_back(elt);
			}
			auto proto = new STAB::PrototypeAST($7, $2, argTypes);
			$$ = new STAB::FunctionAST(proto,declVars, $9);
			std::cout << "New Function Declared\n";
			auto FnIR = $$->codegen();
			FnIR->print(llvm::errs());

                    }
                    | FN ID LBRACE paramListWithVar RBRACE LCURLY stmt RCURLY  {
		        std::vector<std::string> argTypes;
                        std::vector<STAB::VariableDeclExprAST*> declVars;
                        for(const auto elt: $4){
			  argTypes.emplace_back(elt->getType());
			  declVars.emplace_back(elt);
			}
			auto proto = new STAB::PrototypeAST("void", $2, argTypes);
			$$ = new STAB::FunctionAST(proto, declVars,  $7);
			auto FnIR = $$->codegen();
			FnIR->print(llvm::errs());
                     } 

 varDeclaration: DATA_TYPE ID SEMI_COLON {
                  $$ = new STAB::VariableDeclExprAST($1, $2);
		  auto varDeclIR = $$->codegen();
		  varDeclIR->print(llvm::errs());
                } 

 varInitialization:DATA_TYPE ID ASSIGN fnCall SEMI_COLON {

		  }
		  | DATA_TYPE ID ASSIGN expr SEMI_COLON {
                     auto type = $1;
		     auto name = $2;
		     auto val = $4;
		     auto varDecl = new VariableDeclExprAST(type, name);
		     $$ = new VariableDeclAssignExprAST(varDecl, val);
		     auto varInitIR = $$->codegen();
		     varInitIR->print(llvm::errs());
		  }
                  ;

 loop: LOOP LCURLY stmt RCURLY{
       $$ = new LoopStatementAST($3);
       auto loopIR = $$->codegen();
       loopIR->print(llvm::errs());
     } 

 for : FOR ID IN ID LCURLY stmt RCURLY
 
 while: WHILE expr LCURLY stmt RCURLY{
         $$ = new WhileStatementAST($2, $4);
	 auto whileIR = $$->codegen();
	 whileIR->print(llvm::errs());
      } 

 stmt: %empty
      | functionDefinition stmt
      | loop stmt
      | for stmt
      | while stmt
      | ifStmt stmt
      | varDeclaration stmt
      | varInitialization stmt
      | assignExpr stmt
      | breakStmt stmt
      | skipStmt stmt
      | returnStmt stmt
      | functionPrototype stmt
      | fnCall stmt
      ;

 expr: expr PLUS expr {
        $$ = new BinaryExprAST($2, $1, $3);
        auto binExprIR = $$->codegen();
	binExprIR->print(llvm::errs());
      }
     | expr MINUS expr {
        $$ = new BinaryExprAST($2, $1, $3);
	auto binExprIR = $$->codegen();
	binExprIR->print(llvm::errs());
     }
     | expr TIMES expr {
        $$ = new BinaryExprAST($2, $1, $3);
     }
     | expr DIV expr {
        $$ = new BinaryExprAST($2, $1, $3);
     }
     | LBRACE expr RBRACE {
       $$ = $2; 
     }
     | expr GT expr {
       $$ = new BinaryExprAST($2, $1, $3);
     }
     | expr LT expr {
       $$ = new BinaryExprAST($2, $1, $3);
     }
     | expr LE expr {
     $$ = new BinaryExprAST($2, $1, $3);
     }
     | expr GE expr{
     $$ = new BinaryExprAST($2, $1, $3);
     }
     | expr EQ expr{
     $$ = new BinaryExprAST($2, $1, $3);
     }
     | expr NE expr{
     $$ = new BinaryExprAST($2, $1, $3);
     }
     | ID {
       $$ = new VariableExprAST($1);
       auto idIR = $$->codegen();
       idIR->print(llvm::errs());
     }
     | NUMBER {
        auto val = std::stoi($1);
        $$ = new NumberExprAST(val);
	auto numIR = $$->codegen();
	numIR->print(llvm::errs());
     }
     ;

 assignExpr: ID ASSIGN expr SEMI_COLON{
             $$ = new VariableAssignExprAST($1, $3);
	     auto genIR = $$->codegen();
	     genIR->print(llvm::errs());
           }
	   ;
  
 returnStmt: RETURN expr SEMI_COLON

 breakStmt: BREAK SEMI_COLON
 
 skipStmt: SKIP SEMI_COLON
 
 elseStmt: %empty
         | ELSE LCURLY stmt RCURLY
	 ;

 elseifStmt: %empty
           | ELSE_IF expr LCURLY stmt RCURLY elseifStmt;

 ifStmt: IF expr LCURLY stmt RCURLY elseifStmt elseStmt {
           std::cout << "A if stmt was parsed\n";
	 }

 paramList: %empty {
           }
          | params {
	     for (const auto elt: $1)
	         $$.emplace_back(elt);
	  }
	  ;
 
 params: params COMMA DATA_TYPE{
	 for(const auto elt: $1)
	    $$.emplace_back(elt);
	 $$.emplace_back($3);
       }
       | DATA_TYPE {
       $$.emplace_back($1);
       }
       ; 

paramListWithVar: %empty{

		}
		| paramsWithVar {
		  for (const auto elt: $1)
		      $$.emplace_back(elt);
		}
		;

paramsWithVar: paramsWithVar COMMA DATA_TYPE ID {
                for(const auto elt: $1)
		   $$.emplace_back(elt);
	     }
	     | DATA_TYPE ID {
	       auto newDecl = new STAB::VariableDeclExprAST($1, $2);
	       $$.emplace_back(newDecl);
	     }


 argList: %empty {
        } 
        | args {
	 for(const auto elt: $1){
	   $$.emplace_back(elt);
	 }
	} 
        ;

 args: args COMMA expr {
       for(const auto elt: $1)
           $$.emplace_back(elt);
       $$.emplace_back($3);
     }
     | expr {
       $$.emplace_back($1);
     }
     ;

 fnCall: ID LBRACE argList RBRACE{
   // todo: read argList into Args
   //std::vector<STAB::ExprAST*> Args;
   //$$ = new STAB::CallExprAST($1, Args);
 }

%%

namespace STAB {
 template <typename RHS>
 inline void calcLocation(location& current, const RHS& rhs, const std::size_t n){
 current = location(YYRHSLOC(rhs, 1).first, YYRHSLOC(rhs, n).second);
 }
 void Parser::report_syntax_error(const context& ctx) const {

  std::cerr << ctx.location() << ": Syntax Error Something went wrong"; 
 }
 void Parser::error(const location &loc, const std::string &message){
  std::cerr << "Error at lines " << loc << ": " << message << std::endl;
 }
}

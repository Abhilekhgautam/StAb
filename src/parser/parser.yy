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

%token NUMBER TIMES DIV MOD FN
%token LBRACE RBRACE LCURLY RCURLY LBIG RBIG ASSIGN
%token IF ELSE ELSE_IF LOOP FOR WHILE AND OR XOR MATCH
%token IMPORT IN CONTROL_FLOW COMMA FN_ARROW MATCH_ARROW
%token RETURN BREAK SKIP
%token SEMI_COLON
%token<std::string> PLUS MINUS GT LT GE LE NE EQ "op"
%token<std::string> ID "identifier"
%token<std::string> DATA_TYPE "type"

%type<STAB::PrototypeAST*> functionPrototype
%type<STAB::FunctionAST*> functionDefinition

%type<STAB::ExprAST*> expr
%type<STAB::ExprAST*> term
%type<STAB::ExprAST*> stmt

%start stmt

%left PLUS MINUS
%left TIMES DIV
%left GT LT GE LE EQ NE
%%
 
 functionPrototype: FN ID LBRACE paramList RBRACE FN_ARROW DATA_TYPE SEMI_COLON {
                       std::vector<std::string> Args;
                       auto prototype = new STAB::PrototypeAST($7, $2, Args);
                       llvm::Function* FnIR = prototype->codegen();
                       FnIR->print(llvm::errs());
                   }
                   | FN ID LBRACE paramList RBRACE SEMI_COLON{
                      std::vector<std::string> Args;
                      auto prototype = new STAB::PrototypeAST("void", $2, Args);
                      llvm::Function* FnIR = prototype->codegen();
                      FnIR->print(llvm::errs());
                   }

 functionDefinition: FN ID LBRACE paramList RBRACE FN_ARROW DATA_TYPE LCURLY stmt RCURLY{
                       std::vector<std::string> Args;
                       auto proto = new STAB::PrototypeAST($7, $2, Args);

                       $$ = new FunctionAST(proto, $9);
                    }
                    | FN ID LBRACE paramList RBRACE LCURLY stmt RCURLY  {
                       std::vector<std::string> Args;
                       auto proto = new STAB::PrototypeAST("void", $2, Args);

                       $$ = new FunctionAST(proto, $7);
                     } 

 varDeclaration: DATA_TYPE ID SEMI_COLON {
                  auto varDecl = new STAB::VariableDeclExprAST($1, $2);
		  auto varDeclIR = varDecl->codegen();
		  varDeclIR->print(llvm::errs());
                } 

 varInitialization:DATA_TYPE ID ASSIGN fnCall SEMI_COLON {

		  }
		  | DATA_TYPE ID ASSIGN expr SEMI_COLON {

		  }

 loop: LOOP LCURLY stmt RCURLY; 

 for : FOR ID IN ID LCURLY stmt RCURLY
 
 while: WHILE expr LCURLY stmt RCURLY 

 stmt: %empty
      | expr stmt
      | functionDefinition stmt
      | loop stmt
      | for stmt
      | while stmt
      | ifStmt stmt
      | varDeclaration stmt
      | varInitialization stmt
      | assignExpr stmt
      | breakExpr stmt
      | skipExpr stmt
      | returnExpr stmt
      | functionPrototype stmt
      | fnCall stmt
      ;

 expr: expr PLUS expr {
        $$ = new BinaryExprAST($2, $1, $3);
      }
     | expr MINUS expr {
        $$ = new BinaryExprAST($2, $1, $3);
     }
     | term
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
     ;

term: term TIMES factor
    | term DIV factor
    | factor
    ;

factor: LBRACE expr RBRACE
      | ID
      | NUMBER
      ;

 assignExpr: ID ASSIGN expr SEMI_COLON{
               
           }
	   | ID ASSIGN fnCall SEMI_COLON
	   ;
  
 returnExpr: RETURN expr SEMI_COLON

 breakExpr: BREAK SEMI_COLON
 
 skipExpr: SKIP SEMI_COLON
 
 elseStmt: %empty
         | ELSE LCURLY stmt RCURLY
	 ;

 elseifStmt: %empty
           | ELSE_IF expr LCURLY stmt RCURLY elseifStmt;

 ifStmt: IF expr LCURLY stmt RCURLY elseifStmt elseStmt {
           std::cout << "A if stmt was parsed\n";
	 }

 paramList: %empty 
          | params 
	  ;
 
 params: params COMMA parameter
       | parameter
       ; 

 parameter: DATA_TYPE ID;

 argList: %empty 
        | args 
        ;

 args: args COMMA expr
     | expr
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

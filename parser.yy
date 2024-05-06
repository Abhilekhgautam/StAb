%require "3.8"
%language "c++"

%code requires {
  #include "location.hpp"
  #include "parser.hpp"
  #include "AST.h"

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
  #include "lexer.hpp"
  #include "scope.h"
  namespace STAB {
    template <typename RHS>
    void calcLocation(location& current, const RHS& rhs, const std::size_t n);
  }
  #define YYLLOC_DEFAULT(Cur, Rhs, N) calcLocation(Cur, Rhs, N)
  #define yylex lexer.yylex

  // we need at least a scope at the beginning
  auto globalScope = new Scope();
  // global scope is the current scope initially
  auto currentScope = globalScope;
}

%token NUMBER PLUS MINUS TIMES DIV MOD FN
%token LBRACE RBRACE LCURLY RCURLY LBIG RBIG ASSIGN
%token GT LT GE LE EQ NE RELOP ARTHOP KEYWORD
%token IF ELSE ELSE_IF LOOP FOR WHILE AND OR XOR MATCH
%token IMPORT IN CONTROL_FLOW COMMA FN_ARROW MATCH_ARROW
%token RETURN BREAK SKIP
%token SEMI_COLON
%token<std::string> ID "identifier"
%token<std::string> DATA_TYPE "type"
%start stmt

%left PLUS MINUS
%left TIMES DIV
%left GT LT GE LE EQ NE
%%
 
 functionPrototype: FN ID LBRACE paramList RBRACE FN_ARROW DATA_TYPE SEMI_COLON{
                    if (currentScope != globalScope){
		      std::cout << "Error: A function can only be withing a global scope\n"; 
		    } else {
		      if (currentScope->FnExists($2)){
		        std::cout << "Error: The function " << $2 << " is already defined\n"; 
		      } else{
		       // todo: read args and add into the map.
		       std::map<std::string, std::string> dummy;
		       currentScope->installFn($2,$7, dummy);
                       std::cout << "Function Prototype of name: " << $2 << '\n';
		      }
		     }
                   }

 functionDefinition: FN ID LBRACE paramList RBRACE FN_ARROW DATA_TYPE LCURLY stmt RCURLY{
                      std::cout << "A function " << $2 << " was parsed with the return type " << $7 << '\n';
                    }
                   | FN ID LBRACE paramList RBRACE LCURLY stmt RCURLY  {
                      std::cout << "A function " << $2 << " was defined\n"; 
                     } 

 varDeclaration: DATA_TYPE ID SEMI_COLON {
                  if(currentScope->idExists($2)){
		    std::cerr << "Variable " << $2 << " redeclared here.."; 
		  } else {
		    
		    // variable is the key and type is the value
		    currentScope->installID($2, $1);
		    std::cout << "Variable " << $2 << " successfully added to the symbol table"; 
		  }
                } 

 varInitialization:DATA_TYPE ID ASSIGN fnCall SEMI_COLON {
                   if(currentScope->idExists($2)){
		    std::cerr << "Variable " << $2 << " redeclared here.."; 
		    } else {
		      // variable is the key and type is the value
		      currentScope->installID($2, $1);
		      std::cout << "Variable " << $2 << " successfully added to the symbol table"; 
		    }
		  }
		  | DATA_TYPE ID ASSIGN expr SEMI_COLON {
                   if(currentScope->idExists($2)){
		    std::cerr << "Variable " << $2 << " redeclared here.."; 
		    } else {
		      // variable is the key and type is the value
		      currentScope->installID($2, $1);
		      std::cout << "Variable " << $2 << " successfully added to the symbol table"; 
		    }

		  }

 loop: LOOP LCURLY stmt RCURLY; 

 for : FOR ID IN ID LCURLY stmt RCURLY
 
 while: WHILE expr LCURLY stmt RCURLY 

 stmt: %empty
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

 expr: expr PLUS term 
     | expr MINUS term 
     | term 
     | expr GT expr 
     | expr LT expr
     | expr LE expr
     | expr GE expr
     | expr EQ expr 
     | expr NE expr
     ;

term: term TIMES factor
    | term DIV factor
    | factor
    ;

factor: LBRACE expr RBRACE
      | ID
      | NUMBER
      ;

 assignExpr: ID ASSIGN expr SEMI_COLON
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
   if (!globalScope->FnExists($1)){
    std::cout << "Error: No such function " << $1 << " defined\n";
   }
   else {
    std::cout << "A function " << $1 << " was called with argument:\n";
   }
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

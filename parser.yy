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
  namespace STAB {
    template <typename RHS>
    void calcLocation(location& current, const RHS& rhs, const std::size_t n);
  }
  #define YYLLOC_DEFAULT(Cur, Rhs, N) calcLocation(Cur, Rhs, N)
  #define yylex lexer.yylex

}

%token NUMBER PLUS MINUS TIMES DIV MOD FN
%token LBRACE RBRACE LCURLY RCURLY LBIG RBIG ASSIGN
%token GT LT GE LE EQ NE RELOP ARTHOP KEYWORD
%token IF ELSE ELSE_IF LOOP FOR WHILE AND OR XOR MATCH
%token IMPORT IN CONTROL_FLOW COMMA FN_ARROW MATCH_ARROW
%token RETURN BREAK SKIP
%token<std::string> ID "identifier"
%token<std::string> DATA_TYPE "type"
%start stmt

%%
 
 functionPrototype: FN ID LBRACE paramList RBRACE FN_ARROW DATA_TYPE {
                    std::cout << "Function Prototype of name: " << $2 << '\n'; 
                   }

 functionDefinition: FN ID LBRACE paramList RBRACE FN_ARROW DATA_TYPE LCURLY stmt RCURLY{
                      std::cout << "A function " << $2 << " was parsed with the return type " << $7 << '\n';
                    }
                   | FN ID LBRACE paramList RBRACE LCURLY stmt RCURLY  {
                      std::cout << "A function definition was parsed\n"; 
                     } 

 varDeclaration: DATA_TYPE ID; 

 varInitialization: DATA_TYPE ID ASSIGN NUMBER;

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
      | fnCall stmt;

 expr: ID
     | arthExpr
     | relExpr
     | LBRACE expr RBRACE
     | NUMBER
     ;

 arthExpr: ID ARTHOP ID
         | ID ARTHOP NUMBER
	 | NUMBER ARTHOP ID 
	 | NUMBER ARTHOP NUMBER
	 ;
 relExpr: ID RELOP ID
        | ID RELOP NUMBER
	| NUMBER RELOP NUMBER 
	| NUMBER RELOP ID
	;

 assignExpr: ID ASSIGN arthExpr
	   | ID ASSIGN NUMBER
	   | ID ASSIGN fnCall
	   ;
  
 returnExpr: RETURN expr

 breakExpr: BREAK
 
 skipExpr: SKIP
 
 elseStmt: %empty
         | ELSE LCURLY stmt RCURLY;

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

 parameter: DATA_TYPE ID

 argList: %empty 
        | args 
        ;

 args: args COMMA expr
     | expr
     ;

 fnCall: ID LBRACE argList RBRACE{
   std::cout << "A function " << $1 << " was called with argument:";
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

%require "3.8"
%language "c++"

%code requires {
  #include "location.hpp"
  #include "lexer.hpp"
}

%define api.namespace {STAB}
%define api.parser.class {BisonParser}
%define api.value.type {std::string}
%define api.location.type {location}

%locations
%define parse.error detailed 
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
  namespace STAB {
    template <typename RHS>
    void calcLocation(location& current, const RHS& rhs, const std::size_t n);
  }
  #define YYLLOC_DEFAULT(Cur, Rhs, N) calcLocation(Cur, Rhs, N)
  #define yylex lexer.yylex
}

%token ID NUMBER PLUS MINUS TIMES DIV MOD FN
%token LBRACE RBRACE LCURLY RCURLY LBIG RBIG ASSIGN
%token GT LT GE LE EQ NE RELOP ARTHOP KEYWORD
%token IF ELSE ELSE_IF LOOP FOR WHILE AND OR XOR MATCH
%token DATA_TYPE IMPORT IN CONTROL_FLOW COMMA 

%start stmt

%%
 functionDefinition: FN ID LBRACE paramList RBRACE LCURLY stmt RCURLY {
                      std::cout << "A function definition was parsed\n"; 
                     } 

 varDeclaration: DATA_TYPE ID {
   std::cout << "A variable " << "was Declared\n"; 
 }

 varInitialization: DATA_TYPE ID ASSIGN NUMBER {
    std::cout << "A Variable was initialized";
 }

 loop: LOOP LCURLY stmt RCURLY {
   std::cout << "A loop statement was found\n";
 }

 for : FOR ID IN ID LCURLY stmt RCURLY{
    std::cout << "A for loop was detected\n"; 
 }

 stmt: %empty
      | functionDefinition stmt
      | loop stmt
      | for stmt
      | ifStmt stmt
      | varDeclaration stmt
      | varInitialization stmt
      | assignExpr stmt
      | fnCall stmt;

 expr: ID
     | arthExpr
     | relExpr
     | LBRACE expr RBRACE
 
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
        | args; 

 args: expr
     | args COMMA expr
     ;

 fnCall: ID LBRACE argList RBRACE{
   std::cout << "A function call was parsed\n";
 }

%%

namespace STAB {
 template <typename RHS>
 inline void calcLocation(location& current, const RHS& rhs, const std::size_t n){
 current = location(YYRHSLOC(rhs, 1).first, YYRHSLOC(rhs, n).second);
 }
 void BisonParser::error(const location &location, const std::string &message){
   std::cerr << "Error at lines " << location << ": " << message << '\n';
 }
}

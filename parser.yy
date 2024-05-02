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
%token DATA_TYPE IMPORT IN CONTROL_FLOW 

%start functionDefinition

%%
 functionDefinition: FN ID LBRACE RBRACE LCURLY stmt RCURLY {
                      std::cout << "a function definition was parsed\n"; 
                     } 

 varDeclaration: DATA_TYPE ID {
   std::cout << "A variable " << "was Declared\n"; 
 }

 varInitialization: DATA_TYPE ID ASSIGN NUMBER {
    std::cout << "A Variable was initialized";
 }

 loop: LOOP LCURLY stmt RCURLY {
   std::cout << "a loop statement was found\n";
 }

 for : FOR ID IN ID LCURLY stmt RCURLY{
    std::cout << "a for loop was detected\n"; 
 }

 stmt: %empty
      | loop stmt
      | for stmt
      | varDeclaration stmt
      | varInitialization stmt
      | assignExpr stmt;

 arthExpr: ID ARTHOP ID
         | ID ARTHOP NUMBER
	 | NUMBER ARTHOP ID 
	 | NUMBER ARTHOP NUMBER
	 ;
 assignExpr: ID ASSIGN arthExpr
	   | ID ASSIGN NUMBER
	   ;
%%

namespace STAB {
 template <typename RHS>
 inline void calcLocation(location& current, const RHS& rhs, const std::size_t n){
 current = location(YYRHSLOC(rhs, 1).first, YYRHSLOC(rhs, n).second);
 }
 void BisonParser::error(const location &location, const std::string &message){
   std::cerr << "Error at lines " << location << ": " << message << std::endl;
 }
}

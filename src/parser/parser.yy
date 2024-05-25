%require "3.8"
%language "c++"

%code requires {
  #include "../includes/location.hpp"
  #include "../parser/parser.hpp"
  #include "../includes/scope.hpp"
  #include "../globals.h"
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
  #include "../lexer/lexer.hpp"
  #include "../globals.h"
  namespace STAB {
    template <typename RHS>
    void calcLocation(location& current, const RHS& rhs, const std::size_t n);
  }
  #define YYLLOC_DEFAULT(Cur, Rhs, N) calcLocation(Cur, Rhs, N)
  #define yylex lexer.yylex
}

%token MOD
%token LBRACE RBRACE LCURLY RCURLY LBIG RBIG ASSIGN
%token IF ELSE ELSE_IF LOOP FOR WHILE AND OR XOR MATCH
%token IMPORT IN CONTROL_FLOW COMMA FN_ARROW MATCH_ARROW
%token RETURN BREAK SKIP
%token SEMI_COLON
%token<std::string> PLUS MINUS TIMES DIV GT LT GE LE NE EQ "op"
%token<std::string> ID "identifier"
%token<std::string> DATA_TYPE "type"
%token<std::string> NUMBER "num"

%type<std::vector<StatementAST*>> program stmts;
%type<StatementAST*> stmt functionPrototype functionDefinition varDeclaration assignExpr while loop returnStmt 
%type<std::vector<std::string>> paramList params
%type<STAB::VariableDeclAssignExprAST*> varInitialization
%type<ExprAST*> expr 
%type<CallExprAST*> fnCall
%type<std::vector<ExprAST*>> argList args 
%type<std::vector<STAB::VariableDeclExprAST*>>paramsWithVar


%left PLUS MINUS
%left TIMES DIV
%left GT LT GE LE EQ NE
%nonassoc FN DATA_TYPE 

%start program
%%
 
 functionDefinition: FN ID LBRACE paramsWithVar RBRACE FN_ARROW DATA_TYPE LCURLY stmts RCURLY{
			auto fnScope = new Scope(currentScope);
			currentScope = fnScope;
                        std::vector<std::string> argTypes;
			std::vector<STAB::VariableDeclExprAST*> declVars;
                        for(const auto elt: $4){
			  argTypes.emplace_back(elt->getType());
			  declVars.emplace_back(elt);
			}
			auto proto = new STAB::PrototypeAST($7, $2, argTypes);
			$$ = new STAB::FunctionAST(proto,declVars, $9, fnScope);
			currentScope = globalScope;
                    }

 functionPrototype: FN ID LBRACE paramList RBRACE FN_ARROW DATA_TYPE SEMI_COLON {
                       std::vector<std::string> Args;
		       for(const auto elt: $4){
		         Args.emplace_back(elt);
		       }
                       $$ = new STAB::PrototypeAST($7, $2, Args);
                   }


 varDeclaration: DATA_TYPE ID SEMI_COLON {
                  $$ = new STAB::VariableDeclExprAST($1, $2);
                } 

 varInitialization: DATA_TYPE ID ASSIGN expr SEMI_COLON {
                     auto type = $1;
		     auto name = $2;
		     auto val = $4;
		     auto varDecl = new VariableDeclExprAST(type, name);
		     $$ = new VariableDeclAssignExprAST(varDecl, val);
		  }
                  ;

 loop: LOOP LCURLY stmts RCURLY{
       $$ = new LoopStatementAST($3);

     }
     ;

 for : FOR ID IN ID LCURLY stmt RCURLY
 
 while: WHILE expr LCURLY stmts RCURLY{
         if (currentScope == globalScope){
           std::cerr << "\nCannot write a loop statement in the global scope\n"; 
         }
       $$ = new WhileStatementAST($2, $4);

      } 

program: stmts{
       globalScope = new Scope(nullptr);
       currentScope = globalScope;

       std::vector<std::string> Args;
       std::vector<STAB::VariableDeclExprAST*> declVars;
  
       std::vector<STAB::StatementAST*> stmts;

       auto proto = new PrototypeAST("void", "__start__", Args);

       $$ = $1;

       __start__fn = new FunctionAST(proto, declVars, stmts, globalScope);
      
       for (const auto stmt: $1)
           __start__fn->getBody().emplace_back(stmt);

       };
stmts: stmts stmt{
       $1.emplace_back($2);
       $$ = $1;
     }
     | %empty {
       $$ = std::vector<STAB::StatementAST*>();
     }
     ;

 stmt:
      functionDefinition{
        $$ = $1;
      }
      | loop{
        $$ = $1;
      }
      | for 
      | while {
         $$ = $1;
      }
      | ifStmt 
      | varDeclaration{
        $$ = $1;
      }
      | varInitialization{
         $$ = $1;
      }
      | assignExpr{
         $$ = $1;
      }
      | breakStmt
      | skipStmt
      | returnStmt{
          $$ = $1; 
      }
      | functionPrototype {
        $$ = $1;
      }
      ;

 expr: expr PLUS expr {
        $$ = new BinaryExprAST($2, $1, $3);
      }
     | expr MINUS expr {
        $$ = new BinaryExprAST($2, $1, $3);
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
     }
     | NUMBER {
        auto val = std::stoi($1);
        $$ = new NumberExprAST(val);
     }
     | fnCall {
        $$ = new CallExprAST($1->getFnName(), $1->getArgs());
     }
     ;

 assignExpr: ID ASSIGN expr SEMI_COLON %prec ASSIGN{
             $$ = new VariableAssignExprAST($1, $3);
           }
	   ;
  
 returnStmt: RETURN expr SEMI_COLON{
              $$ = new ReturnStmtAST($2);
           }
	   ;

 breakStmt: BREAK SEMI_COLON
 
 skipStmt: SKIP SEMI_COLON
 
 elseStmt: %empty
         | ELSE LCURLY stmt RCURLY
	 ;

 elseifStmt: %empty
           | ELSE_IF expr LCURLY stmt RCURLY elseifStmt;

 ifStmt: IF expr LCURLY stmt RCURLY elseifStmt elseStmt {
	 }

 paramList:
           params {
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

paramsWithVar: paramsWithVar COMMA DATA_TYPE ID {
                for(const auto elt: $1)
		   $$.emplace_back(elt);
	     }
	     | DATA_TYPE ID {
	       auto newDecl = new STAB::VariableDeclExprAST($1, $2);
	       $$.emplace_back(newDecl);
	     }
	     | %empty
	     ;


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
   std::vector<STAB::ExprAST*> Args;
   for (const auto elt: $3){
      Args.emplace_back(elt);
   }
   $$ = new CallExprAST($1, Args);
 }

%%

namespace STAB {
 template <typename RHS>
 inline void calcLocation(location& current, const RHS& rhs, const std::size_t n){
 current = location(YYRHSLOC(rhs, 1).first, YYRHSLOC(rhs, n).second);
 }
//void Parser::report_syntax_error(const context& ctx) const {
 // std::cerr << ctx.location() << ": Syntax Error Something went wrong"; 
 //}
 void Parser::error(const location &loc, const std::string &message){
  std::cerr << "Error at lines " << loc << ": " << message << std::endl;
  }
}

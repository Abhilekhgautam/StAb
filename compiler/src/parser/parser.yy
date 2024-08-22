%require "3.8"
%language "c++"

%code requires {
  #ifndef STAB_LOCATION_H
  #include "../includes/location.hpp"
  #endif
  #ifndef STAB_SCOPE_HPP
  #include "../includes/scope.hpp"
  #endif
  #ifndef STAB_GLOBAL_H
  #include "../globals.h"
  #endif
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
  #ifndef STAB_PARSER_H
  #define STAB_PARSER_H
  #ifndef STAB_LEXER_H
  #include "../lexer/lexer.hpp"
  #endif
  #ifndef STAB_GLOBAL_H
  #include "../globals.h"
  #endif
  #include "../includes/highlight-term.hpp"
  namespace STAB {
    template <typename RHS>
    void calcLocation(location& current, const RHS& rhs, const std::size_t n);
  }
  #define YYLLOC_DEFAULT(Cur, Rhs, N) calcLocation(Cur, Rhs, N)
  #define yylex lexer.yylex
  #endif
}

%token LBRACE RBRACE LCURLY RCURLY LBIG RBIG ASSIGN
%token IF ELSE ELSE_IF LOOP FOR WHILE AND OR XOR MATCH
%token IMPORT IN TO COMMA FN_ARROW MATCH_ARROW
%token RETURN BREAK SKIP
%token SEMI_COLON
%token<std::string> PLUS MOD MINUS TIMES DIV GT LT GE LE NE EQ "op"
%token<std::string> ID "identifier"
%token<std::string> DATA_TYPE "type"
%token<std::string> NUMBER "num"
%token<std::string> STRING "str"
%type<std::vector<StatementAST*>> program stmts;
%type<StatementAST*> stmt ifLadder functionPrototype functionDefinition varDeclaration assignExpr while for loop returnStmt breakStmt skipStmt fnCallStmt
%type<STAB::VariableDeclAssignExprAST*> varInitialization
%type<ExprAST*> expr
%type<CallExprAST*> fnCall
%type<std::vector<ExprAST*>> argList args
%type<std::vector<STAB::VariableDeclExprAST*>> paramList parameters
%type<std::vector<std::string>> paramListPrototype params

%type<STAB::ArrayAST*> arrayDecl;
%type<STAB::ArrayRefAST*> arrayRef;
%type<STAB::ArrayAssignAST*> arrayAssign;

%type<STAB::RangeStatementAST*> range;

%type<STAB::CondStatementAST*> ifStmt elseifStmt
%type<STAB::ElseStatementAST*> elseStmt

%left PLUS MINUS
%left TIMES DIV
%left MOD
%left GT LT GE LE
%left EQ NE
%nonassoc FN DATA_TYPE

%start program
%%

 functionDefinition: FN ID LBRACE paramList RBRACE FN_ARROW DATA_TYPE LCURLY stmts RCURLY{
			auto fnScope = new Scope(currentScope, "fn");
			currentScope = fnScope;
            std::vector<std::string> argTypes;
			std::vector<STAB::VariableDeclExprAST*> declVars;
            for(const auto elt: $4){
			  argTypes.emplace_back(elt->getType());
			  declVars.emplace_back(elt);
			}
			auto proto = new STAB::PrototypeAST($7, $2, argTypes, {@1.first, @10.second});
			$$ = new STAB::FunctionAST(proto,declVars, $9, fnScope, {@1.first, @10.second});
			currentScope = globalScope;
}

            | FN ID LBRACE paramList RBRACE LCURLY stmts RCURLY{
                auto fnScope = new Scope(currentScope, "fn");
			    currentScope = fnScope;
                std::vector<std::string> argTypes;
			    std::vector<STAB::VariableDeclExprAST*> declVars;
                for(const auto elt: $4){
			        argTypes.emplace_back(elt->getType());
			        declVars.emplace_back(elt);
			    }
			    auto proto = new STAB::PrototypeAST("void", $2, argTypes, {@1.first, @8.first});
			    $$ = new STAB::FunctionAST(proto,declVars, $7, fnScope, {@1.first, @8.first});
			    currentScope = globalScope;
}

 functionPrototype: FN ID LBRACE paramListPrototype RBRACE FN_ARROW DATA_TYPE SEMI_COLON {
                        std::vector<std::string> Args;
		                for(const auto elt: $4){
		                Args.emplace_back(elt);
		           }
                       $$ = new STAB::PrototypeAST($7, $2, Args, {@1.first, @8.first});
                   }


 varDeclaration: DATA_TYPE ID SEMI_COLON {
                  $$ = new STAB::VariableDeclExprAST($1, $2, {@1.first, @3.first});
                }

 varInitialization: DATA_TYPE ID ASSIGN expr SEMI_COLON {
                     auto type = $1;
		             auto name = $2;
		             auto val = $4;
		             auto varDecl = new VariableDeclExprAST(type, name, {@1.first, @5.first});
		             $$ = new VariableDeclAssignExprAST(varDecl, val, {@1.first, @5.first});
		           }
                  ;

 arrayDecl: DATA_TYPE ID LBIG expr RBIG SEMI_COLON{
              $$ = new ArrayAST($1, $2, $4, {@1.first,@6.first});
          }
	      ;

 arrayAssign: ID LBIG expr RBIG ASSIGN expr SEMI_COLON{
              $$ = new ArrayAssignAST($1, $3, $6, {@1.first, @7.first});
            }
	    ;

 arrayRef: ID LBIG expr RBIG {
           $$ = new ArrayRefAST($1, $3, {@1.first, @4.first});
         }
         ;

 loop: LOOP LCURLY stmts RCURLY{
       $$ = new LoopStatementAST($3, {@1.first, @2.first});

     }
     ;
 range: expr TO expr{
        $$ = new RangeStatementAST($1, $3, nullptr, {@1.first, @3.first});
      }
      ;

 for : FOR ID IN range LCURLY stmts RCURLY{
        std::string type = "int";
	    auto varDecl = new VariableDeclExprAST(type, $2, {@1.first, @5.first});
        $$ = new ForStatementAST(varDecl, $4, $6, {@1.first, @5.first});
     }
     ;

 while: WHILE expr LCURLY stmts RCURLY{
       $$ = new WhileStatementAST($2, $4, {@1.first, @3.first});

      }

program: stmts{
       std::vector<std::string> Args;
       std::vector<STAB::VariableDeclExprAST*> declVars;

       std::vector<STAB::StatementAST*> stmts;

       auto proto = new PrototypeAST("void", "__start__", Args, {0, 0});

       $$ = $1;

       __start__fn = new FunctionAST(proto, declVars, stmts, globalScope, {0,0});

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
      | for{
        $$ = $1;
      }
      | while {
         $$ = $1;
      }
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
      | fnCallStmt {
         $$ = $1;
      }
      | ifLadder{
         $$ = $1;
      }
      | arrayDecl {
         $$ = $1;
      }
      | arrayAssign {
         $$ = $1;
      }
      ;

 expr: expr PLUS expr {
        $$ = new BinaryExprAST($2, $1, $3, {@1.first, @3.first});
      }
     | expr MINUS expr {
        $$ = new BinaryExprAST($2, $1, $3, {@1.first, @3.first});
     }
     | expr TIMES expr {
        $$ = new BinaryExprAST($2, $1, $3, {@1.first, @3.first});
     }
     | expr DIV expr {
        $$ = new BinaryExprAST($2, $1, $3, {@1.first, @3.first});
     }
     | expr MOD expr {
        $$ = new BinaryExprAST($2, $1, $3, {@1.first, @3.first});
     }
     | LBRACE expr RBRACE {
        $$ = $2;
     }
     | expr GT expr {
        $$ = new BinaryExprAST($2, $1, $3, {@1.first, @3.first});
     }
     | expr LT expr {
        $$ = new BinaryExprAST($2, $1, $3, {@1.first, @3.first});
     }
     | expr LE expr {
        $$ = new BinaryExprAST($2, $1, $3, {@1.first, @3.first});
     }
     | expr GE expr{
        $$ = new BinaryExprAST($2, $1, $3, {@1.first, @3.first});
     }
     | expr EQ expr{
       $$ = new BinaryExprAST($2, $1, $3, {@1.first, @3.first});
     }
     | expr NE expr{
        $$ = new BinaryExprAST($2, $1, $3, {@1.first, @3.first});
     }
     | STRING {
        std::string val = $1;
	    auto length = val.length();
	    std::string without_quotation;
	    for(int i = 1; i < length - 1 ; ++i){
	        without_quotation += val[i];
	    }
	    $$ = new StringExprAST(without_quotation, {@1.first, 0});
     }
     | ID {
       $$ = new VariableExprAST($1, {@1.first, 0});
     }
     | NUMBER {
        $$ = new NumberExprAST($1, {@1.first, 0});
     }
     | fnCall {
        $$ = new CallExprAST($1->getFnName(), $1->getArgs(), {@1.first, 0});
     }
     | arrayRef {
        $$ = $1;
     }
     ;

 assignExpr: ID ASSIGN expr SEMI_COLON %prec ASSIGN{
             $$ = new VariableAssignExprAST($1, $3, {@1.first, @4.first});
           }
	   ;

 returnStmt: RETURN expr SEMI_COLON{
              $$ = new ReturnStmtAST($2, {@1.first, @2.first});
           }
	   ;

 breakStmt: BREAK SEMI_COLON {
         $$ = new BreakStatementAST({@1.first, 0});
       }

 skipStmt: SKIP SEMI_COLON {
          $$ = new SkipStatementAST({@1.first, 0});
       }

 elseStmt: %empty{
          $$ = nullptr;
         }
         | ELSE LCURLY stmts RCURLY{
	    $$ = new ElseStatementAST($3, {@1.first, @2.first});
	 }
	 ;

 elseifStmt: %empty
           | ELSE_IF expr LCURLY stmts RCURLY elseifStmt
	   {
	     $$ = nullptr;
	   };

 ifStmt: IF expr LCURLY stmts RCURLY {
	   $$ = new CondStatementAST($2, $4, {@1.first, @3.first});
	 }
	 ;
 ifLadder: ifStmt elseifStmt elseStmt{
            $$ = new IfStatementAST($1, nullptr, $3, {@1.first, @3.first});
         }
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
paramListPrototype:
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

paramList: %empty{
	 }
	 | parameters {
	   for(const auto elt: $1)
	     $$.emplace_back(elt);
	 }
	 ;

parameters: parameters COMMA DATA_TYPE ID {
	      for(const auto elt: $1){
	         $$.emplace_back(elt);
		  }
          auto decl = new VariableDeclExprAST($3, $4, {@3.first, @4.first});
	      $$.emplace_back(decl);
	  }
	  | DATA_TYPE ID {
	     auto decl = new VariableDeclExprAST($1, $2, {@1.first, @2.first});
	     $$.emplace_back(decl);
	  }

 fnCallStmt: ID LBRACE argList RBRACE SEMI_COLON{
     std::vector<STAB::ExprAST*> Args;
     for (const auto elt: $3){
         Args.emplace_back(elt);
       }
      $$ = new CallStatementAST($1, Args, {@1.first, @5.first});
    }

 fnCall: ID LBRACE argList RBRACE{
   std::vector<STAB::ExprAST*> Args;
   for (const auto elt: $3){
      Args.emplace_back(elt);
   }
   $$ = new CallExprAST($1, Args, {@1.first, @4.first});
 }

%%

namespace STAB {

 std::string improveErrMessage(std::string message){
    std::unordered_map<std::string, std::string> tokenMap = {
        {"LBRACE", "'('"},
        {"RBRACE", "')'"},
        {"LCURLY", "'{'"},
        {"RCURLY", "'}'"},
        {"LBIG", "'['"},
        {"RBIG", "']'"},
        {"ASSIGN", "'='"},
        {"IF", "'if'"},
        {"ELSE", "'else'"},
        {"ELSE_IF", "'else if'"},
        {"LOOP", "'loop'"},
        {"FOR", "'for'"},
        {"WHILE", "'while'"},
        {"AND", "'&&'"},
        {"OR", "'||'"},
        {"XOR", "'^'"},
        {"MATCH", "'match'"},
        {"IMPORT", "'import'"},
        {"IN", "'in'"},
        {"TO", "'to'"},
        {"COMMA", "','"},
        {"FN_ARROW", "'->'"},
        {"MATCH_ARROW", "'=>'"},
        {"RETURN", "'return'"},
        {"BREAK", "'break'"},
        {"SKIP", "'skip'"},
        {"SEMI_COLON", "';'"},
        {"PLUS", "'+'"},
        {"MOD", "'%'"},
        {"MINUS", "'-'"},
        {"TIMES", "'*'"},
        {"DIV", "'/'"},
        {"GT", "'>'"},
        {"LT", "'<'"},
        {"GE", "'>='"},
        {"LE", "'<='"},
        {"NE", "'!='"},
        {"EQ", "'=='"},
    };

    // Iterate over each token and perform replacements
    for (const auto& [token, symbol] : tokenMap) {
        size_t pos = 0;
        while ((pos = message.find(token, pos)) != std::string::npos) {
            message.replace(pos, token.length(), symbol);
            pos += symbol.length();
        }
    }
    return message;
 }

 template <typename RHS>
 inline void calcLocation(location& current, const RHS& rhs, const std::size_t n){
   current = location(YYRHSLOC(rhs, 1).first, YYRHSLOC(rhs, n).second);
 }
//void Parser::report_syntax_error(const context& ctx) const {
 // std::cerr << ctx.location() << ": Syntax Error Something went wrong";
 //}
 void Parser::error(const location &loc,const std::string& message){
   std::string improved_message = improveErrMessage(message);
   color("red", "Error:");
   color("blue",improved_message, true);
   std::cout << "[" << loc.first << "]" << lexer.getSource(loc.first) << '\n';
   // + 2 to counter the addition of line number
   color("green",setArrow(loc.second + 2), true);
   return;
  }
}

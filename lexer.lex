%{
 #include "scope.h"
 int yylval;
 #define ID 1
 #define NUMBER 2
 #define LT 3
 #define LE 4
 #define EQ 5
 #define GT 6
 #define GE 7
 #define NE 8
 #define IF 9
 #define ELSE 10
 #define RELOP 11
 #define PLUS 12
 #define MINUS 13
 #define TIMES 14
 #define DIV 15
 #define MOD 16
 #define ARTHOP 17
 #define ASSIGN 18
 #define OPEN_BRACE 19
 #define CLOSE_BRACE 20
 #define OPEN_CURLY 21
 #define CLOSE_CURLY 22
 #define OPEN_BIG_BRACE 23 
 #define CLOSE_BIG_BRACE 24

 // when the program runs we at least need a global scope 
 Scope* first = new Scope;
 Scope* currentScope = first;

 int installID(Scope* e, const char* text){
  std::string id{text};
  e->symbolTable.emplace_back(id);

  return e->symbolTable.size() + 1;
 }

 int installNumber(Scope* e, const char* text){
   std::string num{text};
   e->numberTable.emplace_back(num);

   return e->numberTable.size() + 1;
 }
 Scope* createNewScope(Scope e){
   Scope* anotherEnv = new Scope(e);
   return anotherEnv;
 }

 void deleteScope(Scope* e){
   delete e; 
 }
%}

%option noyywrap c++

/* general definitions */
delimeter [ \t\n]
whiteSpace {delimeter}+
digit [0-9]
letter [A-Za-z]
identifier {letter}({letter}|{digit})*
number {digit}+(\.{digit}+)?(E[+-]?{digit}+)

%%

{whiteSpace} {/* do nothing ignore*/}

{digit}+ {
  yylval = installNumber(currentScope, YYText());
  return (NUMBER);
}

{identifier} {
  yylval = installID(currentScope, YYText());
  return (ID);
}
"+" {
  yylval = PLUS;
  return (ARTHOP);
}

"-" {
  yylval = MINUS;
  return (ARTHOP);
}

"*" {
  yylval = TIMES;
  return (ARTHOP);
}

"/" {
 yylval = DIV;
 return (ARTHOP);
}

"%" {
  yylval = MOD;
  return (ARTHOP);
}

"(" {
   yylval = OPEN_BRACE;
   return (OPEN_BRACE);
}

")" {
   yylval = CLOSE_BRACE;
   return (CLOSE_BRACE);
}
"{" {
   yylval = OPEN_CURLY;
   currentScope = createNewScope(currentScope);
   return (OPEN_CURLY);
}

"}" {
   yylval = CLOSE_CURLY;
   auto temp_scope = currentScope->prev;
   deleteScope(currentScope);
   currentScope = temp_scope;
   return (CLOSE_CURLY);
}

"[" {
   yylval = OPEN_BIG_BRACE;
   return (OPEN_BIG_BRACE);
}

"]" {
   yylval = CLOSE_BIG_BRACE;
   return (CLOSE_BIG_BRACE);
}

"<" {
   yylval = LT;
   return (RELOP);
}

"<=" {
   yylval = LE;
   return (RELOP);
}

">" {
  yylval = GT;
  return (RELOP); 
}

">=" {
  yylval = GE;
  return (RELOP);
}

"=" {
  yylval = ASSIGN;
  return (ASSIGN);
}

"==" {
  yylval = EQ;
  return (RELOP);
}

"!=" {
  yylval = NE;
  return (RELOP);
}
%%

int main(){
 FlexLexer* lexer = new yyFlexLexer;
 lexer->yylex() ;
}

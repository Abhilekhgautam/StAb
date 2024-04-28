%{
 #include "scope.h"
 #include "utils.h"
 int yylval;

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
  return (Token::NUMBER);
}

{identifier} {
  yylval = installID(currentScope, YYText());
  return (Token::ID);
}
"+" {
  yylval = Token::PLUS;
  return (Token::ARTHOP);
}

"-" {
  yylval = Token::MINUS;
  return (Token::ARTHOP);
}

"*" {
  yylval = Token::TIMES;
  return (Token::ARTHOP);
}

"/" {
 yylval = Token::DIV;
 return (Token::ARTHOP);
}

"%" {
  yylval = Token::MOD;
  return (Token::ARTHOP);
}

"(" {
   yylval = Token::LBRACE;
   return (Token::LBRACE);
}

")" {
   yylval = Token::RBRACE;
   return (Token::RBRACE);
}
"{" {
   yylval = Token::LCURLY;
   currentScope = createNewScope(currentScope);
   return (Token::LCURLY);
}

"}" {
   yylval = Token::RCURLY;
   auto temp_scope = currentScope->prev;
   deleteScope(currentScope);
   currentScope = temp_scope;
   return (Token::RCURLY);
}

"[" {
   yylval = Token::LBIG;
   return (Token::LBIG);
}

"]" {
   yylval = Token::RBIG;
   return (Token::RBIG);
}

"<" {
   yylval = Token::LT;
   return (Token::RELOP);
}

"<=" {
   yylval = Token::LE;
   return (Token::RELOP);
}

">" {
  yylval = Token::GT;
  return (Token::RELOP); 
}

">=" {
  yylval = Token::GE;
  return (Token::RELOP);
}

"=" {
  yylval = Token::ASSIGN;
  return (Token::ASSIGN);
}

"==" {
  yylval = Token::EQ;
  return (Token::RELOP);
}

"!=" {
  yylval = Token::NE;
  return (Token::RELOP);
}
%%

int main(){
 FlexLexer* lexer = new yyFlexLexer;
 lexer->yylex() ;
}

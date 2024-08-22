%{
  #include "lexer.hpp"
  #include <cstring>
  using namespace STAB;

  #undef YY_DECL
  #define YY_DECL int Lexer::yylex(STAB::Parser::value_type* lval, location* const lloc)
  #define YY_USER_INIT yylval = lval; yyloc = lloc;
  #define YY_USER_ACTION copyLocation();
%}

%option c++ noyywrap debug
%option yylineno
%option yyclass = "Lexer"
%option prefix = "yy_stab_"

id    [a-zA-Z][a-zA-Z_0-9]*
digit   [0-9]+
blank [ \t\r]
str [^\"\\]*\\.[^\"\\]**
%{
  using Token = STAB::Parser::token;
  using location = STAB::location;
%}

%%
{blank}+ {/* do nothing; ignore */step(strlen(yytext));}
{digit}+ {
  yylval->emplace<std::string>(yytext);
  step(strlen(yytext));
  return Token::token_kind_type::NUMBER;
}
"//".* /* eat up the entire line */
"\n" {++currentLine; currentColumn = 1;}

";" {
     step();
     return Token::token_kind_type::SEMI_COLON;
    }
"->" {
      step(2);
      return Token::token_kind_type::FN_ARROW;
     }
"," {
     step();
     return Token::token_kind_type::COMMA;
    }
"=>" {
      step(2);
      return Token::token_kind_type::MATCH_ARROW;
     }
"fn" {
     step(2);
     return Token::token_kind_type::FN;
     }
"if" {
     step(2);
     return Token::token_kind_type::IF;
     }
"else"  {
        step(4);
        return Token::token_kind_type::ELSE;
        }
"else if" {
            step(6);
            return Token::token_kind_type::ELSE_IF;
           }
"loop" {
        step(4);
        return Token::token_kind_type::LOOP;
       }
"for" { step(3);
        return Token::token_kind_type::FOR;
      }

"while" { step(5);return Token::token_kind_type::WHILE;}

"match" {step(5); return Token::token_kind_type::MATCH;}

"int" {
       yylval->emplace<std::string>(yytext);
       step(3);
       return Token::token_kind_type::DATA_TYPE;
      }
"in" { step(2); return Token::token_kind_type::IN;}

"import" { step(6); return Token::token_kind_type::IMPORT;}

"and" { step(3); return Token::token_kind_type::AND;}

"or" { step(2); return Token::token_kind_type::OR;}

"xor" { step(3);return Token::token_kind_type::XOR;}

"break" { step(5); return Token::token_kind_type::BREAK;}

"skip" { step(5); return Token::token_kind_type::SKIP;}

"return" { step(6); return Token::token_kind_type::RETURN;}

"void" {
         yylval->emplace<std::string>(yytext);
	 step(4);
	 return Token::token_kind_type::DATA_TYPE;
       }

"string" {
          yylval->emplace<std::string>(yytext);
	  step(6);
	  return Token::token_kind_type::DATA_TYPE;
         }

"to" { step(2); return Token::token_kind_type::TO;}

\"([^\"\\]*(\\.[^\"\\]*)*)\" {
        yylval->emplace<std::string>(yytext);
	step(strlen(yytext));
        return Token::token_kind_type::STRING;
     }

{id} {
       yylval->emplace<std::string>(yytext);
       step(strlen(yytext));
       return Token::token_kind_type::ID;
    }

"+" {
    yylval->emplace<std::string>(yytext);
    step();
    return Token::token_kind_type::PLUS;
    }

"-" {
    yylval->emplace<std::string>(yytext);
    step();
    return Token::token_kind_type::MINUS;
    }

"*" {
     yylval->emplace<std::string>(yytext);
     step();
     return Token::token_kind_type::TIMES;
    }
"/" {
     yylval->emplace<std::string>(yytext);
     step();
     return Token::token_kind_type::DIV;
    }
"%"  {
     yylval->emplace<std::string>(yytext);
     step();
     return Token::token_kind_type::MOD;
     }
"("  { step(); return Token::token_kind_type::LBRACE;}

")"  { step(); return Token::token_kind_type::RBRACE;}

"{" { step(); return Token::token_kind_type::LCURLY;}

"}" { step(); return Token::token_kind_type::RCURLY;}

"[" { step(); return Token::token_kind_type::LBIG;}

"]" { step(); return Token::token_kind_type::RBIG;}

"<" {
     yylval->emplace<std::string>(yytext);
     step(strlen(yytext));
     return Token::token_kind_type::LT;
    }
"<=" {
      yylval->emplace<std::string>("l");
      step(2);
      return Token::token_kind_type::LE;
     }
">" {
      yylval->emplace<std::string>(yytext);
      step();
      return Token::token_kind_type::GT;
    }

">=" {
      yylval->emplace<std::string>("g");
      step(2);
     return Token::token_kind_type::GE;
     }

"==" {
      yylval->emplace<std::string>("e");
      step(2);
      return Token::token_kind_type::EQ;
     }
"=" { step(); return Token::token_kind_type::ASSIGN;}

"!=" {
      yylval->emplace<std::string>("n");
      step(2);
      return  Token::token_kind_type::NE;
     }
%%

%{
  #include "lexer.hpp"

  using namespace STAB;

  #undef YY_DECL
  #define YY_DECL int Lexer::yylex(STAB::Parser::value_type* lval, location* const lloc)
  #define YY_USER_INIT yylval = lval; yyloc = lloc;
  #define YY_USER_ACTION copyLocation();
%}

%option c++ noyywrap debug 

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
{blank}+ {/* do nothing; ignore */}
{digit}+ {
  yylval->emplace<std::string>(yytext);
  return Token::token_kind_type::NUMBER;
}
"\n" {++currentLine;}

";" return Token::token_kind_type::SEMI_COLON;

"->" return Token::token_kind_type::FN_ARROW;

"," return Token::token_kind_type::COMMA;

"=>" return Token::token_kind_type::MATCH_ARROW;

"fn" return Token::token_kind_type::FN;

"if" return Token::token_kind_type::IF;

"else" return Token::token_kind_type::ELSE;

"else if" return Token::token_kind_type::ELSE_IF;

"loop" return Token::token_kind_type::LOOP;

"for" return Token::token_kind_type::FOR;

"while" return Token::token_kind_type::WHILE;

"match" return Token::token_kind_type::MATCH;

"int" {
       yylval->emplace<std::string>(yytext);
       return Token::token_kind_type::DATA_TYPE;
      }
"in" return Token::token_kind_type::IN;

"import" return Token::token_kind_type::IMPORT;

"and" return Token::token_kind_type::AND;

"or" return Token::token_kind_type::OR;

"xor" return Token::token_kind_type::XOR;

"break" return Token::token_kind_type::CONTROL_FLOW;

"continue" return Token::token_kind_type::CONTROL_FLOW;

"return" return Token::token_kind_type::RETURN;

"void" {
         yylval->emplace<std::string>(yytext);
	 return Token::token_kind_type::DATA_TYPE;
       }

"string" {
          yylval->emplace<std::string>(yytext);
	  return Token::token_kind_type::DATA_TYPE;
         }

"to" return Token::token_kind_type::TO;

\"([^\"\\]*(\\.[^\"\\]*)*)\" {
        yylval->emplace<std::string>(yytext);
        return Token::token_kind_type::STRING;
     }

{id} {  
       yylval->emplace<std::string>(yytext);
       return Token::token_kind_type::ID;
    }

"+" {
    yylval->emplace<std::string>(yytext);
    return Token::token_kind_type::PLUS;
    }

"-" {
    yylval->emplace<std::string>(yytext);
    return Token::token_kind_type::MINUS;
    }

"*" {
     yylval->emplace<std::string>(yytext);
     return Token::token_kind_type::TIMES;
    }
"/" {
     yylval->emplace<std::string>(yytext);
     return Token::token_kind_type::DIV;
    }
"%"  {
     yylval->emplace<std::string>(yytext);
     return Token::token_kind_type::MOD;
     }
"("  return Token::token_kind_type::LBRACE;

")"  return Token::token_kind_type::RBRACE;

"{" return Token::token_kind_type::LCURLY;

"}" return Token::token_kind_type::RCURLY;

"["  return Token::token_kind_type::LBIG;

"]" return Token::token_kind_type::RBIG;

"<" {
     yylval->emplace<std::string>(yytext);
     return Token::token_kind_type::LT;
    }
"<=" {
      yylval->emplace<std::string>("l");
      return Token::token_kind_type::LE;
     }
">" {
      yylval->emplace<std::string>(yytext);
      return Token::token_kind_type::GT;
    }

">=" {
      yylval->emplace<std::string>("g");
      return Token::token_kind_type::GE;
     }

"==" {
      yylval->emplace<std::string>("e");
      return Token::token_kind_type::EQ;
     }
"=" return Token::token_kind_type::ASSIGN;

"!=" {
      yylval->emplace<std::string>("n");
      return  Token::token_kind_type::NE;
     }
%%

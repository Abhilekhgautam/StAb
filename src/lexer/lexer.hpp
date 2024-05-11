#pragma once

#if ! defined(yyFlexLexerOnce)
#define yyFlexLexer yy_stab_FlexLexer
#include <FlexLexer.h>
#undef yyFlexLexer
#endif

#include "../includes/location.hpp"
#include "../parser/parser.hpp"

namespace STAB {
 class Lexer: public yy_stab_FlexLexer{
    std::size_t currentLine = 1;

    Parser::value_type* yylval = nullptr;
    location *yyloc = nullptr;

    void copyValue(const std::size_t leftTrim = 0, const std::size_t rightTrim = 0 , const bool trimCr = false);

    void copyLocation(){
	*yyloc = location(currentLine, currentLine);    
    }

    public:
       Lexer(std::istream& in, const bool debug): yy_stab_FlexLexer(&in){
          yy_stab_FlexLexer::set_debug(debug);
       }

       //int yylex(std::string *const lval, location *const lloc);
       int yylex(Parser::value_type* lval, location* const lloc);
 };	
/* inline void Lexer::copyValue(const std::size_t leftTrim, const std::size_t rightTrim, const bool trimCr){
   std::size_t endPos = yyleng - rightTrim;
   if(trimCr && endPos != 0 && yytext[endPos - 1] == '\r') --endPos;

   std::cout << "Throwing you SegFault baby\n";

  *yylval = std::string(yytext + leftTrim, yytext + endPos);
  }*/
}

#pragma once
#ifndef STAB_LEXER_H
#define STAB_LEXER_H
#include <string>
#include <vector>
#if ! defined(yyFlexLexerOnce)
#define yyFlexLexer yy_stab_FlexLexer
#include <FlexLexer.h>
#undef yyFlexLexer
#endif

#include "../includes/location.hpp"
#ifndef YY_YY_SRC_PARSER_PARSER_HPP_INCLUDED
#include "../parser/parser.hpp"
#endif


namespace STAB {
 class Lexer: public yy_stab_FlexLexer{
    std::size_t currentLine = 1;
    std::size_t currentColumn = 1;
    std::istream& in;
    Parser::value_type* yylval = nullptr;
    location *yyloc = nullptr;
    std::vector<std::string> sourceLines;

    void step(std::size_t steps = 1){currentColumn += steps;}

    void copyValue(const std::size_t leftTrim = 0, const std::size_t rightTrim = 0 , const bool trimCr = false);


    void copyLocation(){
	    *yyloc = location(currentLine, currentColumn);
    }

    public:
       Lexer(std::istream& in, const bool debug): yy_stab_FlexLexer(&in), in(in){
          yy_stab_FlexLexer::set_debug(debug);
       }

        const std::string getSource(std::size_t index){
	      return Lexer::sourceLines[index - 1];
       }

        void initSourceLine(){
	      std::string line;
	      while(std::getline(in, line)){
	        Lexer::sourceLines.emplace_back(line);
	      }
	     // Reset stream state
         in.clear();
         in.seekg(0, std::ios::beg);
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
#endif

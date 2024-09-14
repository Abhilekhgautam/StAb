// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.hpp"


// Unqualified %code blocks.
#line 44 "src/parser/parser.yy"

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

#line 65 "src/parser/parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 22 "src/parser/parser.yy"
namespace STAB {
#line 158 "src/parser/parser.cpp"

  /// Build a parser object.
  Parser::Parser (Lexer& lexer_yyarg, const bool debug_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      lexer (lexer_yyarg),
      debug (debug_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_fnCall: // fnCall
        value.copy< CallExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.copy< ExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arrayDecl: // arrayDecl
        value.copy< STAB::ArrayAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arrayAssign: // arrayAssign
        value.copy< STAB::ArrayAssignAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arrayRef: // arrayRef
        value.copy< STAB::ArrayRefAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_elseifStmt: // elseifStmt
      case symbol_kind::S_ifStmt: // ifStmt
        value.copy< STAB::CondStatementAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_elseStmt: // elseStmt
        value.copy< STAB::ElseStatementAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_range: // range
        value.copy< STAB::RangeStatementAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varInitialization: // varInitialization
        value.copy< STAB::VariableDeclAssignExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_functionDefinition: // functionDefinition
      case symbol_kind::S_functionPrototype: // functionPrototype
      case symbol_kind::S_varDeclaration: // varDeclaration
      case symbol_kind::S_loop: // loop
      case symbol_kind::S_for: // for
      case symbol_kind::S_while: // while
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_assignExpr: // assignExpr
      case symbol_kind::S_returnStmt: // returnStmt
      case symbol_kind::S_breakStmt: // breakStmt
      case symbol_kind::S_skipStmt: // skipStmt
      case symbol_kind::S_ifLadder: // ifLadder
      case symbol_kind::S_fnCallStmt: // fnCallStmt
        value.copy< StatementAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MOD: // MOD
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_TIMES: // TIMES
      case symbol_kind::S_DIV: // DIV
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GE: // GE
      case symbol_kind::S_LE: // LE
      case symbol_kind::S_NE: // NE
      case symbol_kind::S_EQ: // "op"
      case symbol_kind::S_ID: // "identifier"
      case symbol_kind::S_DATA_TYPE: // "type"
      case symbol_kind::S_NUMBER: // "num"
      case symbol_kind::S_STRING: // "str"
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_argList: // argList
      case symbol_kind::S_args: // args
        value.copy< std::vector<ExprAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_paramList: // paramList
      case symbol_kind::S_parameters: // parameters
        value.copy< std::vector<STAB::VariableDeclExprAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_stmts: // stmts
        value.copy< std::vector<StatementAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_paramListPrototype: // paramListPrototype
      case symbol_kind::S_params: // params
        value.copy< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_fnCall: // fnCall
        value.move< CallExprAST* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr: // expr
        value.move< ExprAST* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_arrayDecl: // arrayDecl
        value.move< STAB::ArrayAST* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_arrayAssign: // arrayAssign
        value.move< STAB::ArrayAssignAST* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_arrayRef: // arrayRef
        value.move< STAB::ArrayRefAST* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_elseifStmt: // elseifStmt
      case symbol_kind::S_ifStmt: // ifStmt
        value.move< STAB::CondStatementAST* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_elseStmt: // elseStmt
        value.move< STAB::ElseStatementAST* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_range: // range
        value.move< STAB::RangeStatementAST* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_varInitialization: // varInitialization
        value.move< STAB::VariableDeclAssignExprAST* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_functionDefinition: // functionDefinition
      case symbol_kind::S_functionPrototype: // functionPrototype
      case symbol_kind::S_varDeclaration: // varDeclaration
      case symbol_kind::S_loop: // loop
      case symbol_kind::S_for: // for
      case symbol_kind::S_while: // while
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_assignExpr: // assignExpr
      case symbol_kind::S_returnStmt: // returnStmt
      case symbol_kind::S_breakStmt: // breakStmt
      case symbol_kind::S_skipStmt: // skipStmt
      case symbol_kind::S_ifLadder: // ifLadder
      case symbol_kind::S_fnCallStmt: // fnCallStmt
        value.move< StatementAST* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MOD: // MOD
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_TIMES: // TIMES
      case symbol_kind::S_DIV: // DIV
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GE: // GE
      case symbol_kind::S_LE: // LE
      case symbol_kind::S_NE: // NE
      case symbol_kind::S_EQ: // "op"
      case symbol_kind::S_ID: // "identifier"
      case symbol_kind::S_DATA_TYPE: // "type"
      case symbol_kind::S_NUMBER: // "num"
      case symbol_kind::S_STRING: // "str"
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_argList: // argList
      case symbol_kind::S_args: // args
        value.move< std::vector<ExprAST*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_paramList: // paramList
      case symbol_kind::S_parameters: // parameters
        value.move< std::vector<STAB::VariableDeclExprAST*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_stmts: // stmts
        value.move< std::vector<StatementAST*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_paramListPrototype: // paramListPrototype
      case symbol_kind::S_params: // params
        value.move< std::vector<std::string> > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_fnCall: // fnCall
        value.YY_MOVE_OR_COPY< CallExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.YY_MOVE_OR_COPY< ExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arrayDecl: // arrayDecl
        value.YY_MOVE_OR_COPY< STAB::ArrayAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arrayAssign: // arrayAssign
        value.YY_MOVE_OR_COPY< STAB::ArrayAssignAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arrayRef: // arrayRef
        value.YY_MOVE_OR_COPY< STAB::ArrayRefAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_elseifStmt: // elseifStmt
      case symbol_kind::S_ifStmt: // ifStmt
        value.YY_MOVE_OR_COPY< STAB::CondStatementAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_elseStmt: // elseStmt
        value.YY_MOVE_OR_COPY< STAB::ElseStatementAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_range: // range
        value.YY_MOVE_OR_COPY< STAB::RangeStatementAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varInitialization: // varInitialization
        value.YY_MOVE_OR_COPY< STAB::VariableDeclAssignExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_functionDefinition: // functionDefinition
      case symbol_kind::S_functionPrototype: // functionPrototype
      case symbol_kind::S_varDeclaration: // varDeclaration
      case symbol_kind::S_loop: // loop
      case symbol_kind::S_for: // for
      case symbol_kind::S_while: // while
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_assignExpr: // assignExpr
      case symbol_kind::S_returnStmt: // returnStmt
      case symbol_kind::S_breakStmt: // breakStmt
      case symbol_kind::S_skipStmt: // skipStmt
      case symbol_kind::S_ifLadder: // ifLadder
      case symbol_kind::S_fnCallStmt: // fnCallStmt
        value.YY_MOVE_OR_COPY< StatementAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MOD: // MOD
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_TIMES: // TIMES
      case symbol_kind::S_DIV: // DIV
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GE: // GE
      case symbol_kind::S_LE: // LE
      case symbol_kind::S_NE: // NE
      case symbol_kind::S_EQ: // "op"
      case symbol_kind::S_ID: // "identifier"
      case symbol_kind::S_DATA_TYPE: // "type"
      case symbol_kind::S_NUMBER: // "num"
      case symbol_kind::S_STRING: // "str"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_argList: // argList
      case symbol_kind::S_args: // args
        value.YY_MOVE_OR_COPY< std::vector<ExprAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_paramList: // paramList
      case symbol_kind::S_parameters: // parameters
        value.YY_MOVE_OR_COPY< std::vector<STAB::VariableDeclExprAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_stmts: // stmts
        value.YY_MOVE_OR_COPY< std::vector<StatementAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_paramListPrototype: // paramListPrototype
      case symbol_kind::S_params: // params
        value.YY_MOVE_OR_COPY< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_fnCall: // fnCall
        value.move< CallExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.move< ExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arrayDecl: // arrayDecl
        value.move< STAB::ArrayAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arrayAssign: // arrayAssign
        value.move< STAB::ArrayAssignAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arrayRef: // arrayRef
        value.move< STAB::ArrayRefAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_elseifStmt: // elseifStmt
      case symbol_kind::S_ifStmt: // ifStmt
        value.move< STAB::CondStatementAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_elseStmt: // elseStmt
        value.move< STAB::ElseStatementAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_range: // range
        value.move< STAB::RangeStatementAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varInitialization: // varInitialization
        value.move< STAB::VariableDeclAssignExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_functionDefinition: // functionDefinition
      case symbol_kind::S_functionPrototype: // functionPrototype
      case symbol_kind::S_varDeclaration: // varDeclaration
      case symbol_kind::S_loop: // loop
      case symbol_kind::S_for: // for
      case symbol_kind::S_while: // while
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_assignExpr: // assignExpr
      case symbol_kind::S_returnStmt: // returnStmt
      case symbol_kind::S_breakStmt: // breakStmt
      case symbol_kind::S_skipStmt: // skipStmt
      case symbol_kind::S_ifLadder: // ifLadder
      case symbol_kind::S_fnCallStmt: // fnCallStmt
        value.move< StatementAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MOD: // MOD
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_TIMES: // TIMES
      case symbol_kind::S_DIV: // DIV
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GE: // GE
      case symbol_kind::S_LE: // LE
      case symbol_kind::S_NE: // NE
      case symbol_kind::S_EQ: // "op"
      case symbol_kind::S_ID: // "identifier"
      case symbol_kind::S_DATA_TYPE: // "type"
      case symbol_kind::S_NUMBER: // "num"
      case symbol_kind::S_STRING: // "str"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_argList: // argList
      case symbol_kind::S_args: // args
        value.move< std::vector<ExprAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_paramList: // paramList
      case symbol_kind::S_parameters: // parameters
        value.move< std::vector<STAB::VariableDeclExprAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_stmts: // stmts
        value.move< std::vector<StatementAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_paramListPrototype: // paramListPrototype
      case symbol_kind::S_params: // params
        value.move< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_fnCall: // fnCall
        value.copy< CallExprAST* > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.copy< ExprAST* > (that.value);
        break;

      case symbol_kind::S_arrayDecl: // arrayDecl
        value.copy< STAB::ArrayAST* > (that.value);
        break;

      case symbol_kind::S_arrayAssign: // arrayAssign
        value.copy< STAB::ArrayAssignAST* > (that.value);
        break;

      case symbol_kind::S_arrayRef: // arrayRef
        value.copy< STAB::ArrayRefAST* > (that.value);
        break;

      case symbol_kind::S_elseifStmt: // elseifStmt
      case symbol_kind::S_ifStmt: // ifStmt
        value.copy< STAB::CondStatementAST* > (that.value);
        break;

      case symbol_kind::S_elseStmt: // elseStmt
        value.copy< STAB::ElseStatementAST* > (that.value);
        break;

      case symbol_kind::S_range: // range
        value.copy< STAB::RangeStatementAST* > (that.value);
        break;

      case symbol_kind::S_varInitialization: // varInitialization
        value.copy< STAB::VariableDeclAssignExprAST* > (that.value);
        break;

      case symbol_kind::S_functionDefinition: // functionDefinition
      case symbol_kind::S_functionPrototype: // functionPrototype
      case symbol_kind::S_varDeclaration: // varDeclaration
      case symbol_kind::S_loop: // loop
      case symbol_kind::S_for: // for
      case symbol_kind::S_while: // while
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_assignExpr: // assignExpr
      case symbol_kind::S_returnStmt: // returnStmt
      case symbol_kind::S_breakStmt: // breakStmt
      case symbol_kind::S_skipStmt: // skipStmt
      case symbol_kind::S_ifLadder: // ifLadder
      case symbol_kind::S_fnCallStmt: // fnCallStmt
        value.copy< StatementAST* > (that.value);
        break;

      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MOD: // MOD
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_TIMES: // TIMES
      case symbol_kind::S_DIV: // DIV
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GE: // GE
      case symbol_kind::S_LE: // LE
      case symbol_kind::S_NE: // NE
      case symbol_kind::S_EQ: // "op"
      case symbol_kind::S_ID: // "identifier"
      case symbol_kind::S_DATA_TYPE: // "type"
      case symbol_kind::S_NUMBER: // "num"
      case symbol_kind::S_STRING: // "str"
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_argList: // argList
      case symbol_kind::S_args: // args
        value.copy< std::vector<ExprAST*> > (that.value);
        break;

      case symbol_kind::S_paramList: // paramList
      case symbol_kind::S_parameters: // parameters
        value.copy< std::vector<STAB::VariableDeclExprAST*> > (that.value);
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_stmts: // stmts
        value.copy< std::vector<StatementAST*> > (that.value);
        break;

      case symbol_kind::S_paramListPrototype: // paramListPrototype
      case symbol_kind::S_params: // params
        value.copy< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_fnCall: // fnCall
        value.move< CallExprAST* > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.move< ExprAST* > (that.value);
        break;

      case symbol_kind::S_arrayDecl: // arrayDecl
        value.move< STAB::ArrayAST* > (that.value);
        break;

      case symbol_kind::S_arrayAssign: // arrayAssign
        value.move< STAB::ArrayAssignAST* > (that.value);
        break;

      case symbol_kind::S_arrayRef: // arrayRef
        value.move< STAB::ArrayRefAST* > (that.value);
        break;

      case symbol_kind::S_elseifStmt: // elseifStmt
      case symbol_kind::S_ifStmt: // ifStmt
        value.move< STAB::CondStatementAST* > (that.value);
        break;

      case symbol_kind::S_elseStmt: // elseStmt
        value.move< STAB::ElseStatementAST* > (that.value);
        break;

      case symbol_kind::S_range: // range
        value.move< STAB::RangeStatementAST* > (that.value);
        break;

      case symbol_kind::S_varInitialization: // varInitialization
        value.move< STAB::VariableDeclAssignExprAST* > (that.value);
        break;

      case symbol_kind::S_functionDefinition: // functionDefinition
      case symbol_kind::S_functionPrototype: // functionPrototype
      case symbol_kind::S_varDeclaration: // varDeclaration
      case symbol_kind::S_loop: // loop
      case symbol_kind::S_for: // for
      case symbol_kind::S_while: // while
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_assignExpr: // assignExpr
      case symbol_kind::S_returnStmt: // returnStmt
      case symbol_kind::S_breakStmt: // breakStmt
      case symbol_kind::S_skipStmt: // skipStmt
      case symbol_kind::S_ifLadder: // ifLadder
      case symbol_kind::S_fnCallStmt: // fnCallStmt
        value.move< StatementAST* > (that.value);
        break;

      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MOD: // MOD
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_TIMES: // TIMES
      case symbol_kind::S_DIV: // DIV
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GE: // GE
      case symbol_kind::S_LE: // LE
      case symbol_kind::S_NE: // NE
      case symbol_kind::S_EQ: // "op"
      case symbol_kind::S_ID: // "identifier"
      case symbol_kind::S_DATA_TYPE: // "type"
      case symbol_kind::S_NUMBER: // "num"
      case symbol_kind::S_STRING: // "str"
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_argList: // argList
      case symbol_kind::S_args: // args
        value.move< std::vector<ExprAST*> > (that.value);
        break;

      case symbol_kind::S_paramList: // paramList
      case symbol_kind::S_parameters: // parameters
        value.move< std::vector<STAB::VariableDeclExprAST*> > (that.value);
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_stmts: // stmts
        value.move< std::vector<StatementAST*> > (that.value);
        break;

      case symbol_kind::S_paramListPrototype: // paramListPrototype
      case symbol_kind::S_params: // params
        value.move< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
#line 38 "src/parser/parser.yy"
{
  #if YYDEBUG != 0
    set_debug_level(debug);
  #endif
}

#line 1068 "src/parser/parser.cpp"


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_fnCall: // fnCall
        yylhs.value.emplace< CallExprAST* > ();
        break;

      case symbol_kind::S_expr: // expr
        yylhs.value.emplace< ExprAST* > ();
        break;

      case symbol_kind::S_arrayDecl: // arrayDecl
        yylhs.value.emplace< STAB::ArrayAST* > ();
        break;

      case symbol_kind::S_arrayAssign: // arrayAssign
        yylhs.value.emplace< STAB::ArrayAssignAST* > ();
        break;

      case symbol_kind::S_arrayRef: // arrayRef
        yylhs.value.emplace< STAB::ArrayRefAST* > ();
        break;

      case symbol_kind::S_elseifStmt: // elseifStmt
      case symbol_kind::S_ifStmt: // ifStmt
        yylhs.value.emplace< STAB::CondStatementAST* > ();
        break;

      case symbol_kind::S_elseStmt: // elseStmt
        yylhs.value.emplace< STAB::ElseStatementAST* > ();
        break;

      case symbol_kind::S_range: // range
        yylhs.value.emplace< STAB::RangeStatementAST* > ();
        break;

      case symbol_kind::S_varInitialization: // varInitialization
        yylhs.value.emplace< STAB::VariableDeclAssignExprAST* > ();
        break;

      case symbol_kind::S_functionDefinition: // functionDefinition
      case symbol_kind::S_functionPrototype: // functionPrototype
      case symbol_kind::S_varDeclaration: // varDeclaration
      case symbol_kind::S_loop: // loop
      case symbol_kind::S_for: // for
      case symbol_kind::S_while: // while
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_assignExpr: // assignExpr
      case symbol_kind::S_returnStmt: // returnStmt
      case symbol_kind::S_breakStmt: // breakStmt
      case symbol_kind::S_skipStmt: // skipStmt
      case symbol_kind::S_ifLadder: // ifLadder
      case symbol_kind::S_fnCallStmt: // fnCallStmt
        yylhs.value.emplace< StatementAST* > ();
        break;

      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MOD: // MOD
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_TIMES: // TIMES
      case symbol_kind::S_DIV: // DIV
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GE: // GE
      case symbol_kind::S_LE: // LE
      case symbol_kind::S_NE: // NE
      case symbol_kind::S_EQ: // "op"
      case symbol_kind::S_ID: // "identifier"
      case symbol_kind::S_DATA_TYPE: // "type"
      case symbol_kind::S_NUMBER: // "num"
      case symbol_kind::S_STRING: // "str"
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_argList: // argList
      case symbol_kind::S_args: // args
        yylhs.value.emplace< std::vector<ExprAST*> > ();
        break;

      case symbol_kind::S_paramList: // paramList
      case symbol_kind::S_parameters: // parameters
        yylhs.value.emplace< std::vector<STAB::VariableDeclExprAST*> > ();
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_stmts: // stmts
        yylhs.value.emplace< std::vector<StatementAST*> > ();
        break;

      case symbol_kind::S_paramListPrototype: // paramListPrototype
      case symbol_kind::S_params: // params
        yylhs.value.emplace< std::vector<std::string> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // functionDefinition: FN "identifier" LBRACE paramList RBRACE FN_ARROW "type" LCURLY stmts RCURLY
#line 101 "src/parser/parser.yy"
                                                                                         {
			auto fnScope = new Scope(currentScope, "fn");
			currentScope = fnScope;
            std::vector<std::string> argTypes;
			std::vector<STAB::VariableDeclExprAST*> declVars;
            for(const auto elt: yystack_[6].value.as < std::vector<STAB::VariableDeclExprAST*> > ()){
			  argTypes.emplace_back(elt->getType());
			  declVars.emplace_back(elt);
			}
			auto proto = new STAB::PrototypeAST(yystack_[3].value.as < std::string > (), yystack_[8].value.as < std::string > (), argTypes, {yystack_[9].location.first, yystack_[0].location.second});
			yylhs.value.as < StatementAST* > () = new STAB::FunctionAST(proto,declVars, yystack_[1].value.as < std::vector<StatementAST*> > (), fnScope, {yystack_[9].location.first, yystack_[0].location.second});
			currentScope = globalScope;
}
#line 1308 "src/parser/parser.cpp"
    break;

  case 3: // functionDefinition: FN "identifier" LBRACE paramList RBRACE LCURLY stmts RCURLY
#line 115 "src/parser/parser.yy"
                                                               {
                auto fnScope = new Scope(currentScope, "fn");
			    currentScope = fnScope;
                std::vector<std::string> argTypes;
			    std::vector<STAB::VariableDeclExprAST*> declVars;
                for(const auto elt: yystack_[4].value.as < std::vector<STAB::VariableDeclExprAST*> > ()){
			        argTypes.emplace_back(elt->getType());
			        declVars.emplace_back(elt);
			    }
			    auto proto = new STAB::PrototypeAST("void", yystack_[6].value.as < std::string > (), argTypes, {yystack_[7].location.first, yystack_[0].location.first});
			    yylhs.value.as < StatementAST* > () = new STAB::FunctionAST(proto,declVars, yystack_[1].value.as < std::vector<StatementAST*> > (), fnScope, {yystack_[7].location.first, yystack_[0].location.first});
			    currentScope = globalScope;
}
#line 1326 "src/parser/parser.cpp"
    break;

  case 4: // functionPrototype: FN "identifier" LBRACE paramListPrototype RBRACE FN_ARROW "type" SEMI_COLON
#line 129 "src/parser/parser.yy"
                                                                                         {
                        std::vector<std::string> Args;
		                for(const auto elt: yystack_[4].value.as < std::vector<std::string> > ()){
		                Args.emplace_back(elt);
		           }
                       yylhs.value.as < StatementAST* > () = new STAB::PrototypeAST(yystack_[1].value.as < std::string > (), yystack_[6].value.as < std::string > (), Args, {yystack_[7].location.first, yystack_[0].location.first});
                   }
#line 1338 "src/parser/parser.cpp"
    break;

  case 5: // varDeclaration: "type" "identifier" SEMI_COLON
#line 138 "src/parser/parser.yy"
                                         {
                  yylhs.value.as < StatementAST* > () = new STAB::VariableDeclExprAST(yystack_[2].value.as < std::string > (), yystack_[1].value.as < std::string > (), {yystack_[2].location.first, yystack_[0].location.first});
                }
#line 1346 "src/parser/parser.cpp"
    break;

  case 6: // varInitialization: "type" "identifier" ASSIGN expr SEMI_COLON
#line 142 "src/parser/parser.yy"
                                                        {
                     auto type = yystack_[4].value.as < std::string > ();
		             auto name = yystack_[3].value.as < std::string > ();
		             auto val = yystack_[1].value.as < ExprAST* > ();
		             auto varDecl = new VariableDeclExprAST(type, name, {yystack_[4].location.first, yystack_[0].location.first});
		             yylhs.value.as < STAB::VariableDeclAssignExprAST* > () = new VariableDeclAssignExprAST(varDecl, val, {yystack_[4].location.first, yystack_[0].location.first});
		           }
#line 1358 "src/parser/parser.cpp"
    break;

  case 7: // arrayDecl: "type" "identifier" LBIG expr RBIG SEMI_COLON
#line 151 "src/parser/parser.yy"
                                                  {
              yylhs.value.as < STAB::ArrayAST* > () = new ArrayAST(yystack_[5].value.as < std::string > (), yystack_[4].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), {yystack_[5].location.first,yystack_[0].location.first});
          }
#line 1366 "src/parser/parser.cpp"
    break;

  case 8: // arrayAssign: "identifier" LBIG expr RBIG ASSIGN expr SEMI_COLON
#line 156 "src/parser/parser.yy"
                                                      {
              yylhs.value.as < STAB::ArrayAssignAST* > () = new ArrayAssignAST(yystack_[6].value.as < std::string > (), yystack_[4].value.as < ExprAST* > (), yystack_[1].value.as < ExprAST* > (), {yystack_[6].location.first, yystack_[0].location.first});
            }
#line 1374 "src/parser/parser.cpp"
    break;

  case 9: // arrayRef: "identifier" LBIG expr RBIG
#line 161 "src/parser/parser.yy"
                             {
           yylhs.value.as < STAB::ArrayRefAST* > () = new ArrayRefAST(yystack_[3].value.as < std::string > (), yystack_[1].value.as < ExprAST* > (), {yystack_[3].location.first, yystack_[0].location.first});
         }
#line 1382 "src/parser/parser.cpp"
    break;

  case 10: // loop: LOOP LCURLY stmts RCURLY
#line 166 "src/parser/parser.yy"
                               {
       yylhs.value.as < StatementAST* > () = new LoopStatementAST(yystack_[1].value.as < std::vector<StatementAST*> > (), {yystack_[3].location.first, yystack_[2].location.first});

     }
#line 1391 "src/parser/parser.cpp"
    break;

  case 11: // range: expr TO expr
#line 171 "src/parser/parser.yy"
                    {
          auto step = new NumberExprAST(1, {0, 0});
          yylhs.value.as < STAB::RangeStatementAST* > () = new RangeStatementAST(yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > (), step, {yystack_[2].location.first, yystack_[0].location.first});
      }
#line 1400 "src/parser/parser.cpp"
    break;

  case 12: // for: FOR "identifier" IN range LCURLY stmts RCURLY
#line 177 "src/parser/parser.yy"
                                          {
        std::string type = "int";
	    auto varDecl = new VariableDeclExprAST(type, yystack_[5].value.as < std::string > (), {yystack_[6].location.first, yystack_[2].location.first});
        yylhs.value.as < StatementAST* > () = new ForStatementAST(varDecl, yystack_[3].value.as < STAB::RangeStatementAST* > (), yystack_[1].value.as < std::vector<StatementAST*> > (), {yystack_[6].location.first, yystack_[2].location.first});
     }
#line 1410 "src/parser/parser.cpp"
    break;

  case 13: // while: WHILE expr LCURLY stmts RCURLY
#line 184 "src/parser/parser.yy"
                                      {
       yylhs.value.as < StatementAST* > () = new WhileStatementAST(yystack_[3].value.as < ExprAST* > (), yystack_[1].value.as < std::vector<StatementAST*> > (), {yystack_[4].location.first, yystack_[2].location.first});

      }
#line 1419 "src/parser/parser.cpp"
    break;

  case 14: // program: stmts
#line 189 "src/parser/parser.yy"
              {
       std::vector<std::string> Args;
       std::vector<STAB::VariableDeclExprAST*> declVars;

       std::vector<STAB::StatementAST*> stmts;

       auto proto = new PrototypeAST("void", "__start__", Args, {0, 0});

       yylhs.value.as < std::vector<StatementAST*> > () = yystack_[0].value.as < std::vector<StatementAST*> > ();

       __start__fn = new FunctionAST(proto, declVars, stmts, globalScope, {0,0});

       for (const auto stmt: yystack_[0].value.as < std::vector<StatementAST*> > ())
           __start__fn->getBody().emplace_back(stmt);
       }
#line 1439 "src/parser/parser.cpp"
    break;

  case 15: // stmts: stmts stmt
#line 204 "src/parser/parser.yy"
                 {
       yystack_[1].value.as < std::vector<StatementAST*> > ().emplace_back(yystack_[0].value.as < StatementAST* > ());
       yylhs.value.as < std::vector<StatementAST*> > () = yystack_[1].value.as < std::vector<StatementAST*> > ();
     }
#line 1448 "src/parser/parser.cpp"
    break;

  case 16: // stmts: %empty
#line 208 "src/parser/parser.yy"
              {
       yylhs.value.as < std::vector<StatementAST*> > () = std::vector<STAB::StatementAST*>();
     }
#line 1456 "src/parser/parser.cpp"
    break;

  case 17: // stmt: functionDefinition
#line 214 "src/parser/parser.yy"
                        {
        yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > ();
      }
#line 1464 "src/parser/parser.cpp"
    break;

  case 18: // stmt: loop
#line 217 "src/parser/parser.yy"
            {
        yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > ();
      }
#line 1472 "src/parser/parser.cpp"
    break;

  case 19: // stmt: for
#line 220 "src/parser/parser.yy"
           {
        yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > ();
      }
#line 1480 "src/parser/parser.cpp"
    break;

  case 20: // stmt: while
#line 223 "src/parser/parser.yy"
              {
         yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > ();
      }
#line 1488 "src/parser/parser.cpp"
    break;

  case 21: // stmt: varDeclaration
#line 226 "src/parser/parser.yy"
                      {
        yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > ();
      }
#line 1496 "src/parser/parser.cpp"
    break;

  case 22: // stmt: varInitialization
#line 229 "src/parser/parser.yy"
                         {
         yylhs.value.as < StatementAST* > () = yystack_[0].value.as < STAB::VariableDeclAssignExprAST* > ();
      }
#line 1504 "src/parser/parser.cpp"
    break;

  case 23: // stmt: assignExpr
#line 232 "src/parser/parser.yy"
                  {
         yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > ();
      }
#line 1512 "src/parser/parser.cpp"
    break;

  case 24: // stmt: breakStmt
#line 235 "src/parser/parser.yy"
        { yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > (); }
#line 1518 "src/parser/parser.cpp"
    break;

  case 25: // stmt: skipStmt
#line 236 "src/parser/parser.yy"
        { yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > (); }
#line 1524 "src/parser/parser.cpp"
    break;

  case 26: // stmt: returnStmt
#line 237 "src/parser/parser.yy"
                  {
          yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > ();
      }
#line 1532 "src/parser/parser.cpp"
    break;

  case 27: // stmt: functionPrototype
#line 240 "src/parser/parser.yy"
                          {
        yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > ();
      }
#line 1540 "src/parser/parser.cpp"
    break;

  case 28: // stmt: fnCallStmt
#line 243 "src/parser/parser.yy"
                   {
         yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > ();
      }
#line 1548 "src/parser/parser.cpp"
    break;

  case 29: // stmt: ifLadder
#line 246 "src/parser/parser.yy"
                {
         yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > ();
      }
#line 1556 "src/parser/parser.cpp"
    break;

  case 30: // stmt: arrayDecl
#line 249 "src/parser/parser.yy"
                  {
         yylhs.value.as < StatementAST* > () = yystack_[0].value.as < STAB::ArrayAST* > ();
      }
#line 1564 "src/parser/parser.cpp"
    break;

  case 31: // stmt: arrayAssign
#line 252 "src/parser/parser.yy"
                    {
         yylhs.value.as < StatementAST* > () = yystack_[0].value.as < STAB::ArrayAssignAST* > ();
      }
#line 1572 "src/parser/parser.cpp"
    break;

  case 32: // expr: expr PLUS expr
#line 257 "src/parser/parser.yy"
                      {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > (), {yystack_[2].location.first, yystack_[0].location.first});
      }
#line 1580 "src/parser/parser.cpp"
    break;

  case 33: // expr: expr MINUS expr
#line 260 "src/parser/parser.yy"
                       {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > (), {yystack_[2].location.first, yystack_[0].location.first});
     }
#line 1588 "src/parser/parser.cpp"
    break;

  case 34: // expr: expr TIMES expr
#line 263 "src/parser/parser.yy"
                       {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > (), {yystack_[2].location.first, yystack_[0].location.first});
     }
#line 1596 "src/parser/parser.cpp"
    break;

  case 35: // expr: expr DIV expr
#line 266 "src/parser/parser.yy"
                     {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > (), {yystack_[2].location.first, yystack_[0].location.first});
     }
#line 1604 "src/parser/parser.cpp"
    break;

  case 36: // expr: expr MOD expr
#line 269 "src/parser/parser.yy"
                     {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > (), {yystack_[2].location.first, yystack_[0].location.first});
     }
#line 1612 "src/parser/parser.cpp"
    break;

  case 37: // expr: LBRACE expr RBRACE
#line 272 "src/parser/parser.yy"
                          {
        yylhs.value.as < ExprAST* > () = yystack_[1].value.as < ExprAST* > ();
     }
#line 1620 "src/parser/parser.cpp"
    break;

  case 38: // expr: expr GT expr
#line 275 "src/parser/parser.yy"
                    {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > (), {yystack_[2].location.first, yystack_[0].location.first});
     }
#line 1628 "src/parser/parser.cpp"
    break;

  case 39: // expr: expr LT expr
#line 278 "src/parser/parser.yy"
                    {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > (), {yystack_[2].location.first, yystack_[0].location.first});
     }
#line 1636 "src/parser/parser.cpp"
    break;

  case 40: // expr: expr LE expr
#line 281 "src/parser/parser.yy"
                    {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > (), {yystack_[2].location.first, yystack_[0].location.first});
     }
#line 1644 "src/parser/parser.cpp"
    break;

  case 41: // expr: expr GE expr
#line 284 "src/parser/parser.yy"
                   {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > (), {yystack_[2].location.first, yystack_[0].location.first});
     }
#line 1652 "src/parser/parser.cpp"
    break;

  case 42: // expr: expr "op" expr
#line 287 "src/parser/parser.yy"
                   {
       yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > (), {yystack_[2].location.first, yystack_[0].location.first});
     }
#line 1660 "src/parser/parser.cpp"
    break;

  case 43: // expr: expr NE expr
#line 290 "src/parser/parser.yy"
                   {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > (), {yystack_[2].location.first, yystack_[0].location.first});
     }
#line 1668 "src/parser/parser.cpp"
    break;

  case 44: // expr: "str"
#line 293 "src/parser/parser.yy"
              {
        std::string val = yystack_[0].value.as < std::string > ();
	    auto length = val.length();
	    std::string without_quotation;
	    for(int i = 1; i < length - 1 ; ++i){
	        without_quotation += val[i];
	    }
	    yylhs.value.as < ExprAST* > () = new StringExprAST(without_quotation, {yystack_[0].location.first, 0});
     }
#line 1682 "src/parser/parser.cpp"
    break;

  case 45: // expr: "identifier"
#line 302 "src/parser/parser.yy"
          {
       yylhs.value.as < ExprAST* > () = new VariableExprAST(yystack_[0].value.as < std::string > (), {yystack_[0].location.first, 0});
     }
#line 1690 "src/parser/parser.cpp"
    break;

  case 46: // expr: "num"
#line 305 "src/parser/parser.yy"
              {
        auto num = std::stoi(yystack_[0].value.as < std::string > ());
        yylhs.value.as < ExprAST* > () = new NumberExprAST(num, {yystack_[0].location.first, 0});
     }
#line 1699 "src/parser/parser.cpp"
    break;

  case 47: // expr: fnCall
#line 309 "src/parser/parser.yy"
              {
        yylhs.value.as < ExprAST* > () = new CallExprAST(yystack_[0].value.as < CallExprAST* > ()->getFnName(), yystack_[0].value.as < CallExprAST* > ()->getArgs(), {yystack_[0].location.first, 0});
     }
#line 1707 "src/parser/parser.cpp"
    break;

  case 48: // expr: arrayRef
#line 312 "src/parser/parser.yy"
                {
        yylhs.value.as < ExprAST* > () = yystack_[0].value.as < STAB::ArrayRefAST* > ();
     }
#line 1715 "src/parser/parser.cpp"
    break;

  case 49: // assignExpr: "identifier" ASSIGN expr SEMI_COLON
#line 317 "src/parser/parser.yy"
                                                   {
             yylhs.value.as < StatementAST* > () = new VariableAssignExprAST(yystack_[3].value.as < std::string > (), yystack_[1].value.as < ExprAST* > (), {yystack_[3].location.first, yystack_[0].location.first});
           }
#line 1723 "src/parser/parser.cpp"
    break;

  case 50: // returnStmt: RETURN expr SEMI_COLON
#line 322 "src/parser/parser.yy"
                                   {
              yylhs.value.as < StatementAST* > () = new ReturnStmtAST(yystack_[1].value.as < ExprAST* > (), {yystack_[2].location.first, yystack_[1].location.first});
           }
#line 1731 "src/parser/parser.cpp"
    break;

  case 51: // breakStmt: BREAK SEMI_COLON
#line 327 "src/parser/parser.yy"
                             {
         yylhs.value.as < StatementAST* > () = new BreakStatementAST({yystack_[1].location.first, 0});
       }
#line 1739 "src/parser/parser.cpp"
    break;

  case 52: // skipStmt: SKIP SEMI_COLON
#line 331 "src/parser/parser.yy"
                           {
          yylhs.value.as < StatementAST* > () = new SkipStatementAST({yystack_[1].location.first, 0});
       }
#line 1747 "src/parser/parser.cpp"
    break;

  case 53: // elseStmt: %empty
#line 335 "src/parser/parser.yy"
                 {
          yylhs.value.as < STAB::ElseStatementAST* > () = nullptr;
         }
#line 1755 "src/parser/parser.cpp"
    break;

  case 54: // elseStmt: ELSE LCURLY stmts RCURLY
#line 338 "src/parser/parser.yy"
                                   {
	    yylhs.value.as < STAB::ElseStatementAST* > () = new ElseStatementAST(yystack_[1].value.as < std::vector<StatementAST*> > (), {yystack_[3].location.first, yystack_[2].location.first});
	 }
#line 1763 "src/parser/parser.cpp"
    break;

  case 56: // elseifStmt: ELSE_IF expr LCURLY stmts RCURLY elseifStmt
#line 345 "src/parser/parser.yy"
           {
	     yylhs.value.as < STAB::CondStatementAST* > () = nullptr;
	   }
#line 1771 "src/parser/parser.cpp"
    break;

  case 57: // ifStmt: IF expr LCURLY stmts RCURLY
#line 349 "src/parser/parser.yy"
                                     {
	   yylhs.value.as < STAB::CondStatementAST* > () = new CondStatementAST(yystack_[3].value.as < ExprAST* > (), yystack_[1].value.as < std::vector<StatementAST*> > (), {yystack_[4].location.first, yystack_[2].location.first});
	 }
#line 1779 "src/parser/parser.cpp"
    break;

  case 58: // ifLadder: ifStmt elseifStmt elseStmt
#line 353 "src/parser/parser.yy"
                                     {
            yylhs.value.as < StatementAST* > () = new IfStatementAST(yystack_[2].value.as < STAB::CondStatementAST* > (), nullptr, yystack_[0].value.as < STAB::ElseStatementAST* > (), {yystack_[2].location.first, yystack_[0].location.first});
         }
#line 1787 "src/parser/parser.cpp"
    break;

  case 59: // argList: %empty
#line 358 "src/parser/parser.yy"
                 {
        }
#line 1794 "src/parser/parser.cpp"
    break;

  case 60: // argList: args
#line 360 "src/parser/parser.yy"
               {
	    for(const auto elt: yystack_[0].value.as < std::vector<ExprAST*> > ()){
	       yylhs.value.as < std::vector<ExprAST*> > ().emplace_back(elt);
	 }
	}
#line 1804 "src/parser/parser.cpp"
    break;

  case 61: // args: args COMMA expr
#line 367 "src/parser/parser.yy"
                       {
       for(const auto elt: yystack_[2].value.as < std::vector<ExprAST*> > ())
           yylhs.value.as < std::vector<ExprAST*> > ().emplace_back(elt);
       yylhs.value.as < std::vector<ExprAST*> > ().emplace_back(yystack_[0].value.as < ExprAST* > ());
     }
#line 1814 "src/parser/parser.cpp"
    break;

  case 62: // args: expr
#line 372 "src/parser/parser.yy"
            {
       yylhs.value.as < std::vector<ExprAST*> > ().emplace_back(yystack_[0].value.as < ExprAST* > ());
     }
#line 1822 "src/parser/parser.cpp"
    break;

  case 63: // paramListPrototype: params
#line 377 "src/parser/parser.yy"
                  {
	     for (const auto elt: yystack_[0].value.as < std::vector<std::string> > ())
	         yylhs.value.as < std::vector<std::string> > ().emplace_back(elt);
	  }
#line 1831 "src/parser/parser.cpp"
    break;

  case 64: // params: params COMMA "type"
#line 383 "src/parser/parser.yy"
                               {
	 for(const auto elt: yystack_[2].value.as < std::vector<std::string> > ())
	    yylhs.value.as < std::vector<std::string> > ().emplace_back(elt);
	 yylhs.value.as < std::vector<std::string> > ().emplace_back(yystack_[0].value.as < std::string > ());
       }
#line 1841 "src/parser/parser.cpp"
    break;

  case 65: // params: "type"
#line 388 "src/parser/parser.yy"
                   {
       yylhs.value.as < std::vector<std::string> > ().emplace_back(yystack_[0].value.as < std::string > ());
       }
#line 1849 "src/parser/parser.cpp"
    break;

  case 66: // paramList: %empty
#line 393 "src/parser/parser.yy"
                 {
	 }
#line 1856 "src/parser/parser.cpp"
    break;

  case 67: // paramList: parameters
#line 395 "src/parser/parser.yy"
                      {
	   for(const auto elt: yystack_[0].value.as < std::vector<STAB::VariableDeclExprAST*> > ())
	     yylhs.value.as < std::vector<STAB::VariableDeclExprAST*> > ().emplace_back(elt);
	 }
#line 1865 "src/parser/parser.cpp"
    break;

  case 68: // parameters: parameters COMMA "type" "identifier"
#line 401 "src/parser/parser.yy"
                                          {
	      for(const auto elt: yystack_[3].value.as < std::vector<STAB::VariableDeclExprAST*> > ()){
	         yylhs.value.as < std::vector<STAB::VariableDeclExprAST*> > ().emplace_back(elt);
		  }
          auto decl = new VariableDeclExprAST(yystack_[1].value.as < std::string > (), yystack_[0].value.as < std::string > (), {yystack_[1].location.first, yystack_[0].location.first});
	      yylhs.value.as < std::vector<STAB::VariableDeclExprAST*> > ().emplace_back(decl);
	  }
#line 1877 "src/parser/parser.cpp"
    break;

  case 69: // parameters: "type" "identifier"
#line 408 "src/parser/parser.yy"
                         {
	     auto decl = new VariableDeclExprAST(yystack_[1].value.as < std::string > (), yystack_[0].value.as < std::string > (), {yystack_[1].location.first, yystack_[0].location.first});
	     yylhs.value.as < std::vector<STAB::VariableDeclExprAST*> > ().emplace_back(decl);
	  }
#line 1886 "src/parser/parser.cpp"
    break;

  case 70: // fnCallStmt: "identifier" LBRACE argList RBRACE SEMI_COLON
#line 413 "src/parser/parser.yy"
                                                {
     std::vector<STAB::ExprAST*> Args;
     for (const auto elt: yystack_[2].value.as < std::vector<ExprAST*> > ()){
         Args.emplace_back(elt);
       }
      yylhs.value.as < StatementAST* > () = new CallStatementAST(yystack_[4].value.as < std::string > (), Args, {yystack_[4].location.first, yystack_[0].location.first});
    }
#line 1898 "src/parser/parser.cpp"
    break;

  case 71: // fnCall: "identifier" LBRACE argList RBRACE
#line 421 "src/parser/parser.yy"
                                 {
   std::vector<STAB::ExprAST*> Args;
   for (const auto elt: yystack_[1].value.as < std::vector<ExprAST*> > ()){
      Args.emplace_back(elt);
   }
   yylhs.value.as < CallExprAST* > () = new CallExprAST(yystack_[3].value.as < std::string > (), Args, {yystack_[3].location.first, yystack_[0].location.first});
 }
#line 1910 "src/parser/parser.cpp"
    break;


#line 1914 "src/parser/parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  const char *
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    static const char *const yy_sname[] =
    {
    "end of file", "error", "invalid token", "LBRACE", "RBRACE", "LCURLY",
  "RCURLY", "LBIG", "RBIG", "ASSIGN", "IF", "ELSE", "ELSE_IF", "LOOP",
  "FOR", "WHILE", "AND", "OR", "XOR", "MATCH", "IMPORT", "IN", "TO",
  "COMMA", "FN_ARROW", "MATCH_ARROW", "RETURN", "BREAK", "SKIP",
  "SEMI_COLON", "PLUS", "MOD", "MINUS", "TIMES", "DIV", "GT", "LT", "GE",
  "LE", "NE", "op", "identifier", "type", "num", "str", "FN", "$accept",
  "functionDefinition", "functionPrototype", "varDeclaration",
  "varInitialization", "arrayDecl", "arrayAssign", "arrayRef", "loop",
  "range", "for", "while", "program", "stmts", "stmt", "expr",
  "assignExpr", "returnStmt", "breakStmt", "skipStmt", "elseStmt",
  "elseifStmt", "ifStmt", "ifLadder", "argList", "args",
  "paramListPrototype", "params", "paramList", "parameters", "fnCallStmt",
  "fnCall", YY_NULLPTR
    };
    return yy_sname[yysymbol];
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -38;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
     -38,    14,    -5,   -38,     3,    -3,   -21,     3,     3,    -1,
       0,     9,   -11,    -9,   -38,   -38,   -38,   -38,   -38,   -38,
     -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,    22,   -38,
     -38,     3,    12,   -38,   -38,   -38,   223,   -38,   -38,    17,
     234,   247,   -38,   -38,     3,     3,     3,     4,    32,     3,
      28,   212,     3,     3,   -38,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,    64,     3,   -38,   -38,
     391,    39,    25,   281,   356,     3,     3,   -38,     8,   270,
      57,   -38,   -38,    69,   314,    97,   257,    29,   257,   194,
     194,   -15,   -15,   -15,   -15,   -38,   -38,   -38,    76,   344,
     107,    53,     3,    74,   -38,   325,   368,    43,    81,    63,
      83,    65,   -38,   -38,   -38,   -38,   -38,   -38,     3,   -38,
     -38,   391,     3,    60,   -38,   -38,    70,    51,     2,    54,
     130,   140,   163,   391,   380,   -38,    55,   -38,   -38,    58,
      61,    22,   -38,   -38,   -38,    66,   173,    94,   -38,   -38,
     -38,   -38,   -38,   196,   -38
  };

  const signed char
  Parser::yydefact_[] =
  {
      16,     0,    14,     1,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    17,    27,    21,    22,    30,    31,
      18,    19,    20,    15,    23,    26,    24,    25,    55,    29,
      28,     0,    45,    46,    44,    48,     0,    47,    16,     0,
       0,     0,    51,    52,    59,     0,     0,     0,     0,     0,
      53,     0,    59,     0,    16,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    16,    50,
      62,     0,    60,     0,     0,     0,     0,     5,    66,     0,
       0,    58,    37,     0,     0,     0,    32,    36,    33,    34,
      35,    38,    39,    41,    40,    43,    42,    10,     0,     0,
       0,     0,     0,     0,    49,     0,     0,    65,     0,    63,
       0,    67,    16,    16,    71,     9,    57,    16,     0,    13,
      70,    61,     0,     0,     6,    69,     0,     0,     0,     0,
       0,     0,     0,    11,     0,     7,     0,    64,    16,     0,
       0,    55,    54,    12,     8,     0,     0,     0,    68,    56,
       4,     3,    16,     0,     2
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,
     -38,   -38,   -38,   -37,   -38,    -4,   -38,   -38,   -38,   -38,
     -38,   -33,   -38,   -38,    52,   -38,   -38,   -38,   -38,   -38,
     -38,   -38
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    35,    20,    98,
      21,    22,     1,     2,    23,    70,    24,    25,    26,    27,
      81,    50,    28,    29,    71,    72,   108,   109,   110,   111,
      30,    37
  };

  const unsigned char
  Parser::yytable_[] =
  {
      36,    66,    38,    40,    41,     4,    31,   138,     5,     6,
       7,    75,    44,    76,     3,    52,    45,    85,    46,    53,
      39,     8,     9,    10,    64,    65,   139,    51,    42,    43,
      47,   100,    48,    77,    49,    78,    11,    12,    67,    80,
      13,    73,    74,   101,    32,    79,    33,    34,   102,    84,
     107,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,   113,    99,    60,    61,    62,    63,    64,    65,
      97,   105,   106,   114,     4,   130,   131,     5,     6,     7,
     132,   117,   120,   122,   125,   126,   127,   128,   129,   135,
       8,     9,    10,   137,   136,   150,   140,   145,   121,   152,
     147,   146,   148,   116,    83,    11,    12,     4,   149,    13,
       5,     6,     7,   119,   133,   153,     0,     4,   134,     0,
       5,     6,     7,     8,     9,    10,     0,     0,     0,     0,
       0,     0,     0,     8,     9,    10,   141,     0,    11,    12,
       4,     0,    13,     5,     6,     7,   142,     0,    11,    12,
       4,     0,    13,     5,     6,     7,     8,     9,    10,     0,
       0,     0,     0,     0,     0,     0,     8,     9,    10,   143,
       0,    11,    12,     4,     0,    13,     5,     6,     7,   151,
       0,    11,    12,     4,     0,    13,     5,     6,     7,     8,
       9,    10,     0,     0,     0,     0,     0,     0,     0,     8,
       9,    10,   154,     0,    11,    12,     4,     0,    13,     5,
       6,     7,     0,     0,    11,    12,    82,     0,    13,     0,
       0,     0,     8,     9,    10,    56,     0,     0,    54,    60,
      61,    62,    63,    64,    65,     0,     0,    11,    12,    68,
       0,    13,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,   112,    69,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    56,   103,
      58,    59,    60,    61,    62,    63,    64,    65,     0,     0,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,   115,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   123,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,   118,     0,     0,     0,
       0,     0,     0,     0,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,   104,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,   124,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,   144,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65
  };

  const short
  Parser::yycheck_[] =
  {
       4,    38,     5,     7,     8,    10,     3,     5,    13,    14,
      15,     7,     3,     9,     0,     3,     7,    54,     9,     7,
      41,    26,    27,    28,    39,    40,    24,    31,    29,    29,
      41,    68,    41,    29,    12,     3,    41,    42,    21,    11,
      45,    45,    46,     4,    41,    49,    43,    44,    23,    53,
      42,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,     5,    67,    35,    36,    37,    38,    39,    40,
       6,    75,    76,     4,    10,   112,   113,    13,    14,    15,
     117,     5,    29,     9,    41,     4,    23,     4,    23,    29,
      26,    27,    28,    42,    24,    29,    42,    42,   102,     5,
      42,   138,    41,     6,    52,    41,    42,    10,   141,    45,
      13,    14,    15,     6,   118,   152,    -1,    10,   122,    -1,
      13,    14,    15,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    27,    28,     6,    -1,    41,    42,
      10,    -1,    45,    13,    14,    15,     6,    -1,    41,    42,
      10,    -1,    45,    13,    14,    15,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,     6,
      -1,    41,    42,    10,    -1,    45,    13,    14,    15,     6,
      -1,    41,    42,    10,    -1,    45,    13,    14,    15,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      27,    28,     6,    -1,    41,    42,    10,    -1,    45,    13,
      14,    15,    -1,    -1,    41,    42,     4,    -1,    45,    -1,
      -1,    -1,    26,    27,    28,    31,    -1,    -1,     5,    35,
      36,    37,    38,    39,    40,    -1,    -1,    41,    42,     5,
      -1,    45,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,     5,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    31,     8,
      33,    34,    35,    36,    37,    38,    39,    40,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    58,    59,     0,    10,    13,    14,    15,    26,    27,
      28,    41,    42,    45,    47,    48,    49,    50,    51,    52,
      54,    56,    57,    60,    62,    63,    64,    65,    68,    69,
      76,     3,    41,    43,    44,    53,    61,    77,     5,    41,
      61,    61,    29,    29,     3,     7,     9,    41,    41,    12,
      67,    61,     3,     7,     5,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    59,    21,     5,    29,
      61,    70,    71,    61,    61,     7,     9,    29,     3,    61,
      11,    66,     4,    70,    61,    59,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,     6,    55,    61,
      59,     4,    23,     8,    29,    61,    61,    42,    72,    73,
      74,    75,     5,     5,     4,     8,     6,     5,    22,     6,
      29,    61,     9,     8,    29,    41,     4,    23,     4,    23,
      59,    59,    59,    61,    61,    29,    24,    42,     5,    24,
      42,     6,     6,     6,    29,    42,    59,    42,    41,    67,
      29,     6,     5,    59,     6
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    46,    47,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    59,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    62,
      63,    64,    65,    66,    66,    67,    67,    68,    69,    70,
      70,    71,    71,    72,    73,    73,    74,    74,    75,    75,
      76,    77
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,    10,     8,     8,     3,     5,     6,     7,     4,
       4,     3,     7,     5,     1,     2,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     4,
       3,     2,     2,     0,     4,     0,     6,     5,     3,     0,
       1,     3,     1,     1,     3,     1,     0,     1,     4,     2,
       5,     4
  };




#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   101,   101,   115,   129,   138,   142,   151,   156,   161,
     166,   171,   177,   184,   189,   204,   208,   214,   217,   220,
     223,   226,   229,   232,   235,   236,   237,   240,   243,   246,
     249,   252,   257,   260,   263,   266,   269,   272,   275,   278,
     281,   284,   287,   290,   293,   302,   305,   309,   312,   317,
     322,   327,   331,   335,   338,   343,   344,   349,   353,   358,
     360,   367,   372,   377,   383,   388,   393,   395,   401,   408,
     413,   421
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    return static_cast<symbol_kind_type> (t);
  }

#line 22 "src/parser/parser.yy"
} // STAB
#line 2503 "src/parser/parser.cpp"

#line 429 "src/parser/parser.yy"


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

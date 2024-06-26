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
#line 39 "src/parser/parser.yy"

  #include "../lexer/lexer.hpp"
  #include "../globals.h"
  #include "../includes/highlight-term.hpp"
  namespace STAB {
    template <typename RHS>
    void calcLocation(location& current, const RHS& rhs, const std::size_t n);
  }
  #define YYLLOC_DEFAULT(Cur, Rhs, N) calcLocation(Cur, Rhs, N)
  #define yylex lexer.yylex

#line 58 "src/parser/parser.cpp"


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

#line 17 "src/parser/parser.yy"
namespace STAB {
#line 151 "src/parser/parser.cpp"

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
#line 33 "src/parser/parser.yy"
{
  #if YYDEBUG != 0 
    set_debug_level(debug);
  #endif
}

#line 1049 "src/parser/parser.cpp"


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
#line 89 "src/parser/parser.yy"
                                                                                         {
			auto fnScope = new Scope(currentScope, yystack_[8].value.as < std::string > ());
			currentScope = fnScope;
                        std::vector<std::string> argTypes;
			std::vector<STAB::VariableDeclExprAST*> declVars;
                        for(const auto elt: yystack_[6].value.as < std::vector<STAB::VariableDeclExprAST*> > ()){
			  argTypes.emplace_back(elt->getType());
			  declVars.emplace_back(elt);
			}
			auto proto = new STAB::PrototypeAST(yystack_[3].value.as < std::string > (), yystack_[8].value.as < std::string > (), argTypes);
			yylhs.value.as < StatementAST* > () = new STAB::FunctionAST(proto,declVars, yystack_[1].value.as < std::vector<StatementAST*> > (), fnScope);
			currentScope = globalScope;
                    }
#line 1287 "src/parser/parser.cpp"
    break;

  case 3: // functionDefinition: FN "identifier" LBRACE paramList RBRACE LCURLY stmts RCURLY
#line 103 "src/parser/parser.yy"
                                                                       {               
                        auto fnScope = new Scope(currentScope, yystack_[6].value.as < std::string > ());
			currentScope = fnScope;
                        std::vector<std::string> argTypes;
			std::vector<STAB::VariableDeclExprAST*> declVars;
                        for(const auto elt: yystack_[4].value.as < std::vector<STAB::VariableDeclExprAST*> > ()){
			  argTypes.emplace_back(elt->getType());
			  declVars.emplace_back(elt);
			}
			auto proto = new STAB::PrototypeAST("void", yystack_[6].value.as < std::string > (), argTypes);
			yylhs.value.as < StatementAST* > () = new STAB::FunctionAST(proto,declVars, yystack_[1].value.as < std::vector<StatementAST*> > (), fnScope);
			currentScope = globalScope;
                     }
#line 1305 "src/parser/parser.cpp"
    break;

  case 4: // functionPrototype: FN "identifier" LBRACE paramListPrototype RBRACE FN_ARROW "type" SEMI_COLON
#line 117 "src/parser/parser.yy"
                                                                                         {
                       std::vector<std::string> Args;
		       for(const auto elt: yystack_[4].value.as < std::vector<std::string> > ()){
		         Args.emplace_back(elt);
		       }
                       yylhs.value.as < StatementAST* > () = new STAB::PrototypeAST(yystack_[1].value.as < std::string > (), yystack_[6].value.as < std::string > (), Args);
                   }
#line 1317 "src/parser/parser.cpp"
    break;

  case 5: // varDeclaration: "type" "identifier" SEMI_COLON
#line 126 "src/parser/parser.yy"
                                         {
                  yylhs.value.as < StatementAST* > () = new STAB::VariableDeclExprAST(yystack_[2].value.as < std::string > (), yystack_[1].value.as < std::string > ());
                }
#line 1325 "src/parser/parser.cpp"
    break;

  case 6: // varInitialization: "type" "identifier" ASSIGN expr SEMI_COLON
#line 130 "src/parser/parser.yy"
                                                        {
                     auto type = yystack_[4].value.as < std::string > ();
		     auto name = yystack_[3].value.as < std::string > ();
		     auto val = yystack_[1].value.as < ExprAST* > ();
		     auto varDecl = new VariableDeclExprAST(type, name);
		     yylhs.value.as < STAB::VariableDeclAssignExprAST* > () = new VariableDeclAssignExprAST(varDecl, val);
		  }
#line 1337 "src/parser/parser.cpp"
    break;

  case 7: // arrayDecl: "type" "identifier" LBIG expr RBIG SEMI_COLON
#line 139 "src/parser/parser.yy"
                                                  {
              yylhs.value.as < STAB::ArrayAST* > () = new ArrayAST(yystack_[5].value.as < std::string > (), yystack_[4].value.as < std::string > (), yystack_[2].value.as < ExprAST* > ());
          }
#line 1345 "src/parser/parser.cpp"
    break;

  case 8: // arrayAssign: "identifier" LBIG expr RBIG ASSIGN expr SEMI_COLON
#line 144 "src/parser/parser.yy"
                                                      {
              yylhs.value.as < STAB::ArrayAssignAST* > () = new ArrayAssignAST(yystack_[6].value.as < std::string > (), yystack_[4].value.as < ExprAST* > (), yystack_[1].value.as < ExprAST* > ());
            }
#line 1353 "src/parser/parser.cpp"
    break;

  case 9: // arrayRef: "identifier" LBIG expr RBIG
#line 149 "src/parser/parser.yy"
                             {
           yylhs.value.as < STAB::ArrayRefAST* > () = new ArrayRefAST(yystack_[3].value.as < std::string > (), yystack_[1].value.as < ExprAST* > ());
         }
#line 1361 "src/parser/parser.cpp"
    break;

  case 10: // loop: LOOP LCURLY stmts RCURLY
#line 154 "src/parser/parser.yy"
                               {
       yylhs.value.as < StatementAST* > () = new LoopStatementAST(yystack_[1].value.as < std::vector<StatementAST*> > ());

     }
#line 1370 "src/parser/parser.cpp"
    break;

  case 11: // range: expr TO expr
#line 159 "src/parser/parser.yy"
                    {
        yylhs.value.as < STAB::RangeStatementAST* > () = new RangeStatementAST(yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > ()); 
      }
#line 1378 "src/parser/parser.cpp"
    break;

  case 12: // for: FOR "identifier" IN range LCURLY stmts RCURLY
#line 164 "src/parser/parser.yy"
                                          {
        std::string type = "int";
	auto varDecl = new VariableDeclExprAST(type, yystack_[5].value.as < std::string > ());
        yylhs.value.as < StatementAST* > () = new ForStatementAST(varDecl, yystack_[3].value.as < STAB::RangeStatementAST* > (), yystack_[1].value.as < std::vector<StatementAST*> > ());
     }
#line 1388 "src/parser/parser.cpp"
    break;

  case 13: // while: WHILE expr LCURLY stmts RCURLY
#line 171 "src/parser/parser.yy"
                                      {
       yylhs.value.as < StatementAST* > () = new WhileStatementAST(yystack_[3].value.as < ExprAST* > (), yystack_[1].value.as < std::vector<StatementAST*> > ());

      }
#line 1397 "src/parser/parser.cpp"
    break;

  case 14: // program: stmts
#line 176 "src/parser/parser.yy"
              {
       std::vector<std::string> Args;
       std::vector<STAB::VariableDeclExprAST*> declVars;

       std::vector<STAB::StatementAST*> stmts;

       auto proto = new PrototypeAST("void", "__start__", Args);

       yylhs.value.as < std::vector<StatementAST*> > () = yystack_[0].value.as < std::vector<StatementAST*> > ();

       __start__fn = new FunctionAST(proto, declVars, stmts, globalScope);

       for (const auto stmt: yystack_[0].value.as < std::vector<StatementAST*> > ())
           __start__fn->getBody().emplace_back(stmt);
       }
#line 1417 "src/parser/parser.cpp"
    break;

  case 15: // stmts: stmts stmt
#line 191 "src/parser/parser.yy"
                 {
       yystack_[1].value.as < std::vector<StatementAST*> > ().emplace_back(yystack_[0].value.as < StatementAST* > ());
       yylhs.value.as < std::vector<StatementAST*> > () = yystack_[1].value.as < std::vector<StatementAST*> > ();
     }
#line 1426 "src/parser/parser.cpp"
    break;

  case 16: // stmts: %empty
#line 195 "src/parser/parser.yy"
              {
       yylhs.value.as < std::vector<StatementAST*> > () = std::vector<STAB::StatementAST*>();
     }
#line 1434 "src/parser/parser.cpp"
    break;

  case 17: // stmt: functionDefinition
#line 201 "src/parser/parser.yy"
                        {
        yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > ();
      }
#line 1442 "src/parser/parser.cpp"
    break;

  case 18: // stmt: loop
#line 204 "src/parser/parser.yy"
            {
        yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > ();
      }
#line 1450 "src/parser/parser.cpp"
    break;

  case 19: // stmt: for
#line 207 "src/parser/parser.yy"
           {
        yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > ();
      }
#line 1458 "src/parser/parser.cpp"
    break;

  case 20: // stmt: while
#line 210 "src/parser/parser.yy"
              {
         yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > ();
      }
#line 1466 "src/parser/parser.cpp"
    break;

  case 21: // stmt: varDeclaration
#line 213 "src/parser/parser.yy"
                      {
        yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > ();
      }
#line 1474 "src/parser/parser.cpp"
    break;

  case 22: // stmt: varInitialization
#line 216 "src/parser/parser.yy"
                         {
         yylhs.value.as < StatementAST* > () = yystack_[0].value.as < STAB::VariableDeclAssignExprAST* > ();
      }
#line 1482 "src/parser/parser.cpp"
    break;

  case 23: // stmt: assignExpr
#line 219 "src/parser/parser.yy"
                  {
         yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > ();
      }
#line 1490 "src/parser/parser.cpp"
    break;

  case 26: // stmt: returnStmt
#line 224 "src/parser/parser.yy"
                  {
          yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > (); 
      }
#line 1498 "src/parser/parser.cpp"
    break;

  case 27: // stmt: functionPrototype
#line 227 "src/parser/parser.yy"
                          {
        yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > ();
      }
#line 1506 "src/parser/parser.cpp"
    break;

  case 28: // stmt: fnCallStmt
#line 230 "src/parser/parser.yy"
                   {
         yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > (); 
      }
#line 1514 "src/parser/parser.cpp"
    break;

  case 29: // stmt: ifLadder
#line 233 "src/parser/parser.yy"
                {
         yylhs.value.as < StatementAST* > () = yystack_[0].value.as < StatementAST* > ();
      }
#line 1522 "src/parser/parser.cpp"
    break;

  case 30: // stmt: arrayDecl
#line 236 "src/parser/parser.yy"
                  {
         yylhs.value.as < StatementAST* > () = yystack_[0].value.as < STAB::ArrayAST* > ();
      }
#line 1530 "src/parser/parser.cpp"
    break;

  case 31: // stmt: arrayAssign
#line 239 "src/parser/parser.yy"
                    {
         yylhs.value.as < StatementAST* > () = yystack_[0].value.as < STAB::ArrayAssignAST* > ();
      }
#line 1538 "src/parser/parser.cpp"
    break;

  case 32: // expr: expr PLUS expr
#line 244 "src/parser/parser.yy"
                      {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > ());
      }
#line 1546 "src/parser/parser.cpp"
    break;

  case 33: // expr: expr MINUS expr
#line 247 "src/parser/parser.yy"
                       {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > ());
     }
#line 1554 "src/parser/parser.cpp"
    break;

  case 34: // expr: expr TIMES expr
#line 250 "src/parser/parser.yy"
                       {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > ());
     }
#line 1562 "src/parser/parser.cpp"
    break;

  case 35: // expr: expr DIV expr
#line 253 "src/parser/parser.yy"
                     {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > ());
     }
#line 1570 "src/parser/parser.cpp"
    break;

  case 36: // expr: expr MOD expr
#line 256 "src/parser/parser.yy"
                     {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > ());
     }
#line 1578 "src/parser/parser.cpp"
    break;

  case 37: // expr: LBRACE expr RBRACE
#line 259 "src/parser/parser.yy"
                          {
        yylhs.value.as < ExprAST* > () = yystack_[1].value.as < ExprAST* > (); 
     }
#line 1586 "src/parser/parser.cpp"
    break;

  case 38: // expr: expr GT expr
#line 262 "src/parser/parser.yy"
                    {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > ());
     }
#line 1594 "src/parser/parser.cpp"
    break;

  case 39: // expr: expr LT expr
#line 265 "src/parser/parser.yy"
                    {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > ());
     }
#line 1602 "src/parser/parser.cpp"
    break;

  case 40: // expr: expr LE expr
#line 268 "src/parser/parser.yy"
                    {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > ());
     }
#line 1610 "src/parser/parser.cpp"
    break;

  case 41: // expr: expr GE expr
#line 271 "src/parser/parser.yy"
                   {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > ());
     }
#line 1618 "src/parser/parser.cpp"
    break;

  case 42: // expr: expr "op" expr
#line 274 "src/parser/parser.yy"
                   {
       yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > ());
     }
#line 1626 "src/parser/parser.cpp"
    break;

  case 43: // expr: expr NE expr
#line 277 "src/parser/parser.yy"
                   {
        yylhs.value.as < ExprAST* > () = new BinaryExprAST(yystack_[1].value.as < std::string > (), yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > ());
     }
#line 1634 "src/parser/parser.cpp"
    break;

  case 44: // expr: "str"
#line 280 "src/parser/parser.yy"
              {
        std::string val = yystack_[0].value.as < std::string > ();
	auto length = val.length();
	std::string without_quotation;
	for(int i = 1; i < length - 1 ; ++i){
	 without_quotation += val[i];
	}
	yylhs.value.as < ExprAST* > () = new StringExprAST(without_quotation);
     }
#line 1648 "src/parser/parser.cpp"
    break;

  case 45: // expr: "identifier"
#line 289 "src/parser/parser.yy"
          {
       yylhs.value.as < ExprAST* > () = new VariableExprAST(yystack_[0].value.as < std::string > ());
     }
#line 1656 "src/parser/parser.cpp"
    break;

  case 46: // expr: "num"
#line 292 "src/parser/parser.yy"
              {
        auto val = std::stoi(yystack_[0].value.as < std::string > ());
        yylhs.value.as < ExprAST* > () = new NumberExprAST(val);
     }
#line 1665 "src/parser/parser.cpp"
    break;

  case 47: // expr: fnCall
#line 296 "src/parser/parser.yy"
              {
        yylhs.value.as < ExprAST* > () = new CallExprAST(yystack_[0].value.as < CallExprAST* > ()->getFnName(), yystack_[0].value.as < CallExprAST* > ()->getArgs());
     }
#line 1673 "src/parser/parser.cpp"
    break;

  case 48: // expr: arrayRef
#line 299 "src/parser/parser.yy"
                {
        yylhs.value.as < ExprAST* > () = yystack_[0].value.as < STAB::ArrayRefAST* > ();
     }
#line 1681 "src/parser/parser.cpp"
    break;

  case 49: // assignExpr: "identifier" ASSIGN expr SEMI_COLON
#line 304 "src/parser/parser.yy"
                                                   {
             yylhs.value.as < StatementAST* > () = new VariableAssignExprAST(yystack_[3].value.as < std::string > (), yystack_[1].value.as < ExprAST* > ());
           }
#line 1689 "src/parser/parser.cpp"
    break;

  case 50: // returnStmt: RETURN expr SEMI_COLON
#line 309 "src/parser/parser.yy"
                                   {
              yylhs.value.as < StatementAST* > () = new ReturnStmtAST(yystack_[1].value.as < ExprAST* > ());
           }
#line 1697 "src/parser/parser.cpp"
    break;

  case 53: // elseStmt: %empty
#line 318 "src/parser/parser.yy"
                 {
          yylhs.value.as < STAB::ElseStatementAST* > () = nullptr;
         }
#line 1705 "src/parser/parser.cpp"
    break;

  case 54: // elseStmt: ELSE LCURLY stmts RCURLY
#line 321 "src/parser/parser.yy"
                                   {
	    yylhs.value.as < STAB::ElseStatementAST* > () = new ElseStatementAST(yystack_[1].value.as < std::vector<StatementAST*> > ());
	 }
#line 1713 "src/parser/parser.cpp"
    break;

  case 56: // elseifStmt: ELSE_IF expr LCURLY stmts RCURLY elseifStmt
#line 328 "src/parser/parser.yy"
           {
	     yylhs.value.as < STAB::CondStatementAST* > () = nullptr;
	   }
#line 1721 "src/parser/parser.cpp"
    break;

  case 57: // ifStmt: IF expr LCURLY stmts RCURLY
#line 332 "src/parser/parser.yy"
                                     {
	   yylhs.value.as < STAB::CondStatementAST* > () = new CondStatementAST(yystack_[3].value.as < ExprAST* > (), yystack_[1].value.as < std::vector<StatementAST*> > ());
	 }
#line 1729 "src/parser/parser.cpp"
    break;

  case 58: // ifLadder: ifStmt elseifStmt elseStmt
#line 336 "src/parser/parser.yy"
                                     {
            yylhs.value.as < StatementAST* > () = new IfStatementAST(yystack_[2].value.as < STAB::CondStatementAST* > (), nullptr, yystack_[0].value.as < STAB::ElseStatementAST* > ());
         }
#line 1737 "src/parser/parser.cpp"
    break;

  case 59: // argList: %empty
#line 341 "src/parser/parser.yy"
                 {
        }
#line 1744 "src/parser/parser.cpp"
    break;

  case 60: // argList: args
#line 343 "src/parser/parser.yy"
               {
	 for(const auto elt: yystack_[0].value.as < std::vector<ExprAST*> > ()){
	   yylhs.value.as < std::vector<ExprAST*> > ().emplace_back(elt);
	 }
	}
#line 1754 "src/parser/parser.cpp"
    break;

  case 61: // args: args COMMA expr
#line 350 "src/parser/parser.yy"
                       {
       for(const auto elt: yystack_[2].value.as < std::vector<ExprAST*> > ())
           yylhs.value.as < std::vector<ExprAST*> > ().emplace_back(elt);
       yylhs.value.as < std::vector<ExprAST*> > ().emplace_back(yystack_[0].value.as < ExprAST* > ());
     }
#line 1764 "src/parser/parser.cpp"
    break;

  case 62: // args: expr
#line 355 "src/parser/parser.yy"
            {
       yylhs.value.as < std::vector<ExprAST*> > ().emplace_back(yystack_[0].value.as < ExprAST* > ());
     }
#line 1772 "src/parser/parser.cpp"
    break;

  case 63: // paramListPrototype: params
#line 360 "src/parser/parser.yy"
                  {
	     for (const auto elt: yystack_[0].value.as < std::vector<std::string> > ())
	         yylhs.value.as < std::vector<std::string> > ().emplace_back(elt);
	  }
#line 1781 "src/parser/parser.cpp"
    break;

  case 64: // params: params COMMA "type"
#line 366 "src/parser/parser.yy"
                               {
	 for(const auto elt: yystack_[2].value.as < std::vector<std::string> > ())
	    yylhs.value.as < std::vector<std::string> > ().emplace_back(elt);
	 yylhs.value.as < std::vector<std::string> > ().emplace_back(yystack_[0].value.as < std::string > ());
       }
#line 1791 "src/parser/parser.cpp"
    break;

  case 65: // params: "type"
#line 371 "src/parser/parser.yy"
                   {
       yylhs.value.as < std::vector<std::string> > ().emplace_back(yystack_[0].value.as < std::string > ());
       }
#line 1799 "src/parser/parser.cpp"
    break;

  case 66: // paramList: %empty
#line 376 "src/parser/parser.yy"
                 {
	 }
#line 1806 "src/parser/parser.cpp"
    break;

  case 67: // paramList: parameters
#line 378 "src/parser/parser.yy"
                      {
	   for(const auto elt: yystack_[0].value.as < std::vector<STAB::VariableDeclExprAST*> > ())
	     yylhs.value.as < std::vector<STAB::VariableDeclExprAST*> > ().emplace_back(elt);
	 }
#line 1815 "src/parser/parser.cpp"
    break;

  case 68: // parameters: parameters COMMA "type" "identifier"
#line 384 "src/parser/parser.yy"
                                          {
	      for(const auto elt: yystack_[3].value.as < std::vector<STAB::VariableDeclExprAST*> > ())
	         yylhs.value.as < std::vector<STAB::VariableDeclExprAST*> > ().emplace_back(elt);
              auto decl = new VariableDeclExprAST(yystack_[1].value.as < std::string > (), yystack_[0].value.as < std::string > ());
	      yylhs.value.as < std::vector<STAB::VariableDeclExprAST*> > ().emplace_back(decl);
	  }
#line 1826 "src/parser/parser.cpp"
    break;

  case 69: // parameters: "type" "identifier"
#line 390 "src/parser/parser.yy"
                         {
	     auto decl = new VariableDeclExprAST(yystack_[1].value.as < std::string > (), yystack_[0].value.as < std::string > ());
	     yylhs.value.as < std::vector<STAB::VariableDeclExprAST*> > ().emplace_back(decl);
	  }
#line 1835 "src/parser/parser.cpp"
    break;

  case 70: // fnCallStmt: "identifier" LBRACE argList RBRACE SEMI_COLON
#line 395 "src/parser/parser.yy"
                                                {
     std::vector<STAB::ExprAST*> Args;
     for (const auto elt: yystack_[2].value.as < std::vector<ExprAST*> > ()){
         Args.emplace_back(elt);
       }
      yylhs.value.as < StatementAST* > () = new CallStatementAST(yystack_[4].value.as < std::string > (), Args);
    }
#line 1847 "src/parser/parser.cpp"
    break;

  case 71: // fnCall: "identifier" LBRACE argList RBRACE
#line 403 "src/parser/parser.yy"
                                 {
   std::vector<STAB::ExprAST*> Args;
   for (const auto elt: yystack_[1].value.as < std::vector<ExprAST*> > ()){
      Args.emplace_back(elt);
   }
   yylhs.value.as < CallExprAST* > () = new CallExprAST(yystack_[3].value.as < std::string > (), Args);
 }
#line 1859 "src/parser/parser.cpp"
    break;


#line 1863 "src/parser/parser.cpp"

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
  "CONTROL_FLOW", "COMMA", "FN_ARROW", "MATCH_ARROW", "RETURN", "BREAK",
  "SKIP", "SEMI_COLON", "PLUS", "MOD", "MINUS", "TIMES", "DIV", "GT", "LT",
  "GE", "LE", "NE", "op", "identifier", "type", "num", "str", "FN",
  "$accept", "functionDefinition", "functionPrototype", "varDeclaration",
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


  const signed char Parser::yypact_ninf_ = -41;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
     -41,     9,    -3,   -41,     2,    30,   -40,     2,     2,     0,
       6,    25,    -5,    20,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,    26,   -41,
     -41,     2,    92,   -41,   -41,   -41,   217,   -41,   -41,    27,
     228,   328,   -41,   -41,     2,     2,     2,    -1,    47,     2,
      62,   204,     2,     2,   -41,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    64,     2,   -41,   -41,
     375,    78,    70,   262,   340,     2,     2,   -41,    53,   241,
      95,   -41,   -41,    93,   275,    98,    49,    28,    49,   -18,
     -18,   -25,   -25,   -25,   -25,   -41,   -41,   -41,    97,   316,
     118,    73,     2,    96,   -41,   296,   352,    67,   112,    99,
     113,   105,   -41,   -41,   -41,   -41,   -41,   -41,     2,   -41,
     -41,   375,     2,    89,   -41,   -41,   110,    77,     8,    79,
     124,   144,   168,   375,   364,   -41,   100,   -41,   -41,   106,
      94,    26,   -41,   -41,   -41,    91,   178,   137,   -41,   -41,
     -41,   -41,   -41,   188,   -41
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
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -37,   -41,    -4,   -41,   -41,   -41,   -41,
     -41,     7,   -41,   -41,   103,   -41,   -41,   -41,   -41,   -41,
     -41,   -41
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
      36,    66,    39,    40,    41,    31,    75,     4,    76,     3,
       5,     6,     7,   138,    56,    64,    65,    85,    60,    61,
      62,    63,    64,    65,     8,     9,    10,    51,    44,    77,
      42,   100,    45,   139,    46,    38,    43,    47,    49,    11,
      12,    73,    74,    13,    32,    79,    33,    34,    67,    84,
      78,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    48,    99,    60,    61,    62,    63,    64,    65,
      97,   105,   106,    80,     4,   130,   131,     5,     6,     7,
     132,    56,   101,    58,    59,    60,    61,    62,    63,    64,
      65,     8,     9,    10,   102,    52,   107,   114,   121,    53,
     113,   146,   117,   120,   116,   122,    11,    12,     4,   125,
      13,     5,     6,     7,   133,   153,   126,   128,   134,   135,
     137,   150,   140,   127,   119,     8,     9,    10,     4,   129,
     141,     5,     6,     7,     4,   136,   148,     5,     6,     7,
      11,    12,   152,   145,    13,     8,     9,    10,   149,   147,
     142,     8,     9,    10,     4,    83,     0,     5,     6,     7,
      11,    12,     0,     0,    13,     0,    11,    12,     0,     0,
      13,     8,     9,    10,   143,     0,     0,     0,     4,     0,
       0,     5,     6,     7,   151,     0,    11,    12,     4,     0,
      13,     5,     6,     7,   154,     8,     9,    10,     4,     0,
       0,     5,     6,     7,     0,     8,     9,    10,    82,     0,
      11,    12,     0,     0,    13,     8,     9,    10,     0,     0,
      11,    12,    54,     0,    13,     0,     0,     0,     0,     0,
      11,    12,     0,    68,    13,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,   112,     0,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
     103,     0,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,   115,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,   123,     0,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,   118,     0,
       0,     0,     0,     0,     0,     0,     0,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    69,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
     104,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,   124,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,   144,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65
  };

  const short
  Parser::yycheck_[] =
  {
       4,    38,    42,     7,     8,     3,     7,    10,     9,     0,
      13,    14,    15,     5,    32,    40,    41,    54,    36,    37,
      38,    39,    40,    41,    27,    28,    29,    31,     3,    30,
      30,    68,     7,    25,     9,     5,    30,    42,    12,    42,
      43,    45,    46,    46,    42,    49,    44,    45,    21,    53,
       3,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    42,    67,    36,    37,    38,    39,    40,    41,
       6,    75,    76,    11,    10,   112,   113,    13,    14,    15,
     117,    32,     4,    34,    35,    36,    37,    38,    39,    40,
      41,    27,    28,    29,    24,     3,    43,     4,   102,     7,
       5,   138,     5,    30,     6,     9,    42,    43,    10,    42,
      46,    13,    14,    15,   118,   152,     4,     4,   122,    30,
      43,    30,    43,    24,     6,    27,    28,    29,    10,    24,
       6,    13,    14,    15,    10,    25,    42,    13,    14,    15,
      42,    43,     5,    43,    46,    27,    28,    29,   141,    43,
       6,    27,    28,    29,    10,    52,    -1,    13,    14,    15,
      42,    43,    -1,    -1,    46,    -1,    42,    43,    -1,    -1,
      46,    27,    28,    29,     6,    -1,    -1,    -1,    10,    -1,
      -1,    13,    14,    15,     6,    -1,    42,    43,    10,    -1,
      46,    13,    14,    15,     6,    27,    28,    29,    10,    -1,
      -1,    13,    14,    15,    -1,    27,    28,    29,     4,    -1,
      42,    43,    -1,    -1,    46,    27,    28,    29,    -1,    -1,
      42,    43,     5,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      42,    43,    -1,     5,    46,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,     5,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
       8,    -1,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,     8,    -1,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    59,    60,     0,    10,    13,    14,    15,    27,    28,
      29,    42,    43,    46,    48,    49,    50,    51,    52,    53,
      55,    57,    58,    61,    63,    64,    65,    66,    69,    70,
      77,     3,    42,    44,    45,    54,    62,    78,     5,    42,
      62,    62,    30,    30,     3,     7,     9,    42,    42,    12,
      68,    62,     3,     7,     5,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    60,    21,     5,    30,
      62,    71,    72,    62,    62,     7,     9,    30,     3,    62,
      11,    67,     4,    71,    62,    60,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,     6,    56,    62,
      60,     4,    24,     8,    30,    62,    62,    43,    73,    74,
      75,    76,     5,     5,     4,     8,     6,     5,    22,     6,
      30,    62,     9,     8,    30,    42,     4,    24,     4,    24,
      60,    60,    60,    62,    62,    30,    25,    43,     5,    25,
      43,     6,     6,     6,    30,    43,    60,    43,    42,    68,
      30,     6,     5,    60,     6
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    47,    48,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    60,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    63,
      64,    65,    66,    67,    67,    68,    68,    69,    70,    71,
      71,    72,    72,    73,    74,    74,    75,    75,    76,    76,
      77,    78
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
       0,    89,    89,   103,   117,   126,   130,   139,   144,   149,
     154,   159,   164,   171,   176,   191,   195,   201,   204,   207,
     210,   213,   216,   219,   222,   223,   224,   227,   230,   233,
     236,   239,   244,   247,   250,   253,   256,   259,   262,   265,
     268,   271,   274,   277,   280,   289,   292,   296,   299,   304,
     309,   314,   316,   318,   321,   326,   327,   332,   336,   341,
     343,   350,   355,   360,   366,   371,   376,   378,   384,   390,
     395,   403
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

#line 17 "src/parser/parser.yy"
} // STAB
#line 2448 "src/parser/parser.cpp"

#line 411 "src/parser/parser.yy"


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

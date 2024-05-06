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
#line 35 "src/parser/parser.yy"

  #include "../lexer/lexer.hpp"
  #include "../includes/scope.h"
  namespace STAB {
    template <typename RHS>
    void calcLocation(location& current, const RHS& rhs, const std::size_t n);
  }
  #define YYLLOC_DEFAULT(Cur, Rhs, N) calcLocation(Cur, Rhs, N)
  #define yylex lexer.yylex

  // we need at least a scope at the beginning
  auto globalScope = new Scope();
  // global scope is the current scope initially
  auto currentScope = globalScope;

#line 62 "src/parser/parser.cpp"


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

#line 13 "src/parser/parser.yy"
namespace STAB {
#line 155 "src/parser/parser.cpp"

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
      case symbol_kind::S_ID: // "identifier"
      case symbol_kind::S_DATA_TYPE: // "type"
        value.copy< std::string > (YY_MOVE (that.value));
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
      case symbol_kind::S_ID: // "identifier"
      case symbol_kind::S_DATA_TYPE: // "type"
        value.move< std::string > (YY_MOVE (s.value));
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
      case symbol_kind::S_ID: // "identifier"
      case symbol_kind::S_DATA_TYPE: // "type"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
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
      case symbol_kind::S_ID: // "identifier"
      case symbol_kind::S_DATA_TYPE: // "type"
        value.move< std::string > (YY_MOVE (that.value));
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
      case symbol_kind::S_ID: // "identifier"
      case symbol_kind::S_DATA_TYPE: // "type"
        value.copy< std::string > (that.value);
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
      case symbol_kind::S_ID: // "identifier"
      case symbol_kind::S_DATA_TYPE: // "type"
        value.move< std::string > (that.value);
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
#line 29 "src/parser/parser.yy"
{
  #if YYDEBUG != 0 
    set_debug_level(debug);
  #endif
}

#line 549 "src/parser/parser.cpp"


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
      case symbol_kind::S_ID: // "identifier"
      case symbol_kind::S_DATA_TYPE: // "type"
        yylhs.value.emplace< std::string > ();
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
  case 2: // functionPrototype: FN "identifier" LBRACE paramList RBRACE FN_ARROW "type" SEMI_COLON
#line 67 "src/parser/parser.yy"
                                                                               {
                    if (currentScope != globalScope){
		      std::cout << "Error: A function can only be withing a global scope\n"; 
		    } else {
		      if (currentScope->FnExists(yystack_[6].value.as < std::string > ())){
		        std::cout << "Error: The function " << yystack_[6].value.as < std::string > () << " is already defined\n"; 
		      } else{
		       // todo: read args and add into the map.
		       std::map<std::string, std::string> dummy;
		       currentScope->installFn(yystack_[6].value.as < std::string > (),yystack_[1].value.as < std::string > (), dummy);
                       std::cout << "Function Prototype of name: " << yystack_[6].value.as < std::string > () << '\n';
		      }
		     }
                   }
#line 704 "src/parser/parser.cpp"
    break;

  case 3: // functionDefinition: FN "identifier" LBRACE paramList RBRACE FN_ARROW "type" LCURLY stmt RCURLY
#line 82 "src/parser/parser.yy"
                                                                                        {
                      std::cout << "A function " << yystack_[8].value.as < std::string > () << " was parsed with the return type " << yystack_[3].value.as < std::string > () << '\n';
                    }
#line 712 "src/parser/parser.cpp"
    break;

  case 4: // functionDefinition: FN "identifier" LBRACE paramList RBRACE LCURLY stmt RCURLY
#line 85 "src/parser/parser.yy"
                                                                       {
                      std::cout << "A function " << yystack_[6].value.as < std::string > () << " was defined\n"; 
                     }
#line 720 "src/parser/parser.cpp"
    break;

  case 5: // varDeclaration: "type" "identifier" SEMI_COLON
#line 89 "src/parser/parser.yy"
                                         {
                  if(currentScope->idExists(yystack_[1].value.as < std::string > ())){
		    std::cerr << "Variable " << yystack_[1].value.as < std::string > () << " redeclared here.."; 
		  } else {
		    
		    // variable is the key and type is the value
		    currentScope->installID(yystack_[1].value.as < std::string > (), yystack_[2].value.as < std::string > ());
		    std::cout << "Variable " << yystack_[1].value.as < std::string > () << " successfully added to the symbol table"; 
		  }
                }
#line 735 "src/parser/parser.cpp"
    break;

  case 6: // varInitialization: "type" "identifier" ASSIGN fnCall SEMI_COLON
#line 100 "src/parser/parser.yy"
                                                         {
                   if(currentScope->idExists(yystack_[3].value.as < std::string > ())){
		    std::cerr << "Variable " << yystack_[3].value.as < std::string > () << " redeclared here.."; 
		    } else {
		      // variable is the key and type is the value
		      currentScope->installID(yystack_[3].value.as < std::string > (), yystack_[4].value.as < std::string > ());
		      std::cout << "Variable " << yystack_[3].value.as < std::string > () << " successfully added to the symbol table"; 
		    }
		  }
#line 749 "src/parser/parser.cpp"
    break;

  case 7: // varInitialization: "type" "identifier" ASSIGN expr SEMI_COLON
#line 109 "src/parser/parser.yy"
                                                        {
                   if(currentScope->idExists(yystack_[3].value.as < std::string > ())){
		    std::cerr << "Variable " << yystack_[3].value.as < std::string > () << " redeclared here.."; 
		    } else {
		      // variable is the key and type is the value
		      currentScope->installID(yystack_[3].value.as < std::string > (), yystack_[4].value.as < std::string > ());
		      std::cout << "Variable " << yystack_[3].value.as < std::string > () << " successfully added to the symbol table"; 
		    }

		  }
#line 764 "src/parser/parser.cpp"
    break;

  case 49: // ifStmt: IF expr LCURLY stmt RCURLY elseifStmt elseStmt
#line 180 "src/parser/parser.yy"
                                                        {
           std::cout << "A if stmt was parsed\n";
	 }
#line 772 "src/parser/parser.cpp"
    break;

  case 59: // fnCall: "identifier" LBRACE argList RBRACE
#line 202 "src/parser/parser.yy"
                                 {
   if (!globalScope->FnExists(yystack_[3].value.as < std::string > ())){
    std::cout << "Error: No such function " << yystack_[3].value.as < std::string > () << " defined\n";
   }
   else {
    std::cout << "A function " << yystack_[3].value.as < std::string > () << " was called with argument:\n";
   }
 }
#line 785 "src/parser/parser.cpp"
    break;


#line 789 "src/parser/parser.cpp"

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
        report_syntax_error (yyctx);
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
    "end of file", "error", "invalid token", "NUMBER", "PLUS", "MINUS",
  "TIMES", "DIV", "MOD", "FN", "LBRACE", "RBRACE", "LCURLY", "RCURLY",
  "LBIG", "RBIG", "ASSIGN", "GT", "LT", "GE", "LE", "EQ", "NE", "RELOP",
  "ARTHOP", "KEYWORD", "IF", "ELSE", "ELSE_IF", "LOOP", "FOR", "WHILE",
  "AND", "OR", "XOR", "MATCH", "IMPORT", "IN", "CONTROL_FLOW", "COMMA",
  "FN_ARROW", "MATCH_ARROW", "RETURN", "BREAK", "SKIP", "SEMI_COLON",
  "identifier", "type", "$accept", "functionPrototype",
  "functionDefinition", "varDeclaration", "varInitialization", "loop",
  "for", "while", "stmt", "expr", "term", "factor", "assignExpr",
  "returnExpr", "breakExpr", "skipExpr", "elseStmt", "elseifStmt",
  "ifStmt", "paramList", "params", "parameter", "argList", "args",
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








  const signed char Parser::yypact_ninf_ = -40;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
     100,   -17,    12,    23,   -10,    12,    12,    -8,     0,    14,
       5,   100,   100,   100,   100,   100,   100,   100,    53,   100,
     100,   100,   100,   100,   100,    44,   -40,    12,   -40,   133,
      13,   -40,   100,    18,   152,    22,   -40,   -40,    12,    15,
       7,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,
     -40,   -40,   -40,   -40,   -40,    10,   171,    12,    12,   100,
      12,    12,    12,    12,    12,    12,    12,    12,    47,    17,
     100,   -40,   191,    51,    27,    58,    60,    24,    15,   -40,
      37,    59,    45,   -40,   -40,    13,    13,    72,   -40,   -40,
     -40,   -40,   -40,   -40,   -40,   -40,   -40,    74,    75,   -40,
      12,   -40,   -40,   103,    42,   -40,    16,    10,    62,   100,
     -40,   191,   -40,   -40,   100,    46,   -40,    12,    64,    79,
      81,     2,   182,    83,   -40,   -40,   -40,   100,   -40,   100,
     100,    84,    86,    87,   -40,    62,   -40,   -40
  };

  const signed char
  Parser::yydefact_[] =
  {
      11,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    11,    11,    11,    11,    11,    11,    11,     0,    11,
      11,    11,    11,    11,    11,     0,    39,     0,    38,     0,
      27,    36,    11,     0,     0,     0,    43,    44,    55,     0,
       0,    23,    12,    17,    18,    13,    14,    15,     1,    19,
      22,    20,    21,    16,    24,    50,     0,     0,     0,    11,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      11,    42,    58,     0,    56,    38,     0,     0,     0,     5,
       0,     0,    51,    53,    37,    25,    26,     0,    28,    29,
      31,    30,    32,    33,    34,    35,     8,     0,     0,    59,
       0,    40,    41,     0,     0,    54,     0,     0,    47,    11,
      10,    57,     7,     6,    11,     0,    52,     0,    45,     0,
       0,     0,     0,     0,    49,     9,     4,    11,     2,    11,
      11,     0,     0,     0,     3,    47,    46,    48
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -11,    11,
     -26,   -33,   -40,   -40,   -40,   -40,   -40,   -39,   -40,   -40,
     -40,    -6,   -40,   -40,   -32
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,    11,    12,    13,    14,    15,    16,    17,    18,    29,
      30,    31,    19,    20,    21,    22,   124,   118,    23,    81,
      82,    83,    73,    74,    24
  };

  const unsigned char
  Parser::yytable_[] =
  {
      41,    42,    43,    44,    45,    46,    47,    77,    49,    50,
      51,    52,    53,    54,   127,    26,    34,    35,    26,    66,
      67,    68,    27,    78,    38,    27,    57,    58,   114,    25,
      39,    85,    86,    94,    95,    32,    33,    36,    56,    60,
      61,    62,    63,    64,    65,    37,   104,   128,    87,    72,
      76,    40,    79,    48,    55,    69,   115,    80,    28,    98,
      96,    75,    99,    97,    57,    58,   100,    71,    38,   102,
     106,    88,    89,    90,    91,    92,    93,    60,    61,    62,
      63,    64,    65,   105,   107,   108,   109,   113,   110,   103,
     117,   123,   125,   121,   126,   130,   137,   134,   119,   135,
     136,   116,     0,   120,     0,   101,     0,    57,    58,     1,
       0,   111,     0,     0,     0,     0,   131,     0,   132,   133,
      60,    61,    62,    63,    64,    65,     2,     0,   122,     3,
       4,     5,     0,     0,     0,     0,     0,    57,    58,     0,
       0,     0,     6,     7,     8,    59,     9,    10,   112,     0,
      60,    61,    62,    63,    64,    65,    57,    58,     0,     0,
       0,     0,     0,     0,    70,     0,     0,     0,     0,    60,
      61,    62,    63,    64,    65,    57,    58,     0,     0,     0,
       0,     0,    84,     0,     0,     0,    57,    58,    60,    61,
      62,    63,    64,    65,   129,    57,    58,     0,     0,    60,
      61,    62,    63,    64,    65,     0,     0,     0,    60,    61,
      62,    63,    64,    65
  };

  const short
  Parser::yycheck_[] =
  {
      11,    12,    13,    14,    15,    16,    17,    39,    19,    20,
      21,    22,    23,    24,    12,     3,     5,     6,     3,     6,
       7,    32,    10,    16,    10,    10,     4,     5,    12,    46,
      16,    57,    58,    66,    67,    12,    46,    45,    27,    17,
      18,    19,    20,    21,    22,    45,    78,    45,    59,    38,
      39,    46,    45,     0,    10,    37,    40,    47,    46,    70,
      13,    46,    11,    46,     4,     5,    39,    45,    10,    45,
      11,    60,    61,    62,    63,    64,    65,    17,    18,    19,
      20,    21,    22,    46,    39,    13,    12,    45,    13,    78,
      28,    27,    13,    47,    13,    12,   135,    13,   109,    13,
      13,   107,    -1,   114,    -1,    45,    -1,     4,     5,     9,
      -1,   100,    -1,    -1,    -1,    -1,   127,    -1,   129,   130,
      17,    18,    19,    20,    21,    22,    26,    -1,   117,    29,
      30,    31,    -1,    -1,    -1,    -1,    -1,     4,     5,    -1,
      -1,    -1,    42,    43,    44,    12,    46,    47,    45,    -1,
      17,    18,    19,    20,    21,    22,     4,     5,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    22,     4,     5,    -1,    -1,    -1,
      -1,    -1,    11,    -1,    -1,    -1,     4,     5,    17,    18,
      19,    20,    21,    22,    12,     4,     5,    -1,    -1,    17,
      18,    19,    20,    21,    22,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     9,    26,    29,    30,    31,    42,    43,    44,    46,
      47,    49,    50,    51,    52,    53,    54,    55,    56,    60,
      61,    62,    63,    66,    72,    46,     3,    10,    46,    57,
      58,    59,    12,    46,    57,    57,    45,    45,    10,    16,
      46,    56,    56,    56,    56,    56,    56,    56,     0,    56,
      56,    56,    56,    56,    56,    10,    57,     4,     5,    12,
      17,    18,    19,    20,    21,    22,     6,     7,    56,    37,
      12,    45,    57,    70,    71,    46,    57,    72,    16,    45,
      47,    67,    68,    69,    11,    58,    58,    56,    57,    57,
      57,    57,    57,    57,    59,    59,    13,    46,    56,    11,
      39,    45,    45,    57,    72,    46,    11,    39,    13,    12,
      13,    57,    45,    45,    12,    40,    69,    28,    65,    56,
      56,    47,    57,    27,    64,    13,    13,    12,    45,    12,
      12,    56,    56,    56,    13,    13,    13,    65
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    48,    49,    50,    50,    51,    52,    52,    53,    54,
      55,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    58,    58,    58,    59,    59,    59,
      60,    60,    61,    62,    63,    64,    64,    65,    65,    66,
      67,    67,    68,    68,    69,    70,    70,    71,    71,    72
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     8,    10,     8,     3,     5,     5,     4,     7,
       5,     0,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     3,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     3,     1,     1,
       4,     4,     3,     2,     2,     0,     4,     0,     6,     7,
       0,     1,     3,     1,     2,     0,     1,     3,     1,     4
  };




#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,    67,    67,    82,    85,    89,   100,   109,   120,   122,
     124,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   153,   154,   155,   158,   159,   160,
     163,   164,   167,   169,   171,   173,   174,   177,   178,   180,
     184,   185,   188,   189,   192,   194,   195,   198,   199,   202
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

#line 13 "src/parser/parser.yy"
} // STAB
#line 1239 "src/parser/parser.cpp"

#line 211 "src/parser/parser.yy"


namespace STAB {
 template <typename RHS>
 inline void calcLocation(location& current, const RHS& rhs, const std::size_t n){
 current = location(YYRHSLOC(rhs, 1).first, YYRHSLOC(rhs, n).second);
 }
 void Parser::report_syntax_error(const context& ctx) const {

  std::cerr << ctx.location() << ": Syntax Error Something went wrong"; 
 }
 void Parser::error(const location &loc, const std::string &message){
  std::cerr << "Error at lines " << loc << ": " << message << std::endl;
 }
}

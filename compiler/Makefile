.RECIPEPREFIX = >

LLVM_CONFIG = llvm-config
LLVM_CXXFLAGS = `$(LLVM_CONFIG) --cxxflags` -fexceptions -frtti
LLVM_LDFLAGS = `$(LLVM_CONFIG) --ldflags --system-libs --libs all`

SRCS = src/lib/lib.cpp \
       src/main.cpp \
       src/lexer/lexer.cpp \
       src/parser/parser.cpp \
       src/includes/scope.cpp \
       src/simple-ast/binaryExprAST.cpp \
       src/simple-ast/callExprAST.cpp \
       src/simple-ast/functionAST.cpp \
       src/simple-ast/functionPrototype.cpp \
       src/simple-ast/loopStatementAST.cpp \
       src/simple-ast/numberExprAST.cpp \
       src/simple-ast/returnStmtAST.cpp \
       src/simple-ast/variableAssignExprAST.cpp \
       src/simple-ast/variableDeclAssignExprAST.cpp \
       src/simple-ast/variableDeclExprAST.cpp \
       src/simple-ast/variableExprAST.cpp \
       src/simple-ast/whileStatementAST.cpp \
       src/simple-ast/stringExprAST.cpp \
       src/simple-ast/callStatementAST.cpp \
       src/simple-ast/ifstmt.cpp \
       src/simple-ast/condStatement.cpp \
       src/simple-ast/elseStmt.cpp \
       src/simple-ast/forStatementAST.cpp \
       src/simple-ast/arrayAST.cpp \
       src/simple-ast/arrayRefAST.cpp \
       src/simple-ast/arrayAssignAST.cpp \
       src/simple-ast/breakstmtast.cpp \
       src/simple-ast/skipstmtast.cpp

OBJS = $(SRCS:.cpp=.o)

all: stab

stab: $(OBJS)
> clang++ -g $(OBJS) -o $@ $(LLVM_LDFLAGS)

%.o: %.cpp
> clang++ -g -c $< -o $@ $(LLVM_CXXFLAGS)

src/parser/parser.cpp src/parser/parser.hpp parser.output: src/parser/parser.yy
> bison --language=c++ -o src/parser/parser.cpp $<

src/lexer/lexer.cpp: src/lexer/lexer.l
> flex -o src/lexer/lexer.cpp $<

.PHONY: clean
clean:
> rm -f $(OBJS) prog parser.output

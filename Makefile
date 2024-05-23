.RECIPEPREFIX = >

LLVM_CONFIG = llvm-config
LLVM_CXXFLAGS = `$(LLVM_CONFIG) --cxxflags`
LLVM_LDFLAGS = `$(LLVM_CONFIG) --ldflags --system-libs --libs core`

SRCS = src/main.cpp \
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
       src/simple-ast/whileStatementAST.cpp

OBJS = $(SRCS:.cpp=.o)

all: prog

prog: $(OBJS)
> clang++ -g $(OBJS) -o $@ $(LLVM_LDFLAGS)

%.o: %.cpp
> clang++ -g -c $< -o $@ $(LLVM_CXXFLAGS)


src/lexer/lexer.cpp: src/lexer/lexer.l
> flex -o src/lexer/lexer.cpp $<


src/parser/parser.cpp src/parser/parser.hpp parser.output: src/parser/parser.yy
> bison -o src/parser/parser.cpp $<

.PHONY: clean
clean:
> rm -f $(OBJS) prog parser.output

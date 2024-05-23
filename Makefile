.RECIPEPREFIX = >

all: prog

prog: main.o parser.o lexer.o
> clang++ -g  $^ -o $@ `llvm-config --cxxflags --ldflags --system-libs --libs core`

main.o: src/main.cpp src/lexer/lexer.hpp src/parser/parser.hpp src/includes/location.hpp src/includes/scope.h src/globals.h src/simple-ast/ast.h
> clang++ -g -c -o3 $< -o $@ `llvm-config --cxxflags --ldflags --system-libs --libs core`

lexer.o: src/lexer/lexer.cpp src/lexer/lexer.hpp src/parser/parser.hpp src/includes/location.hpp
> clang++ -g -c $< -o $@

parser.o: src/parser/parser.cpp src/lexer/lexer.hpp src/includes/location.hpp
> clang++ -g -c $< -o $@

src/lexer/lexer.cpp: src/lexer/lexer.l
> flex -o src/lexer/lexer.cpp $<

src/parser/parser.hpp src/parser/parser.cpp src/parser/parser.output: src/parser/parser.yy
> bison -o src/parser/parser.cpp $<

.PHONY: clean
clean:
> rm -f main.o lexer.o parser.o parser.output

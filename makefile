.RECIPEPREFIX = >

prog: main.o parser.o lexer.o
> g++ $^ -o $@

main.o: main.cpp lexer.hpp parser.hpp location.hpp
> g++ -c $< -o $@

lexer.o: lexer.cpp lexer.hpp parser.hpp location.hpp
> g++ -c $< -o $@

parser.o: parser.cpp lexer.hpp location.hpp
> g++ -c $< -o $@

lexer.cpp: lexer.ll
> flex -o lexer.cpp $<

parser.hpp parser.cpp parser.output: parser.yy
> bison -o parser.cpp $<

.PHONY: clean
clean:
> rm -f prog main.o lexer.o parser.o parser.output

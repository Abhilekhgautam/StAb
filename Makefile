.RECIPEPREFIX = >

prog: main.o parser.o lexer.o
> g++ $^ -o $@

main.o: src/main.cpp src/lexer/lexer.hpp src/parser/parser.hpp src/includes/location.hpp
> g++ -c $< -o $@

lexer.o: src/lexer/lexer.cpp src/lexer/lexer.hpp src/parser/parser.hpp src/includes/location.hpp
> g++ -c $< -o $@

parser.o: src/parser/parser.cpp src/lexer/lexer.hpp src/includes/location.hpp
> g++ -c $< -o $@

src/lexer/lexer.cpp: src/lexer/lexer.ll
> flex -o src/lexer/lexer.cpp $<

src/parser/parser.hpp src/parser/parser.cpp src/parser/parser.output: src/parser/parser.yy
> bison -o src/parser/parser.cpp $<

.PHONY: clean
clean:
> rm -f prog main.o lexer.o parser.o parser.output

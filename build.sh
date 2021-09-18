clear

rm mutantgenerator

cd ./parser/

flex promela.l && yacc -y -d promela.y

cp promela.l promela.y lex.yy.c y.tab.c ../

cd ..

g++ -Wall -Wextra -ggdb -O0 -o mutantgenerator main.cpp \
	./parser/lex.yy.c \
	./parser/y.tab.c \
	./automata/symbols.cpp \
	./automata/automata.cpp \
	./automata/expression.cpp \
	-I./automata -I./parser \
	-lstdc++

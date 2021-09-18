clear

rm provelines

cd ./parser/

flex promela.l && yacc -y -d promela.y 
cd ..

g++ -Wall -Wextra -ggdb -O0 -o provelines main.cpp \
	parser/lex.yy.c \
	parser/y.tab.c \
	automata/symbols.cpp \
	automata/automata.cpp \
	-I. -I./automata -I./parser \
	-lstdc++

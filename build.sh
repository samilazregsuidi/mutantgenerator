clear

rm mutantgenerator

cd ./parser

flex promela.l && yacc -y -d promela.y

cp promela.l promela.y lex.yy.c y.tab.c ../

cd ..

g++ -Wall -Wextra -ggdb -O0 -o mutantgenerator main.cpp \
	./parser/lex.yy.c \
	./parser/y.tab.c \
	\
	./automata/symbol/symbol.cpp \
	./automata/symbol/symTable.cpp \
	./automata/symbol/bitSymNode.cpp \
	./automata/symbol/boolSymNode.cpp \
	./automata/symbol/byteSymNode.cpp \
	./automata/symbol/shortSymNode.cpp \
	./automata/symbol/intSymNode.cpp \
	./automata/symbol/unsgnSymNode.cpp \
	./automata/symbol/utypeSymNode.cpp \
	./automata/symbol/mtypeSymNode.cpp \
	./automata/symbol/cidSymNode.cpp \
	./automata/symbol/chanSymNode.cpp \
	./automata/symbol/procSymNode.cpp \
	./automata/symbol/tdefSymNode.cpp \
	./automata/symbol/varSymNode.cpp \
	./automata/symbol/naSymNode.cpp \
	./automata/symbol/pidSymNode.cpp \
	./automata/symbol/mtypedefSymNode.cpp \
	\
	./automata/ast/astNode.cpp \
	./automata/ast/stmnt.cpp \
	./automata/ast/chanStmnt.cpp \
	./automata/ast/flowStmnt.cpp \
	./automata/ast/stdlibStmnt.cpp \
	./automata/ast/clockStmnt.cpp \
	./automata/ast/decl.cpp \
	./automata/ast/expr.cpp \
	./automata/ast/unaryExpr.cpp \
	./automata/ast/binaryExpr.cpp \
	./automata/ast/varExpr.cpp \
	./automata/ast/constExpr.cpp \
	./automata/ast/argExpr.cpp \
	\
	-I./automata/symbol -I./automata/symbol/visitor -I./automata/ast -I./parser \
	\
	-lstdc++

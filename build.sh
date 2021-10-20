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
	./automata/symbol/typedef/procSymNode.cpp \
	./automata/symbol/typedef/tdefSymNode.cpp \
	./automata/symbol/typedef/mtypedefSymNode.cpp \
	./automata/symbol/vardef/bitSymNode.cpp \
	./automata/symbol/vardef/boolSymNode.cpp \
	./automata/symbol/vardef/byteSymNode.cpp \
	./automata/symbol/vardef/shortSymNode.cpp \
	./automata/symbol/vardef/intSymNode.cpp \
	./automata/symbol/vardef/unsgnSymNode.cpp \
	./automata/symbol/vardef/utypeSymNode.cpp \
	./automata/symbol/vardef/mtypeSymNode.cpp \
	./automata/symbol/vardef/cidSymNode.cpp \
	./automata/symbol/vardef/chanSymNode.cpp \
	./automata/symbol/vardef/varSymNode.cpp \
	./automata/symbol/vardef/naSymNode.cpp \
	./automata/symbol/vardef/pidSymNode.cpp \
	\
	./automata/ast/astNode.cpp \
	./automata/ast/stmnt/stmnt.cpp \
	./automata/ast/stmnt/chanStmnt.cpp \
	./automata/ast/stmnt/flowStmnt.cpp \
	./automata/ast/stmnt/stdlibStmnt.cpp \
	./automata/ast/stmnt/clockStmnt.cpp \
	./automata/ast/stmnt/decl.cpp \
	./automata/ast/expr/expr.cpp \
	./automata/ast/expr/unaryExpr.cpp \
	./automata/ast/expr/binaryExpr.cpp \
	./automata/ast/expr/varExpr.cpp \
	./automata/ast/expr/constExpr.cpp \
	./automata/ast/expr/argExpr.cpp \
	\
	-I./automata/symbol -I./automata/symbol/typedef -I./automata/symbol/vardef -I./automata/symbol/visitor \
	-I./automata/ast -I./automata/ast/stmnt -I./automata/ast/expr -I./parser \
	\
	-lstdc++

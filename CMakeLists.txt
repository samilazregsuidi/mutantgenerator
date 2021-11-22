cmake_minimum_required(VERSION 3.10)

project(mutantgenerator LANGUAGES CXX)

set(ASAN -fsanitize=address -fno-omit-frame-pointer -static-libasan)

set(Parser "y.tab.cpp")
set(Lexer "lex.yy.cpp")
add_custom_command(
    OUTPUT ${Parser}
    COMMAND yacc -y -d -o ${Parser} ${CMAKE_SOURCE_DIR}/parser/promela.y
    DEPENDS ${CMAKE_SOURCE_DIR}/parser/promela.y
    COMMENT "running yacc"
)

add_custom_command(
    OUTPUT ${Lexer}
    COMMAND flex -o ${Lexer} ${CMAKE_SOURCE_DIR}/parser/promela.l
    DEPENDS ${CMAKE_SOURCE_DIR}/parser/promela.l
    COMMENT "running flex"
)
add_compile_options(
	-Wall
	-Wextra
	-pedantic
	-ggdb
	-O0
	${ASAN}
)
add_link_options(
	${ASAN}
)

add_executable(mutantgenerator
    main.cpp
	./automata/symbol/symbol.cpp
	./automata/symbol/symTable.cpp
	./automata/symbol/typedef/procSymNode.cpp
	./automata/symbol/typedef/tdefSymNode.cpp
	./automata/symbol/typedef/mtypedefSymNode.cpp
	./automata/symbol/vardef/bitSymNode.cpp
	./automata/symbol/vardef/boolSymNode.cpp
	./automata/symbol/vardef/byteSymNode.cpp
	./automata/symbol/vardef/shortSymNode.cpp
	./automata/symbol/vardef/intSymNode.cpp
	./automata/symbol/vardef/unsgnSymNode.cpp
	./automata/symbol/vardef/utypeSymNode.cpp
	./automata/symbol/vardef/mtypeSymNode.cpp
	./automata/symbol/vardef/cidSymNode.cpp
	./automata/symbol/vardef/chanSymNode.cpp
	./automata/symbol/vardef/varSymNode.cpp
	./automata/symbol/vardef/naSymNode.cpp
	./automata/symbol/vardef/pidSymNode.cpp

	./automata/ast/astNode.cpp
	./automata/ast/stmnt/stmnt.cpp
	./automata/ast/stmnt/chanStmnt.cpp
	./automata/ast/stmnt/flowStmnt.cpp
	./automata/ast/stmnt/stdlibStmnt.cpp
	./automata/ast/stmnt/clockStmnt.cpp
	./automata/ast/stmnt/decl.cpp
	./automata/ast/expr/expr.cpp
	./automata/ast/expr/unaryExpr.cpp
	./automata/ast/expr/binaryExpr.cpp
	./automata/ast/expr/varExpr.cpp
	./automata/ast/expr/constExpr.cpp
	./automata/ast/expr/argExpr.cpp

    ${Parser}
    ${Lexer}
    )

#target_link_libraries(mutantgenerator ${FLEX_LIBRARIES})
target_include_directories(mutantgenerator
    PUBLIC
    ./automata/symbol
    ./automata/symbol/typedef
    ./automata/symbol/vardef
    ./automata/symbol/visitor
    ./automata/ast
    ./automata/ast/stmnt
    ./automata/ast/expr
    ${CMAKE_CURRENT_BINARY_DIR}
    )


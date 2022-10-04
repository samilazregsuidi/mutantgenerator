cmake_minimum_required(VERSION 3.10)

project(mutantgenerator LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

#set(ASAN -fsanitize=address -fno-omit-frame-pointer -static-libasan)

set(Parser "y.tab.cpp")
set(Lexer "lex.yy.cpp")

add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/parser/${Parser}
    COMMAND yacc -y -d -o ${CMAKE_SOURCE_DIR}/parser/${Parser} ${CMAKE_SOURCE_DIR}/parser/promela.y
    DEPENDS ${CMAKE_SOURCE_DIR}/parser/promela.y
    COMMENT "running yacc"
)

add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/parser/${Lexer}
    COMMAND flex -o ${CMAKE_SOURCE_DIR}/parser/${Lexer} ${CMAKE_SOURCE_DIR}/parser/promela.l
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
	./automata/symbol/typedef/inlineSymNode.cpp
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
	
	./automata/fsm/ASTtoFSM.cpp
	./automata/fsm/fsm.cpp
	./automata/fsm/fsmNode.cpp
	./automata/fsm/fsmEdge.cpp
	
	./semantic/state.cpp
	./semantic/programState
	./semantic/compositeState.cpp
	./semantic/scope.cpp
	./semantic/process.cpp
	./semantic/variable.cpp
	./semantic/channel.cpp
	./semantic/payload.cpp
	./semantic/transition.cpp
	./semantic/programTransition.cpp
	./semantic/rendezVousTransition.cpp
	./semantic/compositeTransition.cpp

${CMAKE_SOURCE_DIR}/parser/${Parser}
${CMAKE_SOURCE_DIR}/parser/${Lexer}
    
	)

target_include_directories(mutantgenerator
    PUBLIC
    ./automata/symbol
    ./automata/symbol/typedef
    ./automata/symbol/vardef
    ./automata/symbol/visitor
    
    ./automata/ast
    ./automata/ast/stmnt
    ./automata/ast/expr
    ./automata/ast/visitor
    
    ./automata/fsm
    
    ./semantic
    
    ./parser

    ./libs/cudd/cplusplus

    ${CMAKE_CURRENT_BINARY_DIR}
	)


target_link_directories(mutantgenerator
	PUBLIC

	./libs/cudd/cplusplus/.libs
	./libs/cudd/cudd/.libs
	)

target_link_libraries(mutantgenerator libobj.a libcudd.a)




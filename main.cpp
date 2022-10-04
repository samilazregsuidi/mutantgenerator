#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>

#include "symbols.hpp"
#include "ast.hpp"
#include "automata.hpp"
#include "y.tab.hpp"
#include "lexer.h"

#include "ASTtoFSM.hpp"

#include "semantic.hpp"

extern void init_lex();

// Settings defined in main

// Other global variables from main
symTable* globalSymTab = nullptr;
stmnt* program = nullptr;

/**
 * Simply copies a file byte by byte; could be made more efficient.
 */
int copyFile(const std::string& source, const std::string& target) {
	FILE* fsource;
	FILE* ftarget;
	fsource = fopen(source.c_str(), "r");
	ftarget = fopen(target.c_str(), "w");

	if(fsource != NULL && ftarget != NULL)  {
		char buffer;
		buffer = fgetc(fsource);
		while(!feof(fsource)) {
			fputc(buffer, ftarget);
			buffer = fgetc(fsource);
		}
		fclose(fsource);
		fclose(ftarget);
		return 1;
	}

	if(fsource != NULL) fclose(fsource);
	if(ftarget != NULL) fclose(ftarget);
	return 0;
}

#define PRINT_STATE printTexada

#define B 10

void launchExecution(const fsm* automata) {
	state* current = new progState(automata);
	unsigned long i = 0;
	//printf("**********************************\n");
	current->PRINT_STATE();
	current->printGraphViz(i++);

	while(transition* trans = transition::sample(current->executables())){
		current->apply(trans);
		//printf("--------------------------------------\n");
		current->PRINT_STATE();
		current->printGraphViz(i++);
		if(i > B){
			break;
		}
		//add error status
	}
	printf("--\n");
}

#define K 100

void findLasso(const fsm* automata, size_t k_steps) {
	
	size_t i = 0;

	std::set<unsigned long> hashSet;

	state* current = new progState(automata);
	transition* trans = nullptr;

	while(true) {

		//printf("**********************************\n");
		current->PRINT_STATE();
		current->printGraphViz(i);

		auto hash = current->hash();
		if(hashSet.find(hash) == hashSet.end() || i++ < k_steps) {
			
			hashSet.insert(current->hash());
			
			if((trans = transition::sample(current->executables()))) {
				printf("..\n");
				current->apply(trans);
			} else 
				break;

		} else break;
		
	}
		
	printf("--\n");
}

#define D 5

void createStateSpace(const fsm* automata) {
	std::stack<state*> st;
	state* current = new progState(automata);
	st.push(current);
	unsigned long i = 0;
	
	while(!st.empty()){

		current = st.top();
		printf("****************** current state ****************\n");
		current->PRINT_STATE();
		st.pop();
		
		
		auto nexts = current->Post();

		if(nexts.size() > 0) {
			printf("************* next possible states **************\n");
			for(auto n : nexts) {
				n->PRINT_STATE();
				st.push(n);
				if(nexts.size() > 1)
					printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
			}
		} else {
			printf("************* end state **************\n");
		}

		if(i > D)
			break;
		//add error status
	}

}

#define NB_LASSO 1000

int main(int argc, char *argv[]) {

	if(sizeof(int)   != 4)	{ std::cout << "Bad architecture: int type must be four bytes long.\n"; exit(1); }
	if(sizeof(short) != 2)	{ std::cout << "Bad architecture: short type must be two bytes long.\n"; exit(1); }
	if(sizeof(void*) != 8)  { std::cout << "Bad architecture: pointer type must be eight bytes long.\n"; exit(1); }

	if(argc < 2) { std::cout << "No fPromela file provided."; exit(1); }

	if(!copyFile(argv[argc - 1], "__workingfile.tmp")) { std::cout << "The fPromela file does not exist or is not readable!\n"; exit(1); }

	// Invoke cpp
	if(system("cpp __workingfile.tmp __workingfile.tmp.cpp") != 0) { std::cout << "Could not run the c preprocessor (cpp).\n"; exit(1); }

	yyin = fopen("__workingfile.tmp.cpp", "r");
	if(yyin == nullptr) { std::cout << "Could not open temporary working file ("<<argv[argc - 1]<<").\n"; exit(1); }
	init_lex();

	if(yyparse(&globalSymTab, &program) != 0) { 
		std::cout << "Syntax error; aborting..\n"; exit(1); 
	}

	srand(time(NULL));

	unsigned int index = program->assignMutables();
	std::cout << "NUMBER OF MUTABLE NODE " << index << "\n";

	std::ofstream output;
	output.open("mutants/original.pml");
	output << "#include \"./Theory.prp\"\n";
	output << stmnt::string(program);
	output.close();

	//ASTtoFSM converter;
	//fsm* automata = converter.astToFsm(globalSymTab, program);
	//std::ofstream graph;
	//graph.open("fsm_graphvis");
	//automata->printGraphVis(graph);
	//graph.close();

	for(unsigned int i = 1; i <= index; i++) {
		auto copy = program->deepCopy();
		astNode::mutate(copy, i);
		output.open("mutants/mutant_"+ std::to_string(i) + ".pml");
		output << "#include \"./Theory.prp\"\n";
		output << stmnt::string(copy);
		output.close();
		delete copy;
	}

	//for(int i = 0; i < NB_LASSO; ++i)
	//	findLasso(automata, K);

	//std::ofstream symtable;
	//symtable.open("sym_table_graphviz");
	//globalSymTab->printGraphViz(symtable);
	//symtable.close();

	//output.open("mutants/original_.pml");
	//output << stmnt::string(program);
	//output.close();

	
	//state* init = new state(globalSymTab, automata);

	delete globalSymTab;

	delete program;

	if(yyin != nullptr) fclose(yyin);
	
	exit(0);
}

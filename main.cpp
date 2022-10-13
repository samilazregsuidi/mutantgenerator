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
#include "y.tab.hpp"
#include "lexer.h"

extern void init_lex();

// Settings defined in main

// Other global variables from main
symTable* globalSymTab = nullptr;
stmnt* program = nullptr;

int main(int argc, char *argv[]) {

	if(sizeof(int)   != 4)			{ std::cout << "Bad architecture: int type must be four bytes long.\n"; exit(1); }
	if(sizeof(short) != 2)			{ std::cout << "Bad architecture: short type must be two bytes long.\n"; exit(1); }
	if(sizeof(unsigned long) != 8)  	{ std::cout << "Bad architecture: long type must be two bytes long.\n"; exit(1); }
	if(sizeof(double) != 8)  		{ std::cout << "Bad architecture: double type must be two bytes long.\n"; exit(1); }
	if(sizeof(void*) != 8)  		{ std::cout << "Bad architecture: pointer type must be eight bytes long.\n"; exit(1); }

	if(argc < 2) { std::cout << "No fPromela file provided."; exit(1); }

	yyin = fopen(argv[3], "r");
	if(yyin == nullptr) { std::cout << "Could not open temporary working file ("<<argv[3]<<").\n"; exit(1); }
	init_lex();

	if(yyparse(&globalSymTab, &program) != 0) { 
		std::cout << "Syntax error; aborting..\n"; exit(1); 
	}

	unsigned int index = program->assignMutables();
	std::cout << "NUMBER OF MUTABLE NODE " << index << "\n";

	std::ofstream output;
	output.open("mutants/original.pml");
	output << argv[2] <<std::endl ;
	output << stmnt::string(program);
	output.close();

	unsigned int nb_iterations = atoi(argv[1]);
	for(unsigned int j = 0; j < nb_iterations; j++){
		for(unsigned int i = 1; i <= index; i++) {
			auto copy = program->deepCopy();
			astNode::mutate(copy, i);
			output.open("mutants/mutant_"+ std::to_string(j * index + i) + ".pml");
			output << argv[2] << std::endl;
			output << stmnt::string(copy);
			output.close();
			delete copy;
		}
	}


	delete globalSymTab;
	delete program;

	if(yyin != nullptr) fclose(yyin);
	
	exit(0);
}

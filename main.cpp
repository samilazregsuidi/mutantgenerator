#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <time.h>

#include "symbols.h"
#include "ast.h"
#include "y.tab.h"
#include "lexer.h"


extern FILE* yyin;
extern int yyparse(symTable** symTable, stmnt** program);
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

	unsigned int index = program->assignMutables();
	std::cout << "NUMBER OF MUTABLE NODE " << index << "\n";

	std::ofstream output;
	output.open("test/original.pml");
	output << std::string(*program);
	output.close();

	for(int j = 1; j < 2; j++)
	for(unsigned int i = 1; i <= index; i++) {
		auto copy = program->deepCopy();
		copy->mutateMutable(i);
		output.open("test/mutant_"+ std::to_string(i*j) + ".pml");
		output << std::string(*copy);
		output.close();
	}

	output.open("test/original_.pml");
	output << std::string(*program);
	output.close();

	if(yyin != nullptr) fclose(yyin);
	
	exit(0);
}

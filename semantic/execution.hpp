#ifndef EXECUTION_H
#define EXECUTION_H

/*
 * Execution of FSMs
 * * * * * * * * * * * * * * * * * * * * * * * */

#include <stack>

class state;

typedef char byte;
typedef unsigned char byte;

class execution : public std::stack<state*> {
public:
	void print(void);
};

#endif

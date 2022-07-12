#ifndef STATE_SPACE_H
#define STATE_SPACE_H

/*
 * Execution of FSMs
 * * * * * * * * * * * * * * * * * * * * * * * */
#include <map>
#include <vector>

class state;

typedef char byte;
typedef unsigned char byte;

class stateSpace : public std::map<state*, std::vector<state*>> {
public:
	void print(void);
};

#endif

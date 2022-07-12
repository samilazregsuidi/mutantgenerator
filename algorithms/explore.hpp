#ifndef EXPLORE_H
#define EXPLORE_H

#include <stack>

class fsm;
class symTable;
class state;

typedef char byte;

void launchExecution(const fsm* automata);
void startNestedDFS(void);
byte outerDFS(std::stack<state*>& stackOuter);
byte innerDFS(std::stack<state*>& stackOuter, std::stack<state*>& stackInner);

#endif
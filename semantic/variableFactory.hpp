#ifndef VARIABLE_FACTORY_H
#define VARIABLE_FACTORY_H

#include <list>

class variable;
class varSymNode;
class scope;

class variableFactory {
	std::list<variable*> createVariables(scope* sc, const varSymNode* sym) const;
};

#endif
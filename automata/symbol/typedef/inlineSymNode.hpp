#ifndef INLINE_SYM_NODE_H
#define INLINE_SYM_NODE_H

#include <list>

#include "procSymNode.hpp"

//T_INLINE
class inlineSymNode : public seqSymNode {
public:
	inlineSymNode(const std::string& name, const std::list<std::string>& params, stmnt* block, int lineNb);

	std::string getTypeName(void) const override;

	std::string getBasicTypeName(void) const override;

	int getTypeSize(void) const override;

	const std::list<std::string>& getParams(void) const;

	operator std::string(void) const override;

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;

	//void printGraphViz(std::ofstream& file) const;

private:
	std::list<std::string> params;
};

#endif

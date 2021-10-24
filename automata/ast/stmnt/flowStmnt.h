#ifndef FLOW_STMNT_H
#define FLOW_STMNT_H

#include <iostream>

#include "stmnt.h"

//E_STMNT_OPT,		// child[0] = E_STMNT_OPT (next option; or NULL), fsm = fsm of this option
class stmntOpt : public stmnt
{
public:
	stmntOpt(stmnt* block, stmntOpt *nextOpt, int lineNb)
		: stmnt(astNode::E_STMNT_OPT, lineNb)
	{
		setBlock(block);
		setNextOpt(nextOpt);

		//std::cout << "OPT $1 $2 : line " << lineNb << " _ " << std::string(*this) << "\n";
	}

	stmntOpt(stmnt* block, int lineNb)
		: stmnt(astNode::E_STMNT_OPT, lineNb)
	{
		setBlock(block);
		setNextOpt(nextOpt);

		//std::cout << "OPT $1 : line " << lineNb << " _ " << std::string(*this) << "\n";
	}

	void setBlock(stmnt* block) {
		rmChild(this->block);
		addChild(block);
		this->block = block;
	}

	void setNextOpt(stmntOpt* nextOpt) {
		rmChild(this->nextOpt);
		addChild(nextOpt);
		this->nextOpt = nextOpt;
	}

	operator std::string() const override {
		std::string res = _tab(-1) + "::\t" + std::string(*block);

		auto cur = block->getNext();
		while(cur) {
			res += _tab() + std::string(*cur);
			cur = cur->getNext();
		}
		
		return res + (nextOpt? std::string(*nextOpt) : "");
	}

	std::string getTypeDescr(void) const override {
		return "Opt (E_STMNT_OPT)";
	}

	stmnt* deepCopy(void) const override {
		stmntOpt* copy = new stmntOpt(*this);
		copy->prev = copy;
		copy->setBlock(block->deepCopy());
		copy->setNextOpt(nextOpt? static_cast<stmntOpt*>(nextOpt->deepCopy()) : nullptr);

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	stmnt* block;
	stmntOpt* nextOpt;
};

//E_STMNT_IF,			// child[0] = E_STMNT_OPT (contains an fsm)
class stmntIf : public stmnt
{
public:
	stmntIf(stmntOpt *opts, int lineNb)
		: stmnt(astNode::E_STMNT_IF, lineNb)
	{
		setOpts(opts);

		//std::cout << "IF : line " << lineNb << " _ " << std::string(*this) << "\n";
	}

	void setOpts(stmntOpt* opts) {
		rmChild(this->opts);
		addChild(opts);
		this->opts = opts;
	}

	operator std::string() const override {
		std::string res = "if\n";
		tab_lvl++;
		res += std::string(*opts);
		tab_lvl--;
		return res + _tab() + "fi;\n";
	}

	std::string getTypeDescr(void) const override {
		return "If (E_STMNT_IF)";
	}

	stmnt* deepCopy(void) const override {
		stmntIf* copy = new stmntIf(*this);
		copy->prev = copy;
		copy->setOpts(static_cast<stmntOpt*>(opts->deepCopy()));

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	stmntOpt* opts;
};

//E_STMNT_DO,			// child[0] = E_STMNT_OPT (contains an fsm)
class stmntDo : public stmnt
{
public:
	stmntDo(stmntOpt *opts, int lineNb)
		: stmnt(astNode::E_STMNT_DO, lineNb)
	{
		setOpts(opts);
	}

	void setOpts(stmntOpt* opts) {
		rmChild(this->opts);
		addChild(opts);
		this->opts = opts;
	}

	operator std::string() const override {
		std::string res = "do\n"; 
		tab_lvl++;
		res += std::string(*opts); 
		tab_lvl--;
		return res + _tab() +"od;\n";
	}

	std::string getTypeDescr(void) const override {
		return "Do (E_STMNT_DO)";
	}

	stmnt* deepCopy(void) const override {
		stmntDo* copy = new stmntDo(*this);
		copy->prev = copy;
		copy->setOpts(static_cast<stmntOpt*>(opts->deepCopy()));

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	stmntOpt* opts;
};

//E_STMNT_BREAK,		// empty
class stmntBreak : public stmnt
{
public:
	stmntBreak(int lineNb)
		: stmnt(astNode::E_STMNT_BREAK, lineNb)
	{
	}

	operator std::string() const override {
		return "break;\n";
	}

	std::string getTypeDescr(void) const override {
		return "Break (E_STMNT_BREAK)";
	}

	stmnt* deepCopy(void) const override {
		stmntBreak* copy = new stmntBreak(*this);
		copy->prev = copy;

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}
};

//E_STMNT_GOTO,		// sVal = the label to go to
class stmntGoto : public stmnt
{
public:
	stmntGoto(const std::string& label, int lineNb)
		: stmnt(astNode::E_STMNT_GOTO, lineNb)
	{
		this->label = label;
	}

	operator std::string() const override {
		return "goto " + label + ";\n";
	}

	std::string getTypeDescr(void) const override {
		return "Goto (E_STMNT_GOTO)";
	}
	
	std::string getLabel(void) const {
		return label;
	}

	stmnt* deepCopy(void) const override {
		stmntGoto* copy = new stmntGoto(*this);
		copy->prev = copy;

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	std::string label;
};

//E_STMNT_LABEL,		// child[0] = E_STMNT_*, sVal = the label of child[0]
class stmntLabel : public stmnt
{
public:
	stmntLabel(const std::string& label, stmnt *labelled, int lineNb)
		: stmnt(astNode::E_STMNT_LABEL, lineNb)
	{
		this->label = label;

		setLabelled(labelled);
	}

	void setLabelled(stmnt* labelled) {
		rmChild(this->labelled);
		addChild(labelled);
		this->labelled = labelled;
	}

	operator std::string() const override {
		return label + ": \n" + std::string(*labelled);
	}

	std::string getTypeDescr(void) const override {
		return "Label (E_STMNT_LABEL)";
	}

	std::string getLabel(void) const {
		return label;
	}

	stmnt* getLabelledStmnt(void) const {
		return labelled;
	}

	stmnt* deepCopy(void) const override {
		stmntLabel* copy = new stmntLabel(*this);
		copy->prev = copy;
		copy->setLabelled(labelled->deepCopy());

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	std::string label;
	stmnt* labelled;
};

//E_STMNT_ELSE,		// empty
class stmntElse : public stmnt
{
public:
	stmntElse(int lineNb)
		: stmnt(astNode::E_STMNT_ELSE, lineNb)
	{
	}

	operator std::string() const override{
		return "else ->\n";
	}

	std::string getTypeDescr(void) const override{
		return "Else (E_STMNT_ELSE)";
	}

	stmnt* deepCopy(void) const override {
		stmntElse* copy = new stmntElse(*this);
		copy->prev = copy;

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}
};

#endif
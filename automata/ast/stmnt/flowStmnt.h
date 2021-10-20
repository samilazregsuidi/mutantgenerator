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
		this->block = block;
		this->nextOpt = nextOpt;

		this->block->setParent(this);
		this->nextOpt->setParent(this);
	}

	stmntOpt(stmnt* block, int lineNb)
		: stmnt(astNode::E_STMNT_OPT, lineNb)
	{
		this->block = block;
		this->nextOpt = nullptr;

		this->block->setParent(this);
	}

	~stmntOpt() override {
		delete block;
		if(nextOpt)
			delete nextOpt;
		if (next)
			delete next;
	}

	operator std::string() const override
	{
		return _tab(-1) + "::\t" + std::string(*block) 
		+ (nextOpt? std::string(*nextOpt) : "") 
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override
	{
		return "Opt (E_STMNT_OPT)";
	}

	unsigned int assignMutables(const Mask& mask, unsigned int id = 0) override {
		if(mask.isPresent(type))
			id = block->assignMutables(mask, id);
			id = (nextOpt? nextOpt->assignMutables(mask, id) : id); 
		return (next? next->assignMutables(mask, id) : id);
	}

	void mutateMutable(unsigned int id) override {
		block->mutateMutable(id);
		if (nextOpt) nextOpt->mutateMutable(id);
		if (next) next->mutateMutable(id);
	}

	stmnt* deepCopy(void) const {
		stmntOpt* copy = new stmntOpt(*this);
		copy->prev = copy;
		copy->block = block->deepCopy();
		copy->nextOpt = nextOpt? static_cast<stmntOpt*>(nextOpt->deepCopy()) : nullptr;

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
		this->opts = opts;
		this->opts->setParent(this);
	}

	~stmntIf() override {
		if(opts)
			delete opts;
		if (next)
			delete next;
	}

	operator std::string() const override
	{
		std::string res = "if\n";
		tab_lvl++;
		res += std::string(*opts);
		tab_lvl--;
		return res + _tab() + "fi;\n" 
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override
	{
		return "If (E_STMNT_IF)";
	}

	unsigned int assignMutables(const Mask& mask, unsigned int id = 0) override {
		if(mask.isPresent(type))
			id = opts->assignMutables(mask, id);
		return (next? next->assignMutables(mask, id) : id);
	}

	void mutateMutable(unsigned int id) override {
		opts->mutateMutable(id);
		if (next) next->mutateMutable(id);
	}

	stmnt* deepCopy(void) const {
		stmntIf* copy = new stmntIf(*this);
		copy->prev = copy;
		copy->opts = static_cast<stmntOpt*>(opts->deepCopy());

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
		this->opts = opts;

		this->opts->setParent(this);
	}

	~stmntDo() override {
		if(opts)
			delete opts;
		if (next)
			delete next;
	}

	operator std::string() const override
	{
		std::string res = "do\n"; 
		tab_lvl++;
		res += std::string(*opts); 
		tab_lvl--;
		return res + _tab() +"od;\n" 
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override
	{
		return "Do (E_STMNT_DO)";
	}

	unsigned int assignMutables(const Mask& mask, unsigned int id = 0) override {
		if(mask.isPresent(type))
			id = opts->assignMutables(mask, id);
		return (next? next->assignMutables(mask, id) : id);
	}

	void mutateMutable(unsigned int id) override {
		opts->mutateMutable(id);
		if (next) next->mutateMutable(id);
	}

	stmnt* deepCopy(void) const {
		stmntDo* copy = new stmntDo(*this);
		copy->prev = copy;
		copy->opts = static_cast<stmntOpt*>(opts->deepCopy());

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

	operator std::string() const override
	{
		return "break;\n" 
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override
	{
		return "Break (E_STMNT_BREAK)";
	}

	stmnt* deepCopy(void) const {
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

	operator std::string() const override
	{
		return "goto " + label + ";\n" 
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override
	{
		return "Goto (E_STMNT_GOTO)";
	}
	
	std::string getLabel(void) const {
		return label;
	}

	stmnt* deepCopy(void) const {
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
		this->labelled = labelled;

		this->labelled->setParent(this);
	}

	~stmntLabel() override {
		delete labelled;
		if (next)
			delete next;
	}

	operator std::string() const override
	{
		return label + ": \n" + std::string(*labelled) 
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override
	{
		return "Label (E_STMNT_LABEL)";
	}

	std::string getLabel(void) const {
		return label;
	}

	stmnt* getLabelledStmnt(void) const {
		return labelled;
	}

	unsigned int assignMutables(const Mask& mask = Mask(), unsigned int id = 0) override {
		if(mask.isPresent(type))
			id = labelled->assignMutables(mask, id);
		return (next? next->assignMutables(mask, id) : id);
	}

	void mutateMutable(unsigned int id) override {
		labelled->mutateMutable(id);
		if (next) next->mutateMutable(id);
	}

	stmnt* deepCopy(void) const {
		stmntLabel* copy = new stmntLabel(*this);
		copy->prev = copy;
		copy->labelled = labelled->deepCopy();

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
		return "else -> " 
		+ (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override{
		return "Else (E_STMNT_ELSE)";
	}

	stmnt* deepCopy(void) const {
		stmntElse* copy = new stmntElse(*this);
		copy->prev = copy;

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}
};

#endif
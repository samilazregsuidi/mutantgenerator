#include "variableFactory.hpp"

#include "scope.hpp"
#include "variable.hpp"
#include "channel.hpp"

#include "symbols.hpp"

std::list<variable*> variableFactory::createVariables(scope* sc, const varSymNode* sym) const {
	assert(sym && sc);

	std::list<variable*> res;

	switch(sym->getType())
	{
	case symbol::T_NA:
		assert(false);
	case symbol::T_BOOL:
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i)
			res.push_back(new boolVar(sc, sc->getEndOffset(), dynamic_cast<const boolSymNode*>(sym), i));
		return res;
	}
	case symbol::T_BIT:
	case symbol::T_BYTE:
	case symbol::T_SHORT:
	case symbol::T_INT:
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i)
			res.push_back(new variable(sc, sc->getEndOffset(), sym, i));
		return res;
	}
	case symbol::T_UNSGN: 	// not supported yet
		assert(false);
	case symbol::T_MTYPE:
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i)
			res.push_back(new mtypeVar(sc, sc->getEndOffset(), dynamic_cast<const mtypeSymNode*>(sym), i));
		return res;
	}
	case symbol::T_CLOCK:	// dense time clock
	case symbol::T_MTYPE_DEF:
		assert(false);
	case symbol::T_CMTYPE:
	{
		res.push_back(new cmtypeVar(sc, dynamic_cast<const cmtypeSymNode*>(sym)));
		return res;
	}
	//case symbol::T_FEAT,
	//case symbol::T_UFEAT,
	case symbol::T_UTYPE:	// Type of variable is a user type (basically, a case symbol::T_TDEF record is being used as the type): utype points to the type record
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i)
			res.push_back(new utypeVar(sc, sc->getEndOffset(), dynamic_cast<const utypeSymNode*>(sym), i));
		return res;
	}
		// "Special" types:
	case symbol::T_CHAN:		// Channel: capacity used; children denote message fields
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i)
			res.push_back(new channel(sc, sc->getEndOffset(), dynamic_cast<const chanSymNode*>(sym), i));
		return res;
	}
	case symbol::T_CID:		// Channel reference; capacity and children are not used.
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i)
			res.push_back(new CIDVar(sc, sc->getEndOffset(), dynamic_cast<const cidSymNode*>(sym), i));
		return res;
	}
	case symbol::T_PID:
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i)
			res.push_back(new PIDVar(sc, sc->getEndOffset(), dynamic_cast<const pidSymNode*>(sym), i));
		return res;
	}
	case symbol::T_TDEF:		// Type definition: children denote fields of type
	case symbol::T_INIT:
	case symbol::T_PROC:		// ProcType: fsm field used; bound denotes the number of initially active processes
	case symbol::T_INLINE:
	case symbol::T_NEVER:	// Never claim
		assert(false);
	}
	return res;
}
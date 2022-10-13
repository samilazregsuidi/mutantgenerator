#include "constExpr.hpp"

/****************************************************************
 * **************************************************************
 * *************************************************************/

exprConst::exprConst(int constant, int lineNb)
    : expr(astNode::E_EXPR_CONST, lineNb)
    , constant(constant)
{
    setExprType(symbol::T_INT);
}

exprConst::exprConst(astNode::Type type, int constant, int lineNb) 
    : expr(type, lineNb)
    , constant(constant)
{
    setExprType(symbol::T_INT);
}

int exprConst::getCstValue(void) const {
    return constant;
}

/*void exprConst::setCstValue(int constant) {
    this->constant = constant;
}*/

exprConst::operator std::string() const {
    return std::to_string(constant);
}

std::string exprConst::getTypeDescr(void) const {
    return "Constant (E_EXPR_CONST)";
}

symbol::Type exprConst::getExprType(void) const {
    return exprType == symbol::T_NA? symbol::T_INT : exprType;
}

bool exprConst::castToExprType(symbol::Type type) const {
    switch(type) {
        case symbol::T_BIT:
            if(constant != 1 && constant != 0)
                break;
            return true;
        case symbol::T_BYTE:
            if(constant < static_cast<int>(std::numeric_limits<char>::min()) 
            || constant > static_cast<int>(std::numeric_limits<char>::max()))
                break;
            return true;
        case symbol::T_SHORT:
            if(constant < static_cast<int>(std::numeric_limits<short>::min())
            || constant > static_cast<int>(std::numeric_limits<short>::max()))
                break;
            return true;
        case symbol::T_UNSGN:
            //if(constant < std::numeric_limits<unsigned int>::min() 
            //|| constant > std::numeric_limits<unsigned int>::max())
                break;
            return true;
        case symbol::T_INT:
            if(constant < std::numeric_limits<int>::min() 
            || constant > std::numeric_limits<int>::max())
                break;
            return true;
        case symbol::T_NA:
            return false;
        default:
            return false;
    }
    return false;
}

astNode* exprConst::deepCopy(void) const {
    return new exprConst(*this);
}

bool exprConst::exceed_limits(int add) const {
    return (constant + add > varSymNode::getUpperBound(getExprType()) 
    || constant + add < varSymNode::getLowerBound(getExprType()));
}

std::vector<astNode*> exprConst::getMutations(void) const {
    
    std::vector<astNode*> res;
    if(!exceed_limits(- 1))
        res.push_back(new exprConst(constant - 1, lineNb));
    if(!exceed_limits(+ 1))
        res.push_back(new exprConst(constant + 1, lineNb));

    return res;
}

/****************************************************************
 * **************************************************************
 * *************************************************************/

exprTrue::exprTrue(int lineNb)
    : exprConst(astNode::E_EXPR_TRUE, 1, lineNb)
{
    setExprType(symbol::T_BOOL);
}

exprTrue::operator std::string() const {
    return "true";
}

std::string exprTrue::getTypeDescr(void) const {
    return "True (E_EXPR_TRUE)";
}

symbol::Type exprTrue::getExprType(void) const {
    return symbol::T_BOOL;
}

astNode* exprTrue::deepCopy(void) const {
    return new exprTrue(*this);
}

std::vector<astNode*> exprTrue::getMutations(void) const {
    return { new exprFalse(lineNb) };
}

/****************************************************************
 * **************************************************************
 * *************************************************************/

exprFalse::exprFalse(int lineNb)
    : exprConst(astNode::E_EXPR_FALSE, 0, lineNb)
{
    setExprType(symbol::T_BOOL);
}

exprFalse::operator std::string() const {
    return "false";
}

std::string exprFalse::getTypeDescr(void) const {
    return "False (E_EXPR_FALSE)";
}

symbol::Type exprFalse::getExprType(void) const {
    return symbol::T_BOOL;
}

astNode* exprFalse::deepCopy(void) const {
    return new exprFalse(*this);
}

std::vector<astNode*> exprFalse::getMutations(void) const {
    return { new exprTrue(lineNb) };
}

/****************************************************************
 * **************************************************************
 * *************************************************************/
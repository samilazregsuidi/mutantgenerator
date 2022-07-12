#ifndef ALGORITHM_H
#define ALGORITHM_H

class fsm;
class symTable;

class algorithm {
    

    virtual void execute(const fsm* automata) = 0;
    
};

#endif
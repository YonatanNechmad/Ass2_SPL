
#ifndef PROJECT1_AGENT_H
#define PROJECT1_AGENT_H

#include <vector>
#include "Session.h"

class Agent{
public:
    Agent();
    virtual ~Agent()=default;
    virtual void act(Session & session)=0;
    virtual Agent* clone() const =0;
};

class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual void act(Session & session);
    virtual Agent* clone() const ;
};


class Virus: public Agent{
public:
    Virus(int nodeInd);
    virtual void act(Session & session);
    virtual Agent* clone() const ;
private:
    const int nodeInd;
};

#endif
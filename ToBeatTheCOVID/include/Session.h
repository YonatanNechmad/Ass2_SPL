#ifndef UNTITLED4_SESSION_H
#define UNTITLED4_SESSION_H
#include <vector>
#include <string>
#include "Graph.h"
#include <queue>
#define JSON_PATH "output.json"
using namespace std;

class Agent;

enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class Session{
public:

    //Rule of 5 and CTR
    Session(const string & path); //CTR
    virtual ~Session(); //destructure
    Session (const Session & that); //copy CTR
    Session(Session && that); // move CTR
    const Session& operator= (const Session& that ); // copy assignment operator
    const Session& operator= (Session && that); // move assignment operator
    void clean ();

    //methods
    void simulate();

    //cycle
    void cycle () ;
    bool shouldCycle () ;
    int getcurrentCycle() const ;

    //agent
    void addAgent(const Agent& agent);

    //graph
    void setGraph(const Graph& graph);
    Graph getGraph () const ;

    //infected
    void enqueueInfected(int);    // insert to queue the infected
    int dequeueInfected(); // takeout the infected node from the queue

    //treeType
    TreeType getTreeType() const ;

    //isInfected
    bool infectqueueempty();


private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    unsigned int currentCycle; //the number of this current cycle.
    unsigned int startTheCycle; // part of terminate condition
    queue <int> infected;


};

#endif //UNTITLED4_SESSION_H
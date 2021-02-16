
#include <vector>
#include "../include/Agent.h"
#include "../include/Tree.h"
using namespace std;
Agent::Agent() = default;

//==============================
//ContactTracer

ContactTracer::ContactTracer() = default;

void ContactTracer::act(Session & session) {
    if (!session.infectqueueempty()) {
        int currNode = session.dequeueInfected();
        Tree *TcurrNode = Tree::bfs(session, currNode); // create  BFS tree on this node
        currNode = TcurrNode->traceTree();
        delete TcurrNode;
        Graph g=session.getGraph();
        g.disconnectNeighbors(currNode);
        session.setGraph(g);

    }
}

Agent *ContactTracer::clone() const {
    return new ContactTracer();
}

//==============================
// virus

Virus::Virus(int nodeInd) :Agent() , nodeInd(nodeInd){}

void Virus::act(Session & session) {
    Graph g =session.getGraph();
    vector <bool> boolInfected=g.getVIsInfected();// array with infected nodes
    if(!boolInfected[nodeInd]){
        boolInfected[nodeInd]=true;
        g.setVIsInfected(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    vector <int> children=g.getConnectedNodes(nodeInd); // the function return neighbours of nodeInd
    vector<bool> vis=g.getVisited() ;
    bool worked =false;
    for (unsigned int i=0 ; i<children.size() && !worked ; i++){
        if (children[i]==1 && !vis[i]){
            worked= true;
            g.setVisited(i); // update changes in the original graph
            vis[i]= true;
            Virus virus(i);
            session.addAgent(virus);
        }
    }
    session.setGraph(g);
}


Agent *Virus::clone() const {
    return new Virus(*this);
}

//==============================




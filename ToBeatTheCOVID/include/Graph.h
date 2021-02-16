
#ifndef PROJECT1_GRAPH_H
#define PROJECT1_GRAPH_H

#include <vector>

using namespace std;

class Graph {
public:
    Graph(vector<vector<int>> matrix); //CTR
    // methods
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    void disconnectNeighbors(int node);
    //getter
    int matrixSize ();
    vector<int> getConnectedNodes(int nodeInd);
    vector<bool> getVIsInfected();
    vector<bool> getVisited() ;
    vector<vector<int>> getGraph ();

    //setter
    void setVIsInfected(int toChange);
    void setVisited(int toChange) ;
private:
    vector<vector<int>> edges;
    int edgesSize;
    vector<bool> VIsInfected ;   //array of the infection node
    vector<bool> visited ;   //if this node in the queue
};

#endif
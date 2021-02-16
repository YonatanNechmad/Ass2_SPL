
#include "../include/Graph.h"
using namespace std;
//CTOR
Graph::Graph(vector<vector<int>> matrix):edges(matrix),edgesSize(edges.size()),VIsInfected(),visited(){ // CTR
    VIsInfected.resize(edgesSize,false);
    visited.resize(edgesSize,false);
}
//===============================================
//methods
void Graph::infectNode(int nodeInd) {
    VIsInfected[nodeInd]=true;
}

bool Graph::isInfected(int nodeInd) {
    return VIsInfected[nodeInd];
}

void Graph::disconnectNeighbors(int node) {
    for(int i=0;i<edgesSize;i++){
        if(edges[node][i]==1){
            edges[node][i]=0;
            edges[i][node]=0;
        }
    }
}
//===============================================
//getter
int Graph::matrixSize() {
    return edgesSize;
}
vector<int> Graph::getConnectedNodes(int nodeInd) {
    return this->edges[nodeInd];
}
vector<bool> Graph::getVIsInfected() {
    return VIsInfected;
}
vector<bool> Graph::getVisited() {
    return visited;
}
vector<vector<int>> Graph::getGraph() {
    return edges;
}
//===============================================
//setter
void Graph::setVIsInfected(int toChange) {
    VIsInfected[toChange]= true;
}

void Graph::setVisited(int toChange) {
    visited[toChange]= true;
}

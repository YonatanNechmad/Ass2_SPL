
#include "ostream"
#include <fstream>
# include <vector>
#include "../include/json.hpp"
#include "../include/Session.h"
#include "../include/Agent.h"
#define JSON_PATH "output.json"

using json=nlohmann::json;
using namespace  std;
//=====================================
//Rule of 5 and CTR

Session:: Session(const string & path): g({}),treeType(),agents(), currentCycle(0),startTheCycle(0), infected(){     //CTR
    // //initialize json file
    ifstream k(path);
    json j;
    k>>j;
    this->g = Graph(j["graph"]);
    //initialize 'Agents'
    for (auto & agentConfiguration: j["agents"]) {
        string type = agentConfiguration[0];
        if (type == "V") {
            Virus *virus = new Virus(agentConfiguration[1]);
            this->agents.push_back(virus);  //
            g.setVisited(agentConfiguration[1]);
        } else {
            ContactTracer *contactTracerToAgents = new ContactTracer();
            this->agents.push_back(contactTracerToAgents);
        }
    }
    //initialize 'treeType'
    string treeTypeName = j["tree"];
    if (treeTypeName == "M") {
        this->treeType = MaxRank;
    } else if (treeTypeName == "C") {
        this->treeType = Cycle;
    } else {
        this->treeType = Root;
    }
}
Session :: ~Session(){    //destructure
    this->clean();
}

Session ::Session(const Session & that):g(that.g),treeType(that.treeType),agents(),currentCycle(that.currentCycle),
                                        startTheCycle(that.startTheCycle),infected(that.infected) {  //copy CTR
    for (const auto _Agent : that.agents) {
        this->agents.push_back(_Agent->clone());
    }}

Session ::Session(Session && that) :g(that.g),treeType(that.treeType) ,agents(move(that.agents)),currentCycle(that.currentCycle),
                                    startTheCycle(that.startTheCycle) ,infected(move(that.infected)){} // move CTR

const Session& Session :: operator= (const Session & that ) {  // copy assignment operator
    if (this!= &that){
        this->clean();
        this->g=that.g;
        this->treeType=that.treeType;
        this->currentCycle=that.currentCycle;
        this->startTheCycle=that.startTheCycle;
        this->infected=that.infected;

        for (const auto _Agent : that.agents) {
            this->agents.push_back(_Agent->clone());
        }
    }
    return *this;
}

const Session& Session::operator=(Session &&that) { // move assignment operator
    if (this!= &that) {
        this->clean();
        this->g=that.g;
        this->treeType=that.treeType;
        this->currentCycle=that.currentCycle;
        this->startTheCycle=that.startTheCycle;
        this-> infected=move(that.infected);
        this->agents=move (that.agents);
    }
    return *this;
}

void Session:: clean (){
    for (Agent * _agent :agents) {
        if(_agent)
            delete _agent;
    }
    agents.clear();
}

//======================================
//methods

void Session ::simulate() { // simulate our acts until stop condition
    for (this->currentCycle = 0; this->shouldCycle(); this->currentCycle++) {
        this->cycle();
    }
    vector<int> print;
    int j=0;
    for(bool isInfect: g.getVIsInfected()){
        if(isInfect){
            print.push_back(j);
        }
        j++;
    }
    nlohmann::json output;
    output["graph"] = g.getGraph();
    output ["infected"] = print;
    std::ofstream o(JSON_PATH);
    o << output << endl;
}
//======================================
//cycle
void Session::cycle() { //each session consists from several cycles
    int numberOfAgentsToRun = this->agents.size();
    this->startTheCycle=agents.size();
    for (int i = 0; i < numberOfAgentsToRun; i++) {
        this->agents[i]->act(*this);
    }
}

bool Session::shouldCycle() {
    return (this->startTheCycle != agents.size());
}

int Session::getcurrentCycle() const {
    return this->currentCycle;
}
//======================================
//agent
void Session::addAgent(const Agent & agent) {
    Agent * clone1 = agent.clone () ;
    agents.push_back(clone1);
}
//======================================
//graph
void Session ::setGraph(const Graph & graph) {
    this->g=graph;
}
Graph Session::getGraph() const {
    return this->g;
}
//======================================
//infected
void Session::enqueueInfected(int _node) {
    infected.push(_node);
}

int Session::dequeueInfected() {
    int toReturn = infected.front() ;
    infected.pop();
    return toReturn;
}
//======================================
//treeType

TreeType Session:: getTreeType() const {
    return this->treeType;
}
//======================================

bool Session::infectqueueempty() {
    return infected.empty();
}
//======================================


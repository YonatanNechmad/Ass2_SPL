
#include "../include/Tree.h"
#include <queue>
#include <set>
using namespace std;

// CTR , rule of 5
Tree::Tree(int rootLabel): node(rootLabel) ,children(){}

Tree::~Tree() { // destructure
    for ( Tree * toDelete : children){
        if(toDelete)
            delete toDelete;
    }
    children.clear() ;
}

Tree::Tree(const Tree &that):node(that.node) , children() { // copy CTR
    for (const Tree * toCopy : that.children){
        Tree * newTree = toCopy->clone();
        this->children.push_back(newTree);
    }
}

Tree::Tree(Tree &&that):node(that.node) ,children() { // move CTR
    this->children= that.children;
    that.children.clear();
}

const Tree& Tree::operator=(const Tree & that) { //copy assignment operator
    if (this!= &that){
        this->node=that.node;
        this->deleteChildren();
        for (Tree* toCopy :that.children){
            this->children.push_back(toCopy->clone());
        }
    }
    return *this;
}

const Tree &Tree::operator=(Tree && that) { //move assignment operator
    if (this!= & that){
        this->node= that.node;
        this->deleteChildren();
        for(auto & toMove : that.children){
            this->children.push_back(move(toMove));
            toMove= nullptr;
        }
        that.deleteChildren();
    }
    return *this;
}

void Tree::deleteChildren() {
    for ( Tree * toDelete : children) {
        delete toDelete;
    }
    children.clear();
}

//==================================
//methods
void Tree::addChild(const Tree &child) {
    Tree * _child = child.clone();
    children.push_back(_child);
}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    TreeType type = session.getTreeType();
    if (type == MaxRank) {
        return new MaxRankTree(rootLabel);
    } else if (type == Root) {
        return new RootTree(rootLabel);
    } else if (type==Cycle) {
        int currCycle = session.getcurrentCycle();
        return new CycleTree(rootLabel, currCycle);
    }
    else
        return nullptr;
}

int Tree::getNode() const {
    return node;
}

Tree *Tree::bfs(Session &session, int rootLabel) {
    Tree *result = createTree(session, rootLabel);
    queue<Tree *> labelsQueue;
    set<int> visitedLabels = set<int>();
    labelsQueue.push(result);
    visitedLabels.insert(rootLabel);
    while (!labelsQueue.empty()) {
        // Pop from queue
        Tree *currentTree = labelsQueue.front();
        int currentLabel = currentTree->getNode();
        labelsQueue.pop();
        // Insert into Queue
        vector<int> children = session.getGraph().getConnectedNodes(currentLabel);
        for (unsigned int childLabel = 0; childLabel < children.size(); childLabel++) {
            if (children[childLabel] == 1) { // if the current tree
                if (visitedLabels.insert(childLabel).second) {
                    Tree *child = createTree(session, childLabel);
                    currentTree->addChild(*child);
                    delete child;
                }
            }
        }
        for (Tree *child:currentTree->getChildren()) {
            labelsQueue.push(child);
        }
    }

    return result;
}

std::vector<Tree *> Tree::getChildren() const {
    return children;
}

// ===========================
// cycleTree

CycleTree::CycleTree(int _rootLabel, int _currCycle) :Tree(_rootLabel) , currCycle(_currCycle){}

int CycleTree::traceTree() {
    vector<Tree *> children = this->getChildren();
    Tree *result = this;
    for (int i = 0; children.size()!=0 && i < currCycle; i++) {
        result = children[0];
        children = result->getChildren();
    }
    return result->getNode();
}

Tree *CycleTree::clone() const {
    return new CycleTree(*this);
}

// ===========================
// MaxRankTree
MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

int MaxRankTree::traceTree() {
    int maxnode = this->getNode();
    int maxvalus = this->getChildren().size();
    queue<Tree *> childqueue;
    childqueue.push(this);
    MaxRankTree *curr;
    while (!childqueue.empty()) {
        curr = (MaxRankTree *) childqueue.front();
        childqueue.pop();
        int rankOfNode = curr->getChildren().size();
        if (rankOfNode > maxvalus) {
            maxvalus = rankOfNode;
            maxnode = curr->getNode();
        }
        int sizeOfChildren = curr->getChildren().size();
        for (int i = 0; i < sizeOfChildren; ++i) {
            childqueue.push((curr->getChildren()[i]));
        }
    }
    return maxnode;
}

Tree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}
// ===========================
// RootTree
RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}


int RootTree::traceTree() {
    return this->getNode();
}

Tree *RootTree::clone() const {
    return new RootTree(*this);
}

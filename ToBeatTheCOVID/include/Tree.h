
#ifndef PROJECT1_TREE_H
#define PROJECT1_TREE_H

#include <vector>
#include "../include/Session.h"
class Session;

class Tree{
public:
    //CTR ,rule of 5
    Tree(int rootLabel);
    virtual ~Tree(); //destructure
    Tree(const Tree& that); //copy CTR
    Tree (Tree && that ); //move CTR
    const Tree& operator=(const Tree& that); // copy assignment operator
    const Tree& operator=( Tree&& that); // move assignment operator
    void deleteChildren();
   //int getRootLabel()const;
    //methods

    void addChild(const Tree & child);
    virtual Tree* clone() const =0 ;
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    int getNode() const;
    static  Tree* bfs (Session  &session, int rootlable);
    std:: vector <Tree * > getChildren () const ;
private:
    int node;
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
    virtual Tree* clone() const;
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;

};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;


};

#endif
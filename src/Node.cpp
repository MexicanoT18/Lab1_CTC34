#include "Node.h"

Node::Node(int id)
{
    _id = id;
}

void Node::addEdge(char carac, int to){
    if (_id == to && carac == '&') return;
    if (!adj.count(carac)) adj[carac] = set<int>();
    adj[carac].insert(to);
}

Node::~Node()
{
    //dtor
}

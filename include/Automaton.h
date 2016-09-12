#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <string>
#include <vector>
#include <algorithm>
#include "Node.h"
using namespace std;
typedef pair<int,int> ii;

class Automaton
{
    public:
        Automaton();
        virtual ~Automaton();
        int getSize(){ return (int)nodes.size(); }
        bool addExpression(int s, int t, string expression);
        bool addExpression(string expression) { return addExpression(root, end, expression); }
        void print();
        void printStates();
        void possibleStates(string expression);
    protected:
    private:
        int root;
        int end;
        int size;
        vector<Node> nodes;
        set<int> endstates;
        bool isCarac(char carac);
        void possibleStatesRecurs(string expression,int index,Node node,map<ii,bool> used);
};

#endif // AUTOMATON_H

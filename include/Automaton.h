#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <string>
#include <vector>
#include "Node.h"
using namespace std;

class Automaton
{
    public:
        Automaton();
        virtual ~Automaton();
        int getSize(){ return (int)nodes.size(); }
        bool addExpression(int s, int t, string expression);
        bool addExpression(string expression) { return addExpression(root, end, expression); }
        void print();
    protected:
    private:
        int root;
        int end;
        int size;
        vector<Node> nodes;
        bool isCarac(char carac);
};

#endif // AUTOMATON_H

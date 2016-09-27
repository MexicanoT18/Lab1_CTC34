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
        bool validExpression(){return endstates.count(1);}
        void possibleStates(string expression);
        void deleteETransitions();
        string getRegExpression();
        void print();
        void printStates();

    protected:
    private:
        int root;
        int end;
        int size;
        vector<Node> nodes;
        vector<string> B;
        vector< vector<string> > A;
        vector< vector<string> > L;
        vector< vector< vector< string > > > R;
        set<int> endstates;

        bool isCarac(char carac);
        bool trans(int i, int j, char carac);
        string star(string str);
        string sum(string str1, string str2);
        string concat(string str1, string str2);
        void possibleStatesRecurs(string expression,int index,Node node,map<ii,bool> &used);
        void findEClusureRecurs(Node node,vector<int> &visited,
                                int id,set<int> &vertices,vector<set<int> > &eClosure);
};

#endif // AUTOMATON_H

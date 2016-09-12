#include "Automaton.h"
#include <cstdio>

Automaton::Automaton()
{
    nodes.clear();
    root = 0;
    end = 1;
    nodes.push_back(Node(root));
    nodes.push_back(Node(end));
}

void Automaton::print(){
    map<char, set<int> >::iterator it;
    set<int>::iterator setit;
    for(int i=0; i<getSize(); i++){
        printf("node #%d:\n", i);
        for(it = nodes[i].adj.begin(); it!=nodes[i].adj.end(); it++){
            printf("   edge %c->", it->first);
            for(setit = it->second.begin(); setit != it->second.end(); setit++){
                printf(" %d", *setit);
            }
            printf("\n");
        }
    }
}

void Automaton::printStates(){
    set<int>::iterator it;
    printf("End States:\n");
    for (it = endstates.begin();it!=endstates.end();it++){
        printf("%d ",*it);
    }
    printf("\n");
}

bool Automaton::isCarac(char carac){
    return (carac >= 'a' && carac <= 'z') ||
        (carac >= 'A' && carac <= 'Z') ||
        (carac >= '0' && carac <= '9') ||
        carac == '&';
}

bool Automaton::addExpression(int s, int t, string expression){

    printf("adding |%s| from %d to %d\n", expression.c_str(), s, t);

    //Check empty string
    if (expression.empty()) return true;

    //Check letter
    if ((int)expression.size() == 1 && isCarac(expression[0])){
        nodes[s].addEdge(expression[0], t);
        return true;
    }


    //Remove brackets
    int openBrackets = 0;
    if (expression.size() >= 2){
        bool eliminate = true;
        for(int i=0; i<(int)expression.size() && eliminate; i++){
            if (expression[i] == '(') openBrackets++;
            if (expression[i] == ')') openBrackets--;
            if (i+1 < (int)expression.size() && openBrackets == 0) eliminate = false;
        }
        if (eliminate) return addExpression(s, t, expression.substr(1, expression.size()-2));
    }

    //Decompose with plus
    openBrackets = 0;
    for(int i=0; i<(int)expression.size(); i++){
        if (expression[i] == '(') openBrackets++;
        if (expression[i] == ')') openBrackets--;
        if (expression[i] == '+' && openBrackets == 0){
            return addExpression(s, t, expression.substr(0, i))
                && addExpression(s, t, expression.substr(i+1));
        }
    }

    //Decompose with concatenation
    openBrackets = 0;
    for(int i=0; i<(int)expression.size(); i++){
        if (i > 0 && openBrackets == 0 && expression[i]!='*'){
            int new_node = (int)nodes.size();
            nodes.push_back(new_node);
            return addExpression(s, new_node, expression.substr(0, i))
                && addExpression(new_node, t, expression.substr(i));
        }
        if (expression[i] == '(') openBrackets++;
        else if (expression[i] == ')') openBrackets--;
    }

    //Decompose with Kleener
    if ((int)expression.size() > 0 && expression[expression.size()-1] == '*'){
            int new_node = (int)nodes.size();
            nodes.push_back(new_node);
            nodes[s].addEdge('&', new_node);
            nodes[new_node].addEdge('&', t);
            return addExpression(new_node, new_node, expression.substr(0, expression.size()-1));
    }

    return false;
}

void Automaton::possibleStatesRecurs(string expression,int index,Node node,map<ii,bool> used){
    int j;
    char letter;

    if (used[ii(index,node.getId())])return;
    used[ii(index,node.getId())]=true;

    if (index == (int)expression.size()){
        endstates.insert(node.getId());
        j = 1;
        letter = '&';
    }else {
        j=0;
        letter = expression[index];
    }
    set<int>::iterator it;
    for (; j<2; j++)
    {
        for (it = node.adj[letter].begin(); it!=node.adj[letter].end(); it++)
        {
            possibleStatesRecurs(expression,index+1-j,nodes[*it],used);
        }
        letter = '&';
    }
}

void Automaton::possibleStates(string expression){
    endstates.clear();
    map<ii,bool> used;
    possibleStatesRecurs(expression,0,nodes[0],used);
}

Automaton::~Automaton()
{
    //dtor
}

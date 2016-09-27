#include "Automaton.h"
#include <cstdio>

Automaton::Automaton()
{
    nodes.clear();
    root = 0;
    end = 1;
    nodes.push_back(Node(root));
    nodes.push_back(Node(end));
    nodes[1].setIsFinal();
}

void Automaton::print(){
    map<char, set<int> >::iterator it;
    set<int>::iterator setit;
    for(int i=0; i<getSize(); i++){
        printf("node #%d: %d\n", i,nodes[i].getIsFinal()?1:0);
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

    //printf("adding |%s| from %d to %d\n", expression.c_str(), s, t);

    //Check empty strinmap<ii,bool> used;g
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

void Automaton::possibleStatesRecurs(string expression,int index,Node node,map<ii,bool> &used){
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
    map<ii,bool> used;
    endstates.clear();
    used.clear();
    possibleStatesRecurs(expression,0,nodes[0],used);
}

void Automaton::findEClusureRecurs(Node node,vector<int> &visited,
                                   int id,set<int> &vertices,vector<set<int> > &eClosure){
    if (visited[node.getId()]>0)return;
    visited[node.getId()]=1;
    char letter = '&';

    set<int>::iterator it;
    for (it = node.adj[letter].begin(); it!=node.adj[letter].end(); it++)
    {
        findEClusureRecurs(nodes[*it],visited,id,vertices,eClosure);
        vertices.insert(*it);
    }
}

void Automaton::deleteETransitions(){
    vector<int> visited;
    vector<set<int> > eClosure;
    set<int> v,u;

    //Computa o E-fecho de cada estado

    for (int i=0;i<(int)nodes.size();i++){
        visited.assign(nodes.size(),-1);
        v.clear();
        findEClusureRecurs(nodes[i],visited,i,v,eClosure);
        eClosure.push_back(v);
    }
    //Todo arco de A em X gera um arco de A em Y para cada Y no e-fecho(X)

    map<char, set<int> >::iterator it;
    vector<Node> auxnodes;
    set<int>::iterator it2,it3;
    char letter;

    auxnodes = nodes;

    for (int i=0;i<(int)nodes.size();i++){
        for (it = nodes[i].adj.begin();it!=nodes[i].adj.end();it++){
            letter = (*it).first;
            if (letter=='&')continue;
            v = (*it).second;
            for (it2=v.begin();it2!=v.end();it2++){
                u = eClosure[*it2];
                for (it3=u.begin();it3!=u.end();it3++){
                    auxnodes[i].adj[letter].insert(*it3);
                }
            }
        }
    }


    //todo arco de Y em A para qualquer Y no E-fecho(X) gera um arco de X para A.

    for (int i=0;i<(int)nodes.size();i++){
        u = eClosure[i];
        for (it2=u.begin();it2!=u.end();it2++){
            for (it = nodes[*it2].adj.begin();it!=nodes[*it2].adj.end();it++){
                letter = (*it).first;
                if (letter=='&')continue;
                v = (*it).second;
                for (it3=v.begin();it3!=v.end();it3++){
                    auxnodes[i].adj[letter].insert(*it3);
                }
            }
        }
    }

    //Adiciona os elementos de auxnode para nodes

    for (int i=0;i<(int)nodes.size();i++)
    {
        for (it = auxnodes[i].adj.begin();it!=auxnodes[i].adj.end();it++){
            nodes[i].adj[it->first].insert(it->second.begin(),it->second.end());
        }


    }

    //Determinação dos novos estados finais

    for (int i=0;i<(int)nodes.size();i++){
        if (eClosure[i].count(1))nodes[i].setIsFinal();
        nodes[i].adj['&'].clear();
    }
}

bool Automaton::trans(int i, int j, char carac){
    return nodes[i].adj[carac].count(j);
}

string Automaton::star(string str){
    if (str == "") return "";
    if (str == "&") return "&";
    return "(" + str + ")*";
}

string Automaton::sum(string str1, string str2){
    if (str1 == str2) return str1;
    else if (str1 == "") return str2;
    else if (str2 == "") return str1;
    else return str1 + "+" + str2;
}

string Automaton::concat(string str1, string str2){
    if (str1.size() == 0 || str2.size() == 0) return "";
    else if (str1 == "&") return str2;
    else if (str2 == "&") return str1;
    else return str1 + str2;
}

string Automaton::getRegExpression(){

    size = (int)nodes.size();

    L.resize(size);
    for(int i=0; i<size; i++){
        L[i].resize(size);
        for(int j=0; j<size; j++){
            if (i == j) L[i][j] = "&";
            else L[i][j] = "";
            for(char a='a'; a<='z'; a++){
                if (trans(i, j, a)){
                    L[i][j] = sum(L[i][j], string() + a);
                }
            }
        }
    }

    for(int k=0; k<size; k++){
        if (k == root || k == end) continue;
        for(int j=0; j<size; j++){
            for(int i=0; i<size; i++){
                L[i][i] = sum(L[i][i], concat(L[i][k], concat(star(L[k][k]), L[k][i])));
                L[j][j] = sum(L[j][j], concat(L[j][k], concat(star(L[k][k]), L[k][j])));
                L[i][j] = sum(L[i][j], concat(L[i][k], concat(star(L[k][k]), L[k][j])));
                L[j][i] = sum(L[j][i], concat(L[j][k], concat(star(L[k][k]), L[k][i])));
            }
        }
    }
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            printf("L[%d][%d] = %s ", i, j, L[i][j].c_str());
        }
        printf("\n");
    }

    return concat(concat(star(L[root][root]), L[root][end]), star(sum(concat(concat(L[end][root], star(L[root][root])), L[root][end]), L[end][end])));
}

Automaton::~Automaton()
{
    //dtor
}

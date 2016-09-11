#ifndef NODE_H
#define NODE_H

#include <map>
#include <set>
using namespace std;

class Node
{
    public:
        Node(int id);
        virtual ~Node();
        void addEdge(char carac, int to);
        map<char, set<int> > adj;
        int getId() { return _id; }
    protected:
    private:
        int _id;
};

#endif // NODE_H

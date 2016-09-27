#ifndef IDSET_H
#define IDSET_H

#include <set>
using namespace std;

class IdSet
{
    public:
        IdSet();
        virtual ~IdSet();
        bool count(int id);
        set<int> getSet() { return _ids; }
        bool add(int id);
        bool operator < (const IdSet other);
        bool operator == (const IdSet other);
    protected:
    private:
        set<int> _ids;
};

#endif // IDSET_H

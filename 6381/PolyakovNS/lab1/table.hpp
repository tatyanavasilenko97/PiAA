 #ifndef TABLE_H
#define TABLE_H

#include "square.hpp"
#include "point.hpp"

class table{
private:
    int sidelen;
    bool **array;
    int num;
    
    
    square *current;
    inline bool get(int,int);
    inline void set(int,int,bool);
    bool full();
    point findfirstfree();
    bool addsquare(point,int);
    void delsquare(square);
    void nextsquare();
public:
    int maxnum;
    square *squares;
    void zerotable();
    void findmin();
    void print();
    void setmax();
    table();
    table(int len);
    ~table();
};

#include "table.cpp"

#endif

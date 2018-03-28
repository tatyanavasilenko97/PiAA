#ifndef POINT_H
#define POINT_H

class point{
private:
    int x;
    int y;
public:
    point();
    point(int a, int b);
    void set(int a, int b);
    int getx();
    int gety();
};

#include "point.cpp"

#endif

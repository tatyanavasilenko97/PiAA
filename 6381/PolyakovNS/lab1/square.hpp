#ifndef SQUARE_H
#define SQUARE_H

#include "point.hpp"

class square{
private:
    point ld;
    int sidelen;
public:
    point getld();
    int getside();
    void setld(point x, int len);
    square();
    square(point x,int len);
};

#include "square.cpp"

#endif

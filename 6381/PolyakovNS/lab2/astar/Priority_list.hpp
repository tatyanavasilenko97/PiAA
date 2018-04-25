#pragma once
class Priority_list;
#include "Edge.hpp"
#include "Vertex.hpp"

struct item{
    item *next;
    Vertex *ver;
    double priority;
    item(double p,Vertex * v, item *n)
    :priority(p), ver(v),next(n){}
};

class Priority_list{
private:
    item *head;
    char end;
public:
    void push(Vertex*,double);
    Vertex* pop();
    void pop(Vertex*);
    Priority_list(char);
};

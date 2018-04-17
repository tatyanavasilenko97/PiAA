#pragma once
class Edge;
#include "Vertex.hpp"
#include "Priority_list.hpp"

class Edge{
private:
    double weight;
    Vertex *end;
    Edge *next;
public:
    void setWeight(double);
    void setEnd(Vertex*);
    void setNext(Edge*);
    double getWeight();
    Vertex* getEnd();
    Edge*& getNext();
    Edge(double,Vertex*);
    void addToList(Priority_list&,Vertex*);
};


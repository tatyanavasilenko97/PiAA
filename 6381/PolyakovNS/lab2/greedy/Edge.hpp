#pragma once
class Edge;
#include "Vertex.hpp"


class Edge{
private:
    Vertex *first;
    Vertex *second;
    double weight;
public:
    void setFirst(Vertex*);
    void setSecond(Vertex*);
    void setWeight(double);
    double getWeight();
    Vertex* getFirst();
    Vertex* getSecond();
    Edge(double,Vertex*,Vertex*);
};


#pragma once
class Edge;
#include "Vertex.hpp"


class Edge{
private:
    Vertex *first;
    Vertex *second;
    unsigned int weight;
    unsigned int stream;
public:
    void setFirst(Vertex*);
    void setSecond(Vertex*);
    void setWeight(unsigned int);
    void setStream(unsigned int);
    unsigned int getStream();
    unsigned int getWeight();
    Vertex* getFirst();
    Vertex* getSecond();
    Edge(double,Vertex*,Vertex*);
    Edge();
};


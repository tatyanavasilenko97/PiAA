#pragma once
class Vertex;
#include <vector>
#include "Edge.hpp"


class Vertex{
private:
    Vertex *prev;
    char name;
    bool vizited;
    std::vector<Edge> edges;
public:
    void setName(char);
    char getName();
    void addEdge(Edge);
    void setPrev(Vertex*);
    void setVizited(bool);
    bool getVizited();
    Vertex* getPrev();
    Vertex* findMin();
    Vertex(char);
};

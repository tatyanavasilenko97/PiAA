#pragma once
class Vertex;
#include <vector>
#include "Edge.hpp"


class Vertex{
private:
    Vertex *prev;
    unsigned int mark;
    char name;
    bool vizited;
    std::vector<Edge> edges;
public:
    void setName(char);
    char getName();
    void addEdge(Edge);
    void setPrev(Vertex*);
    void setVizited(bool);
    void setMark(unsigned int);
    unsigned int getMark();
    bool getVizited();
    Vertex* getPrev();
    Vertex* findMin();
    Vertex(char);
    Vertex* findNextVer();
    Edge* findEdge(Vertex*);
    std::vector<Edge>& getEdges();
};

#pragma once
#include <vector>
#include <algorithm>
#include "Vertex.hpp"

class Graph{
private:
    std::vector<Vertex*> list_of_Vertexes;
    Vertex *start;
    Vertex *end;
    
public:
    Vertex* addVertex(char);
    void addEdge(char,char,double);
    void delVertex(Vertex*);
    unsigned int findMaxStream(char,char);
    unsigned int findPath();
    void printStream();
    Vertex* findVertex(char);
    void setNotVisited();
};

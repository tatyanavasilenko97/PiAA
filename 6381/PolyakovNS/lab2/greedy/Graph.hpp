#pragma once
#include <vector>
#include <string>
#include "Vertex.hpp"

class Graph{
private:
    std::vector<Vertex*> list_of_Vertexes;
    std::string path;
public:
    Vertex* addVertex(char);
    void addEdge(char,char,double);
    void delVertex(Vertex*);
    bool notvizited(char);
    Vertex* findVertex(char);
    std::string greedy(char,char);
};

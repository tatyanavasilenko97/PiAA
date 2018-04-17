#pragma once
class Graph;
#include <string>
#include "Vertex.hpp"

class Graph{
private:
    Vertex *head;
    int number;
public:
    Vertex* addVertex(char ch);
    void addEdge(char first, char second, double weight);
    std::string AStar(char,char);
    Vertex* findVertex(char);
    Graph();
};

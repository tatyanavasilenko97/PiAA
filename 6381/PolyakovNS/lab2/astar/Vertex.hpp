#pragma once
class Vertex;
#include "Edge.hpp"
#include "Priority_list.hpp"

class Vertex{
private:
    char name;
    int count;
    bool visited;
    double path;
    Vertex *prevVisited;
    Vertex *next;
    Vertex *prev;
    Edge *trail;
public:
    char getName();
    bool getVisited();
    double getPath();
    Vertex* getPrevVisited();
    Vertex* getPrev();
    Vertex* getNext();
    void setName(char);
    void setVisited(bool);
    void setPath(double);
    void setPrevVisited(Vertex*);
    void setPrev(Vertex*);
    void setNext(Vertex*);
    Vertex(char);
    void addEdge(double,Vertex*);
    void addToVisited(Priority_list&);
};

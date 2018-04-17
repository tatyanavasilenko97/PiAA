#include "Vertex.hpp"

Vertex::Vertex(char ch){
    visited = false;
    name = ch;
    count = 0;
    next = nullptr;
    prev = nullptr;
    trail = nullptr;
    path = 0;
}

void Vertex::addEdge(double weight,Vertex *other){
    if(trail == nullptr){
        trail = new Edge(weight, other);
        trail->getNext() = nullptr;
    }
    else{
        Edge *it = trail;
        while(it->getNext() != nullptr) it = it->getNext();
        it->getNext() = new Edge(weight, other);
        it->getNext()->getNext() = nullptr;
        
    }
}

void Vertex::addToVisited(Priority_list& list){
    visited = true;
    Edge *it = trail;
    while(it != nullptr){
        if(!it->getEnd()->getVisited()) it->addToList(list,this);
        it = it->getNext();
    }
}

char Vertex::getName(){
    return name;
}
bool Vertex::getVisited(){
    return visited;
}
double Vertex::getPath(){
    return path;
}
Vertex* Vertex::getPrevVisited(){
    return prevVisited;
}
Vertex* Vertex::getPrev(){
    return prev;
}
Vertex* Vertex::getNext(){
    return next;
}
void Vertex::setName(char x){
    name = x;
}
void Vertex::setVisited(bool x){
    visited = x;
}
void Vertex::setPath(double x){
    path = x;
}
void Vertex::setPrevVisited(Vertex* x){
    prevVisited = x;
}
void Vertex::setPrev(Vertex* x){
    prev = x;
}
void Vertex::setNext(Vertex* x){
    next = x;
}

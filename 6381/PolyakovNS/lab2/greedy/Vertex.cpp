#include "Vertex.hpp"

Vertex* Vertex::findMin(){
    double min = -1;
    Vertex *closest;
    for(int i = 0; i < edges.size(); ++i){
        if(edges[i].getSecond()->getVizited() == false){
            min = edges[i].getWeight();
            break;
        }
    }
    if(min == -1) return nullptr;
    for(int i = 0; i < edges.size(); ++i){
        if(edges[i].getSecond()->getVizited() == false && edges[i].getWeight() <= min){
            min = edges[i].getWeight();
            closest = edges[i].getSecond();
        }
    }
    return closest;
}

void Vertex::addEdge(Edge newEdge){
    if(newEdge.getFirst()->getName() == name){
        edges.push_back(newEdge);
    }
    else{
        edges.push_back(Edge(newEdge.getWeight(),newEdge.getSecond(),newEdge.getFirst()));
    }
}

Vertex* Vertex::getPrev(){
    return prev;
}

void Vertex::setPrev(Vertex *p){
    prev = p;
}

bool Vertex::getVizited(){
    return vizited;
}

void Vertex::setVizited(bool x){
    vizited = x;
}

void Vertex::setName(char ch){
    name =ch;
    vizited = false;
    prev=nullptr;
}

char Vertex::getName(){
    return name;
}

Vertex::Vertex(char ch){
    vizited = false;
    name = ch;
}

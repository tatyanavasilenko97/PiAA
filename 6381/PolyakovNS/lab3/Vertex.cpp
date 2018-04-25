#include "Vertex.hpp"

void Vertex::addEdge(Edge newEdge){
    if(newEdge.getFirst()->getName() == name){
        edges.push_back(newEdge);
    }
    else{
        edges.push_back(Edge(newEdge.getWeight(),newEdge.getSecond(),newEdge.getFirst()));
    }
}

Vertex* Vertex::findNextVer(){
    Edge finded;
    for(int i = 0 ; i < edges.size() ; ++i){
        if(edges[i].getSecond()->getVizited() == false && edges[i].getWeight() != 0){
            finded = edges[i];
            break;
        }
    }
    if(finded.getWeight() == 0) return nullptr;
    for(int i = 0 ; i < edges.size() ; ++i){
        if(edges[i].getSecond()->getVizited() == false && edges[i].getWeight() > finded.getWeight()){
            finded = edges[i];
        }
    }
    return finded.getSecond();
}

Edge* Vertex::findEdge(Vertex* x){
    for(int i = 0 ; i < edges.size() ; ++i){
        if(edges[i].getSecond() == x) return &edges[i];
    }
    return nullptr;
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

void Vertex::setMark(unsigned int x){
    mark = x;
}
unsigned int Vertex::getMark(){
    return mark;
}

std::vector<Edge>& Vertex::getEdges(){
    return edges;
}

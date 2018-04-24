#include "Edge.hpp"

void Edge::setFirst(Vertex* new_first){
    first = new_first;
}
void Edge::setSecond(Vertex* new_second){
    second = new_second;
}
Vertex* Edge::getFirst(){
    return first;
}
Vertex* Edge::getSecond(){
    return second;
}

void Edge::setWeight(unsigned int new_weight){
    weight = new_weight;
}

unsigned int Edge::getWeight(){
    return weight;
}

Edge::Edge(double x, Vertex *new_first, Vertex *new_second){
    weight = x;
    first = new_first;
    second = new_second;
    stream = 0;
}

Edge::Edge(){
    weight = 0;
    stream = 0;
    first = nullptr;
    second = nullptr;
}

void Edge::setStream(unsigned int x){
    stream = x;
}
unsigned int Edge::getStream(){
    return stream;
}

#include "Edge.hpp"

Edge::Edge(double x, Vertex *y){
    weight = x;
    end = y;
    next = nullptr;
}

void Edge::addToList(Priority_list& list,Vertex* prev_v){
    if(end->getPrevVisited() == nullptr){
        end->setPath(prev_v->getPath() + weight);
        end->setPrevVisited(prev_v);
        list.push(end,weight + prev_v->getPath());
    }
    else{
        if(prev_v->getPath() + weight < end->getPath()){
            end->setPath(prev_v->getPath() + weight);
            end->setPrevVisited(prev_v);
            list.pop(end);
            list.push(end, end->getPath());
        }
    }
}

void Edge::setWeight(double x){
    weight = x;
}
void Edge::setEnd(Vertex* x){
    end = x;
}
void Edge::setNext(Edge* x){
    next = x;
}
double Edge::getWeight(){
    return weight;
}
Vertex* Edge::getEnd(){
    return end;
}
Edge*& Edge::getNext(){
    return next;
}

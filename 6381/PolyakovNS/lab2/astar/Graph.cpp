#include "Graph.hpp"

Vertex* Graph::addVertex(char ch){
    if(head == nullptr){
        head = new Vertex(ch);
        return head;
    }
    Vertex *it = findVertex(ch);
    if(it != nullptr) return it;
    
    head->setPrev(new Vertex(ch));
    head->getPrev()->setNext(head);
    head = head->getPrev();
    number++;
    return head;
}
void Graph::addEdge(char first, char second, double weight){
    Vertex *first_v = addVertex(first);
    Vertex *second_v = addVertex(second);
    first_v->addEdge(weight,second_v);
    second_v->addEdge(weight,first_v);
}

Graph::Graph(){
    head = nullptr;
}

Vertex* Graph::findVertex(char ch){
    Vertex *it = head;
    if(head == nullptr) return nullptr;
    while(it->getName() != ch ){
        if(it->getNext() == nullptr) return nullptr;
        it = it->getNext();
    }
    return it;
}

std::string Graph::AStar(char start, char end){
    Priority_list openedVer(end);
    Vertex *start_v = findVertex(start);
    Vertex *end_v = findVertex(end);
    Vertex *current = start_v;
    while(true){
        if(current == end_v || current == nullptr) break;
        current->addToVisited(openedVer);
        current = openedVer.pop();
    }
    std::string path;
    current = end_v;
    while(current != start_v){
        path.insert(0,1,current->getName());
        current = current->getPrevVisited();
    }
    path.insert(0,1,start_v->getName());
    return path;
}

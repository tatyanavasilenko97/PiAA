#include "Graph.hpp"

std::string Graph::greedy(char start, char end){
    Vertex *start_v=nullptr;
    Vertex *end_v=nullptr;
    for(int i = 0 ; i < list_of_Vertexes.size(); i++){
        if( list_of_Vertexes[i]->getName() == start) start_v = list_of_Vertexes[i];
        if( list_of_Vertexes[i]->getName() == end) end_v = list_of_Vertexes[i];
    }
    Vertex *current = start_v;
    start_v->setPrev(nullptr);
    while(true){
        if(current == end_v && current == nullptr) break;
        path.push_back(current->getName());
        current->setVizited(true);
        Vertex *next = current->findMin();
        if(next == end_v){
            path.push_back(end_v->getName());
            return path;
        }
        if(next == nullptr){
            current = current->getPrev();
            path.pop_back();
            path.pop_back();
            continue;
        }
        next->setPrev(current);
        current = next;
    }
    return path;
}

Vertex* Graph::addVertex(char ch){
    for(int i = 0; i < list_of_Vertexes.size(); i++){
        if(list_of_Vertexes[i]->getName() == ch) return list_of_Vertexes[i];
    }
    Vertex* new_ver = new Vertex(ch);
    list_of_Vertexes.push_back(new_ver);
    return new_ver;
}

void Graph::addEdge(char edge_start, char edge_end, double weight){
    Vertex *first_Vertex = addVertex(edge_start);
    Vertex *second_Vertex = addVertex(edge_end);
    Edge new_edge = Edge(weight, first_Vertex, second_Vertex);
    first_Vertex->addEdge(new_edge);
}

Vertex* Graph::findVertex(char ch){
    for(int i=0;i<list_of_Vertexes.size();++i){
        if(list_of_Vertexes[i]->getName() == ch) return list_of_Vertexes[i];
    }
    return nullptr;
}

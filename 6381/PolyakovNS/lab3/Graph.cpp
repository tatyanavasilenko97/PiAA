#include "Graph.hpp"

bool cmpVerPtr(Vertex *x, Vertex *y){
    return x->getName() < y->getName();
}

bool cmpEdgeMin(Edge x, Edge y){
    return x.getSecond()->getName() < y.getSecond()->getName();
}

bool cmpEdgeMax(Edge x, Edge y){
    return x.getSecond()->getName() > y.getSecond()->getName();
}

struct PointerCompare {
    bool operator()(const Vertex *x, const Vertex *y) {
        return ((Vertex*)x)->getName() < ((Vertex*)y)->getName();
    }
};

unsigned int Graph::findMaxStream(char start_ch, char end_ch){
    for(int i = 0 ; i < list_of_Vertexes.size() ; ++i){
    }
    start = findVertex(start_ch);
    end = findVertex(end_ch);
    unsigned int max_stream = 0;
    unsigned int cur_stream = 1;
    while(cur_stream != 0){
        cur_stream = findPath();
        setNotVisited();
        max_stream += cur_stream;
    }
    for(int i = 0 ; i < list_of_Vertexes.size() ; ++i){
        for(int j = 0 ; j < list_of_Vertexes[i]->getEdges().size(); ++j){
            if(list_of_Vertexes[i]->getEdges()[j].getSecond()->findEdge(list_of_Vertexes[i]) != nullptr){
                unsigned int forward = list_of_Vertexes[i]->getEdges()[j].getStream();
                unsigned int backward = list_of_Vertexes[i]->getEdges()[j].getSecond()->findEdge(list_of_Vertexes[i])->getStream();
                if(forward != 0 && backward != 0){
                    if(forward > backward){
                        list_of_Vertexes[i]->getEdges()[j].setStream(forward - backward);
                        list_of_Vertexes[i]->getEdges()[j].getSecond()->findEdge(list_of_Vertexes[i])->setStream(0);
                    }
                    else{
                        list_of_Vertexes[i]->getEdges()[j].getSecond()->findEdge(list_of_Vertexes[i])->setStream(backward - forward);
                        list_of_Vertexes[i]->getEdges()[j].setStream(0);
                    }
                }
            }
        }
    }
    return max_stream;
}

void Graph::printStream(){
    std::sort(list_of_Vertexes.begin(),list_of_Vertexes.end(),cmpVerPtr);
    for(int i = 0 ; i < list_of_Vertexes.size() ; ++i){
        std::sort(list_of_Vertexes[i]->getEdges().begin(),list_of_Vertexes[i]->getEdges().end(), cmpEdgeMin);
        for(int j = 0 ; j < list_of_Vertexes[i]->getEdges().size(); ++j){
            std::cout << list_of_Vertexes[i]->getName() << " " << list_of_Vertexes[i]->getEdges()[j].getSecond()->getName() << " " << list_of_Vertexes[i]->getEdges()[j].getStream() << std::endl;
        }
    }
}

unsigned int Graph::findPath(){
    Vertex * cur = start;
    start->setVizited(true);
    while(true){
        if(cur == end) break;
        Vertex *next = cur->findNextVer();
        if(next == nullptr){
            if(cur == start) break;
            Vertex *tmp = cur;
            cur = cur->getPrev();
            tmp->setPrev(nullptr);
            continue;
        }
        next->setVizited(true);
        next->setPrev(cur);
        next->setMark(cur->findEdge(next)->getWeight());
        cur = next;
    }
    if(cur == start) return 0;
    else{
        unsigned int result = end->getMark();
        while(cur != start){
            result = std::min(result,cur->getMark());
            cur = cur->getPrev();
        }
        cur = end;
        std::string path;
        while(cur != start){
            Vertex *next = cur;
            path.insert(path.begin(),cur->getName());
            cur = cur->getPrev();
            Edge *cur_edge = cur->findEdge(next);
            cur_edge->setStream(result + cur_edge->getStream());
            cur_edge->setWeight(cur_edge->getWeight() - result);
        }
        return result;
    }
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

void Graph::setNotVisited(){
    for(int i = 0 ; i < list_of_Vertexes.size() ; ++i){
        list_of_Vertexes[i]->setVizited(false);
    }
}









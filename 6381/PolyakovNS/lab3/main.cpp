#include <iostream>
#include <fstream>
#include "Graph.hpp"

int main(){
    Graph my_graph;
    int number;
    char start, end;
    std::ifstream file;
    file.open("input.txt",std::ios::in);
    file >> number >> start >> end;
    char edge_start;
    char edge_end;
    unsigned int weight;
    for(int i = 0 ; i < number ; ++i){
        file >> edge_start >> edge_end >> weight;
        my_graph.addEdge(edge_start, edge_end, weight);
    }
    std::cout << my_graph.findMaxStream(start, end);
    std::cout << std::endl;
    my_graph.printStream();
    return 0;
}

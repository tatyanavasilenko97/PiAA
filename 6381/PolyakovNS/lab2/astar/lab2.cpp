#include <iostream>
#include <fstream>
#include "Edge.hpp"
#include "Vertex.hpp"
#include "Graph.hpp"

int main(){
    Graph my_graph;
    char start, end;
    std::ifstream file;
    file.open("input.txt",std::ios::in);
    file >> start >> end;
    char edge_start;
    char edge_end;
    double weight;
    while(file >> edge_start >> edge_end >> weight){
        my_graph.addEdge(edge_start, edge_end, weight);
    }
    std::cout << my_graph.AStar(start, end) << std::endl;
    return 0;
}

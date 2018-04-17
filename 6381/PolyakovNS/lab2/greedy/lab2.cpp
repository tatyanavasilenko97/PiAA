#include <iostream>
#include "Edge.hpp"
#include "Vertex.hpp"
#include "Graph.hpp"

int main(){
    Graph my_graph;
    char start, end;
    std::cin >> start >> end;
    char edge_start;
    char edge_end;
    double weight;
    while(std::cin >> edge_start >> edge_end >> weight){
        my_graph.addEdge(edge_start, edge_end, weight);
    }
    std::cout << my_graph.greedy(start, end) << std::endl;
    return 0;
}

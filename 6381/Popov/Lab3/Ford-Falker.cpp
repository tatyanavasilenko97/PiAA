#include <iostream>
#include <list>
#include <map>
#include <stack>
#include <algorithm>
#include <vector>
#include <conio.h>
#include <fstream>

using namespace std;

class Vertex;

class Curve{
public:
    Vertex* source;
    Vertex* outlet;
    int max_capacity;
    int curr_capacity;
	
    Curve(Vertex* source, Vertex* outlet, int max_capacity) : source(source), outlet(outlet),
                                                              max_capacity(max_capacity), curr_capacity(0) {}
};

class Vertex{
    char name;
    bool visited;

public:
    vector<Curve*> neighbours;

    Vertex(char name) : name(name), visited(0){};
    char getName() const;
    bool isVisited() const;
    void setVisited(bool flag);
};

class Graph{
public:
    vector<Vertex*> list_ver;
    map<Vertex*, Curve*> came_from;
    stack<pair<Curve*, bool>> next_vertex;

    Vertex* getVertex(char name);
    void visitVertex(Vertex* vertex, Vertex* point_to);
    void findMaxFlow(Vertex* point_from, Vertex* point_to);
    int findMinimum(Vertex* point_from, Vertex* point_to);
    void setMinimum(Vertex* point_to, int minimum);
    void printAnswer(Vertex* point_from);
};

Vertex* Graph::getVertex(char name) {
    for(Vertex* vertex : list_ver)
        if(vertex->getName() == name)
            return vertex;
    return nullptr;
}

char Vertex::getName() const {
    return name;
}

bool Vertex::isVisited() const {
    return visited;
}

void Vertex::setVisited(bool flag) {
    visited = flag;
}

Graph *buildGraph(){
	char choice, ver_a, ver_b;
	bool readFromFile;
	int size, capacity;
	Graph *graph = new Graph;
	while(1){
		cout << "Input graph from file? (y/n) ";
		choice = getch();
		cout << endl;
		switch (choice){
			case 'y':{
				ifstream fin;
				fin.open("GraphForFord.txt");
				if(!fin){
					cout << "File wasnt founded\n";
					system("pause");
					break;
				}
				fin >> size >> ver_a >> ver_b;
				Vertex* point_from = new Vertex(ver_a);
				Vertex* point_to = new Vertex(ver_b);
				graph->list_ver.push_back(point_from);
				graph->list_ver.push_back(point_to);
				for(int i = 0; i < size; i++){					
					fin >> ver_a >> ver_b >> capacity;
					point_from = graph->getVertex(ver_a);
					point_to = graph->getVertex(ver_b);
					if(point_from == nullptr) {
						point_from = new Vertex(ver_a);
						graph->list_ver.push_back(point_from);
					}
					if(point_to == nullptr) {
						point_to = new Vertex(ver_b);
						graph->list_ver.push_back(point_to);
					}
					point_from->neighbours.push_back(new Curve(point_from, point_to, capacity));
					point_to->neighbours.push_back(new Curve(point_from, point_to, capacity));
				}
				fin.close();
				return graph;
			}
			case 'n':{
				cin >> size >> ver_a >> ver_b;
				Vertex* point_from = new Vertex(ver_a);
				Vertex* point_to = new Vertex(ver_b);
				graph->list_ver.push_back(point_from);
				graph->list_ver.push_back(point_to);
				for(int i = 0; i < size; i++){					
					cin >> ver_a >> ver_b >> capacity;
					point_from = graph->getVertex(ver_a);
					point_to = graph->getVertex(ver_b);
					if(point_from == nullptr) {
						point_from = new Vertex(ver_a);
						graph->list_ver.push_back(point_from);
					}
					if(point_to == nullptr) {
						point_to = new Vertex(ver_b);
						graph->list_ver.push_back(point_to);
					}
					point_from->neighbours.push_back(new Curve(point_from, point_to, capacity));
					point_to->neighbours.push_back(new Curve(point_from, point_to, capacity));
				}
				return graph;
			}
			default:
				printf("Repeat command\n");
		}
	}
	return graph;
}
//!!!!!!!!main!!!!!!!!!!
int main(){
	Graph *graph = buildGraph();
	Vertex *point_start = graph->list_ver[0];
	Vertex *point_end = graph->list_ver[1];
    graph->findMaxFlow(point_start, point_end);
    return 0;
}
//!!!!!!!!!!!!!!!!!!!!!
void Graph::findMaxFlow(Vertex* point_from, Vertex* point_to){
    next_vertex.emplace(new Curve(nullptr, point_from, 0), true);
    came_from[point_from] = nullptr;
    Vertex* current = nullptr;
    while(!next_vertex.empty()) {
        if(next_vertex.top().second)
            current = next_vertex.top().first->outlet;
        else
            current = next_vertex.top().first->source;
        came_from[current] = next_vertex.top().first;
        next_vertex.pop();
        if(current == point_to) {
            setMinimum(point_to, findMinimum(point_from, point_to));
            continue;
        }
        visitVertex(current, point_to);
    }
    printAnswer(point_from);
}

void Graph::visitVertex(Vertex* vertex, Vertex* point_to){
    vertex->setVisited(true);
    sort(vertex->neighbours.begin(), vertex->neighbours.end(), [vertex, point_to](Curve* const& a, Curve* const& b) {
        Vertex* first = a->source == vertex ? a->outlet : a->source;
        Vertex* second = b->source == vertex ? b->outlet : b->source;
        if(first == point_to || second == point_to) 
            return false;
        return first->getName() > second->getName();
    });
    for(Curve* elem : vertex->neighbours){
        if(elem->source == vertex && !elem->outlet->isVisited() && elem->curr_capacity != elem->max_capacity)
            next_vertex.emplace(elem, true);
        else 
			if(elem->outlet == vertex && !elem->source->isVisited() && elem->curr_capacity != 0)
				next_vertex.emplace(elem, false);
    }
}

int Graph::findMinimum(Vertex* point_from, Vertex* point_to){
    int minimum = 1000;
    Curve* current = came_from[point_to];
    Vertex* prev_node = point_to;
    while(prev_node != point_from){
        if(current->outlet == prev_node){
            if((current->max_capacity - current->curr_capacity) < minimum) 
                minimum = current->max_capacity - current->curr_capacity;
            prev_node = current->source;
        } 
		else{
            if(current->curr_capacity < minimum)
                minimum = current->curr_capacity;
            prev_node = current->outlet;
        }
        current = came_from[prev_node];
    }
    return minimum;
}

void Graph::setMinimum(Vertex* point_to, int minimum){
    Curve* current = came_from[point_to];
    Vertex* prev_node = point_to;
    bool flag = true;
    while(current != nullptr){
        if(!next_vertex.empty()){
            if((next_vertex.top().second && next_vertex.top().first->source == prev_node) ||
               (!next_vertex.top().second && next_vertex.top().first->outlet == prev_node))
                flag = false;
            if(flag)
                prev_node->setVisited(false);
        }
        if(current->outlet == prev_node){
            current->curr_capacity += minimum;
            prev_node = current->source;
        }
		else 
			if(current->source == prev_node){
				current->curr_capacity -= minimum;
				prev_node = current->outlet;
			}
        current = came_from[prev_node];
    }
}

void Graph::printAnswer(Vertex* point_from){
    int max_flow = 0;
    for(Curve* elem: point_from->neighbours)
        max_flow += elem->curr_capacity;
    cout << max_flow << endl;
    list<Curve*> fact;
    for(Vertex* vertex : list_ver)
        for(Curve* edge : vertex->neighbours)
            if(vertex == edge->source)
                fact.push_back(edge);
    fact.sort([](Curve* const& a, Curve* const& b) {
        if(a->source->getName() == b->source->getName())
            return a->outlet->getName() < b->outlet->getName();
        return a->source->getName() < b->source->getName();
    });
    for(Curve* edge : fact)
        cout << edge->source->getName() << " " << edge->outlet->getName() << " " << edge->curr_capacity << endl;
}

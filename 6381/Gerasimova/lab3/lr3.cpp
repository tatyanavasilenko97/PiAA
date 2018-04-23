#include <iostream>
#include <list>
#include <map>
#include <string>
#include <stack>
#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

class Node;

struct Edge {
    Edge(Node* source, Node* destination, int max_capacity) : source(source), destination(destination),
                                                              max_capacity(max_capacity), curr_capacity(0) {}

    Node* source;
    Node* destination;
    int curr_capacity;
    int max_capacity;
};

class Node {
private:
    char name;
    bool visited;

public:
    Node(char name) : name(name), visited(false) {};

    vector<Edge*> neighbours;

    char getName() const;

    bool isVisited() const;

    void setVisited(bool flag);
};


class Graph {
public:
    vector<Node*> nodes;

    map<Node*, Edge*> came_from;

    stack<pair<Edge*, bool>> next_nodes;

    Node* getNode(char name);

    void visitNode(Node* node, Node* point_to);

    void findMaxFlow(Node* point_from, Node* point_to);

    int findMinimum(Node* point_from, Node* point_to);

    void setMinimum(Node* point_to, int minimum);

    void printAnswer(Node* point_from);
};


int main() {
    char name_a, name_b;
    int capacity, size;
    cin >> size >> name_a >> name_b;
    auto* point_start = new Node(name_a);
    auto* point_end = new Node(name_b);
    auto* graph = new Graph;
    graph->nodes.push_back(point_start);
    graph->nodes.push_back(point_end);

    Node* point_from;
    Node* point_to;
    for(int i = 0; i < size; i++) {
        cin >> name_a >> name_b >> capacity;
        point_from = graph->getNode(name_a);
        point_to = graph->getNode(name_b);

        if(point_from == nullptr) {
            point_from = new Node(name_a);
            graph->nodes.push_back(point_from);
        }
        if(point_to == nullptr) {
            point_to = new Node(name_b);
            graph->nodes.push_back(point_to);
        }
        point_from->neighbours.push_back(new Edge(point_from, point_to, capacity));
        point_to->neighbours.push_back(new Edge(point_from, point_to, capacity));
    }
    graph->findMaxFlow(point_start, point_end);
    return 0;
}

void Graph::findMaxFlow(Node* point_from, Node* point_to) {
    next_nodes.emplace(new Edge(nullptr, point_from, 0), true);
    came_from[point_from] = nullptr;
    Node* current = nullptr;
    while(!next_nodes.empty()) {
        if(next_nodes.top().second) {
            current = next_nodes.top().first->destination;
        } else {
            current = next_nodes.top().first->source;
        }
        came_from[current] = next_nodes.top().first;
        next_nodes.pop();
        if(current == point_to) {
            setMinimum(point_to, findMinimum(point_from, point_to));
            continue;
        }
        visitNode(current, point_to);
    }
    printAnswer(point_from);
}

void Graph::visitNode(Node* node, Node* point_to) {
    node->setVisited(true);

    sort(node->neighbours.begin(), node->neighbours.end(), [node, point_to](Edge* const& a, Edge* const& b) {
        Node* first = a->source == node ? a->destination : a->source;
        Node* second = b->source == node ? b->destination : b->source;
        if(first == point_to || second == point_to) {
            return false;
        }
        return first->getName() > second->getName();

    });
    for(Edge* elem : node->neighbours) {
        if(elem->source == node && !elem->destination->isVisited() && elem->curr_capacity != elem->max_capacity) {
            next_nodes.emplace(elem, true);
        } else if(elem->destination == node && !elem->source->isVisited() && elem->curr_capacity != 0) {
            next_nodes.emplace(elem, false);
        }

    }
}

int Graph::findMinimum(Node* point_from, Node* point_to) {
    int minimum = INT_MAX;
    Edge* current = came_from[point_to];
    Node* prev_node = point_to;
    while(prev_node != point_from) {
        if(current->destination == prev_node) {
            if((current->max_capacity - current->curr_capacity) < minimum) {
                minimum = current->max_capacity - current->curr_capacity;
            }
            prev_node = current->source;
        } else {
            if(current->curr_capacity < minimum) {
                minimum = current->curr_capacity;
            }
            prev_node = current->destination;
        }
        current = came_from[prev_node];
    }
    return minimum;
}

void Graph::setMinimum(Node* point_to, int minimum) {
    Edge* current = came_from[point_to];
    Node* prev_node = point_to;
    bool flag = true;
    while(current != nullptr) {
        if(!next_nodes.empty()) {
            if((next_nodes.top().second && next_nodes.top().first->source == prev_node) ||
               (!next_nodes.top().second && next_nodes.top().first->destination == prev_node)) {
                flag = false;
            }
            if(flag) {
                prev_node->setVisited(false);
            }
        }
        if(current->destination == prev_node) {
            current->curr_capacity += minimum;
            prev_node = current->source;
        } else if(current->source == prev_node) {
            current->curr_capacity -= minimum;
            prev_node = current->destination;
        }
        current = came_from[prev_node];
    }
}

void Graph::printAnswer(Node* point_from) {
    int max_flow = 0;
    for(Edge* elem: point_from->neighbours) {
        max_flow += elem->curr_capacity;
    }
    cout << max_flow << endl;
    list<Edge*> fact;
    for(Node* node : nodes) {
        for(Edge* edge : node->neighbours) {
            if(node == edge->source) {
                fact.push_back(edge);
            }
        }
    }
    fact.sort([](Edge* const& a, Edge* const& b) {
        if(a->source->getName() == b->source->getName()) {
            return a->destination->getName() < b->destination->getName();
        }
        return a->source->getName() < b->source->getName();
    });
    for(Edge* edge : fact) {
        cout << edge->source->getName() << " " << edge->destination->getName() << " " << edge->curr_capacity
             << endl;
    }
}

char Node::getName() const {
    return name;
}

bool Node::isVisited() const {
    return visited;
}

void Node::setVisited(bool flag) {
    visited = flag;
}

Node* Graph::getNode(char name) {
    for(Node* node : nodes) {
        if(node->getName() == name) {
            return node;
        }
    }
    return nullptr;
}
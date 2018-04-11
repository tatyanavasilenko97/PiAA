#include <iostream>
#include <list>
#include <queue>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

class Node {
private:
    char name;
    bool visited;

public:
    explicit Node(char name) : name(name), visited(false) {};

    list<pair<Node*, double>> neighbours;

    char getName() const;

    bool isVisited() const;

    void visit();
};

struct Comparator {
    bool operator()(pair<Node*, double> const& pair1, pair<Node*, double> const& pair2) {
        return pair1.second < pair2.second;
    }
};

class Graph {
public:
    list<Node*> nodes;

    map<char, char> came_from;

    priority_queue<pair<Node*, double>, vector<pair<Node*, double>>, Comparator> next_nodes;

    Node* getNode(char name);

    void visitNode(Node* node);

    void findPath(Node* point_from, Node* point_to);
};


int main() {
    char name_a, name_b;
    double weight;
    cin >> name_a >> name_b;
    auto* point_start = new Node(name_a);
    auto* point_end = new Node(name_b);
    auto* graph = new Graph;
    graph->nodes.push_back(point_start);
    graph->nodes.push_back(point_end);

    Node* point_from;
    Node* point_to;
    while(cin >> name_a && cin >> name_b && cin >> weight) {
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
        point_from->neighbours.emplace(point_from->neighbours.begin(), point_to, weight);
        point_to->neighbours.emplace(point_to->neighbours.begin(), point_from, weight);
    }
    graph->findPath(point_start, point_end);
    return 0;
}


char Node::getName() const {
    return name;
}

bool Node::isVisited() const {
    return visited;
}

void Node::visit() {
    visited = true;
}

Node* Graph::getNode(char name) {
    for(Node* node : nodes) {
        if(node->getName() == name) {
            return node;
        }
    }
    return nullptr;
}

void Graph::visitNode(Node* node) {
    static int counter = 1;
    node->visit();
    node->neighbours.sort([](pair<Node*, double> const& pair1, pair<Node*, double> const& pair2) {
        return pair1.second > pair2.second;
    });
    for(pair<Node*, double>& elem : node->neighbours) {
        if(!elem.first->isVisited()) {
            next_nodes.emplace(elem.first, counter++);
            came_from[elem.first->getName()] = node->getName();
        }
    }
}

void Graph::findPath(Node* point_from, Node* point_to) {
    next_nodes.emplace(point_from, 0);
    came_from[point_from->getName()] = 0;
    Node* current = nullptr;
    while(!next_nodes.empty()) {
        current = next_nodes.top().first;
        if(current == point_to) {
            break;
        }
        next_nodes.pop();
        visitNode(current);
    }
    char index = point_to->getName();
    string text;
    while(index != 0) {
        text += index;
        index = came_from[index];
    }
    reverse(text.begin(), text.end());
    cout << text;
}
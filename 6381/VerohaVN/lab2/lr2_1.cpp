#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Node {
	char start;
	char end;
	double weight;
public:
	Node(char start, char end, double weight) : start(start), end(end), weight(weight) {}
	char getStart() { return start; }
	char getEnd() { return end; }
	double getWeight() { return weight; }
};

bool getTop(vector<char> tops, char top) {
	for (int i = 0; i < tops.size(); i++)
		if (tops[i] == top) return true;
	return false;
}

int getIndex(vector<char> tops, char start_) {
	for (int i = 0; i < tops.size(); i++)
		if (tops[i] == start_) return i;
}

void printStack(stack <char> stack) {
	char a = stack.top();
	stack.pop();
	if (!stack.empty())
		printStack(stack);
	cout << a;
}

bool way = false;
void searchWay(vector<char> tops, vector<vector<Node>> nodes, int startIndex, char end, stack <char> stack) {
	if (!nodes[startIndex].empty()) {
		char endLocal = nodes[startIndex][0].getEnd();
		stack.push(endLocal);
		if (endLocal != end) {
			nodes[startIndex].erase(nodes[startIndex].begin());
			searchWay(tops, nodes, getIndex(tops, endLocal), end, stack);
			stack.pop();
			if (way == false)
				searchWay(tops, nodes, startIndex, end, stack);
		}
		else {
			printStack(stack);
			way = true;
		}
	}
}

void sortiForNodes(vector<vector<Node>> &nodes) {
	for (int i = 0; i < nodes.size(); i++) {
		if (1 < nodes[i].size())
			for (int j = 0; j < nodes[i].size() - 1; j++) {
				for (int k = 0; k < nodes[i].size(); k++) {
					if (nodes[i][j].getWeight() > nodes[i][j + 1].getWeight()) {
						Node a = nodes[i][j];
						nodes[i][j] = nodes[i][j + 1];
						nodes[i][j + 1] = a;
					}
				}
			}
	}
	nodes.swap(nodes);
}

int main() {
	char start;
	char end;
	cin >> start >> end;

	char start_;
	char end_;
	double weight;
	vector<char> tops;
	vector<vector<Node>> nodes;

	while (cin >> start_ && cin >> end_ && cin >> weight) {
		if (!getTop(tops, start_)) {
			tops.push_back(start_);
			vector<Node> a;
			nodes.push_back(a);
		}
		if (!getTop(tops, end_)) {
			tops.push_back(end_);
			vector<Node> a;
			nodes.push_back(a);
		}
		nodes[getIndex(tops, start_)].push_back(Node(start_, end_, weight));
	}
	stack <char> stack;
	stack.push(start);
	sortiForNodes(nodes);
	searchWay(tops, nodes, getIndex(tops, start), end, stack);
	return 0;
}
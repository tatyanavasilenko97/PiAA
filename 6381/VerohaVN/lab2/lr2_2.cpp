#include <iostream>
#include <vector>

using namespace std;

class Node {
	char start;
	char end;
	double weight;
public:
	Node(char start, char end, double weight) : start(start), end(end), weight(weight) {};
	char getStart() { return start; }
	char getEnd() { return end; }
	double getWeight() { return weight; }
};

struct TopForPriorityQueue {
	char top;
	double priority;
	TopForPriorityQueue(char top, double priority) :top(top), priority(priority) {}
};

class My_priority_queue {
	vector<TopForPriorityQueue> priority_queue;
public:
	void push(TopForPriorityQueue p) {
		if (!priority_queue.empty()) {
			for (unsigned int i = 0; i < priority_queue.size(); i++)
				if (priority_queue[i].priority > p.priority) {
					priority_queue.insert(priority_queue.begin() + i, p);
					return;
				}
		}
		priority_queue.push_back(p);
	}
	void pop(char top) {
		for (unsigned int i = 0; i < priority_queue.size(); i++){
			if (priority_queue[i].top == top) {
				priority_queue.erase(priority_queue.begin() + i);
				return;
			}
		}
		priority_queue.erase(priority_queue.begin());
	}
	TopForPriorityQueue top() { return priority_queue[0]; }
	bool empty() { return priority_queue.empty(); }
};

bool getTop(vector<char> tops, char top) {
	for (unsigned  int i = 0; i < tops.size(); i++)
		if (tops[i] == top) 
			return true;
	return false;
}

int getIndex(vector<char> tops, char start_) {
	for (unsigned  int i = 0; i < tops.size(); i++)
		if (tops[i] == start_) 
			return i;
	return 1;
}

double heuristic(char top_1, char top_2) {
	return abs(top_2 - top_1);
}

void printShortWay(vector<char> from, vector<char> to, char start, char end) {
	if (end != start)
		printShortWay(from, to, start, from[getIndex(to, end)]);
	cout << end;
}

void searchShortWay(vector<char> tops, vector<vector<Node>> nodes, char start, char end) {
	My_priority_queue priority_queue;
	vector<char> to;
	vector<char> from;
	vector<double> weigthWay;

	to.push_back(start);
	from.push_back(0);
	weigthWay.push_back(0);
	priority_queue.push(TopForPriorityQueue(start, 0));

	while (!priority_queue.empty()) {
		TopForPriorityQueue nowPrior = priority_queue.top();
		int nowPos = getIndex(tops, nowPrior.top);
		for (unsigned  int i = 0; i < nodes[nowPos].size(); i++) {
			Node nowNode = nodes[nowPos][i];
			double weigthNowWay = nowNode.getWeight() +  weigthWay.at(getIndex(to, nowPrior.top));
			if (getTop(to, nowNode.getEnd())) {
				if (weigthNowWay < weigthWay.at(getIndex(to, nowNode.getEnd()))) {
					weigthWay[getIndex(to, nowNode.getEnd())] = weigthNowWay;
					from[getIndex(to, nowNode.getEnd())] = nowPrior.top;
				}
			}
			else {
				to.push_back(nowNode.getEnd());
				from.push_back(nowPrior.top);
				weigthWay.push_back(weigthNowWay);
			}
			double priority = weigthNowWay + heuristic(nowNode.getEnd(), end);
			priority_queue.push(TopForPriorityQueue(nowNode.getEnd(), priority));
		}
		priority_queue.pop(nowPrior.top);
		if (nowPrior.top == end) {
			printShortWay(from, to, start, nowPrior.top);
			break;
		}
	}
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
		Node edge(start_, end_, weight);
		nodes[getIndex(tops, start_)].push_back(edge);
	}
	searchShortWay(tops, nodes, start, end);
	return 0;
}
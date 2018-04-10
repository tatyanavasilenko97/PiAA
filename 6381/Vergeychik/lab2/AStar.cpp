
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <queue>
using namespace std;

class Edge
{
public:
	char start;
	char end;
	double length;

	Edge(char start, char end, double length) : start(start), end(end), length(length) {};
	char getStart()
	{
		return start;
	}
	char getEnd()
	{
		return end;
	}
	double getLength()
	{
		return length;
	}
};

class Priority
{
public:
	char top;
	double priority;
	Priority(char top, double priority) :top(top), priority(priority) {}
};

class PriorityQueue
{
	vector<Priority> queue;
public:
	void push(Priority p)
	{
		if (!queue.empty())
		{
			for (int i = 0; i < queue.size(); i++)
			{
				if (queue[i].priority > p.priority)
				{
					queue.insert(queue.begin() + i, p);
					return;
				}
			}
		}
		queue.push_back(p);
	}
	Priority top()
	{
		return queue[0];
	}
	bool empty()
	{
		return queue.empty();
	}
	void pop(char top)
	{
			for (int i = 0; i < queue.size(); i++)
			{
				if (queue[i].top == top)
				{
					queue.erase(queue.begin()+i);
					return;
				}
			}
		queue.erase(queue.begin());
	}

};

bool isTopInList(vector<char> tops, char top)
{
	for (int i = 0; i < tops.size(); i++)
	{
		if (tops[i] == top)
		{
			return true;
		}
	}
	return false;
}

int getPositionOfTop(vector<char> tops, char top)
{
	for (int i = 0; i < tops.size(); i++)
	{
		if (tops[i] == top)
		{
			return i;
		}
	}
}

bool consistTop(vector<char> tops,char top)
{
	for (int i = 0; i < tops.size(); i++)
	{
		if (tops[i] == top)
		{
			return true;
		}
	}
	return false;
}

double costOfWayFromCurrentTop(vector<char> cameTo, vector<double> wayCosts, char top)//return way to the top
{
	return wayCosts.at(getPositionOfTop(cameTo, top));
}

double heuristic(char top1, char top2)
{
	return abs(top2 - top1);
}

void printWay(vector<char> cameFrom, vector<char> cameTo, char start, char end)
{
	if (end != start)
	{
		printWay(cameFrom, cameTo, start, cameFrom[getPositionOfTop(cameTo, end)]);
	}
	cout << end;
}
void findWay(vector<char> tops, vector<vector<Edge>> edges, char start, char end)
{
	PriorityQueue queue;
	stack <char> stack;
	vector<char> cameTo;//vector of tops in which we came
	vector<char> cameFrom;//vector of tops We came from
	vector<double> wayCost;//cost of way from cameFrom[i] to cameTo[i]
	cameTo.push_back(start);
	cameFrom.push_back(0);
	wayCost.push_back(0);
	queue.push(Priority(start, 0));
	while (!queue.empty())
	{
		Priority currentPriority = queue.top();//get the top with the highest priority
		int currentPosition = getPositionOfTop(tops, currentPriority.top);//find position of the top (for work with vector edges)
		if (currentPriority.top == end)
		{
			printWay(cameFrom, cameTo, start, currentPriority.top);
			cout << endl;
			break;
		}
		for (int i = 0; i < edges[currentPosition].size() ;i++)
		{
			Edge currentEdge = edges[currentPosition][i];
			double costOfCurrentWay = currentEdge.getLength() + costOfWayFromCurrentTop(cameTo, wayCost, currentPriority.top);//length of the edge + length of the way to current top
			if (consistTop(cameTo, currentEdge.getEnd()))//check presence the top in the vector of tops
			{
				if (costOfCurrentWay < wayCost.at(getPositionOfTop(cameTo, currentEdge.getEnd())))//
				{
					wayCost[getPositionOfTop(cameTo, currentEdge.getEnd())] = costOfCurrentWay;
					cameFrom[getPositionOfTop(cameTo, currentEdge.getEnd())] = currentPriority.top;
				}
			}
			else//if the top isn't in the vector, put the top there
			{
				cameTo.push_back(currentEdge.getEnd());
				cameFrom.push_back(currentPriority.top);
				wayCost.push_back(costOfCurrentWay);
			}
			double priority = costOfCurrentWay + heuristic(currentEdge.getEnd(), end);//find priority as heuristic + cost of current way
			queue.push(Priority(currentEdge.getEnd(), priority));//push new top in the queue with priority
		}
		queue.pop(currentPriority.top);//pop the analyzed top
	}
}
int main()
{
	char start;
	char end;

	ifstream fin("edges.txt");

	fin >> start;
	fin >> end;

	char startEdge;
	char endEdge;
	double length;

	vector<char> tops;
	vector<vector<Edge>> edges;

	while (fin >> startEdge && fin >> endEdge && fin >> length)
	{
		if (!isTopInList(tops, startEdge))//check presence of start top in list
		{
			tops.push_back(startEdge);//put new top in list
			vector<Edge> a;		//create new vector
			edges.push_back(a);//and put it in the list
		}
		if (!isTopInList(tops, endEdge))//check presence of end top in list
		{
			tops.push_back(endEdge);
			vector<Edge> a;
			edges.push_back(a);
		}
		Edge edge(startEdge, endEdge, length);//create new edge
		edges[getPositionOfTop(tops, startEdge)].push_back(edge);
	}
	fin.close();

	findWay(tops, edges, start, end);

	return 0;
}

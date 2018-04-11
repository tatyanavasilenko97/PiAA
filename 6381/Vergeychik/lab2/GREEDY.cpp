 // GREEDY.cpp: определяет точку входа для консольного приложения.
//


#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
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
void printStack(stack <char> stack)
{
	char k = stack.top();
	stack.pop();
	if (!stack.empty())
		printStack(stack);
	cout << k;
}
bool way = false;

void findWay(vector<char> tops, vector<vector<Edge>> edges, int position, char end, stack <char> stack)
{
	if (!edges[position].empty())
	{
		char endOfEdge = edges[position][0].getEnd();
		stack.push(endOfEdge);
		if (endOfEdge != end)
		{
			edges[position].erase(edges[position].begin());
			findWay(tops, edges, getPositionOfTop(tops, endOfEdge), end, stack);
			stack.pop();
			if (way == false)
			{
				findWay(tops, edges, position, end, stack);
			}
		}
		else
		{
			printStack(stack);
			way = true;
		}
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
	if (edges.size() > 1)
	for (int i = 0; i < edges.size(); i++)
	{
		if (edges[i].size() > 1)
		for (int j = 0; j < edges[i].size()-1; j++)
		{
			for (int k = 0; k < edges[i].size(); k++)
			{
					if (edges[i][j].getLength() > edges[i][j + 1].getLength())
					{
						Edge e = edges[i][j];
						edges[i][j] = edges[i][j + 1];
						edges[i][j + 1] = e;
					}
			}
		}
	}
	stack <char> stack;
	stack.push(start);
	findWay(tops, edges, getPositionOfTop(tops, start), end, stack);
	cout << endl;
    return 0;
}

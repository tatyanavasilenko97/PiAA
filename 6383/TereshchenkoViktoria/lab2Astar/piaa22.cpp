// piaa2
/*Разработайте программу,
которая решает задачу построения кратчайшего пути в ориентированном графе методом А*.*/
//priority в значении "старшинство"

#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

class Edge
{
    char startOfEdge;
    char endOfEdge;
    double length;

public:
    
    char getStartOfEdge()
	{
		return startOfEdge;
	}

	char getEndOfEdge()
	{
		return endOfEdge;
	}

    double getlength()
    {
        return length;
    }
    
    Edge(char startOfEdge, char endOfEdge, double length) : startOfEdge(startOfEdge), endOfEdge(endOfEdge), length(length) {}

};

class Priority
{
public:

	char top;
	double priority;
	Priority(char top, double priority) : top(top), priority(priority) {}
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
					queue.insert(queue.begin() + i, p); //insert from push_back?
					return; //?
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
		queue.erase(queue.begin());         //?
	}
};

bool isTopInList(vector<char> tops, char startOfEdge)
{
    for (int i = 0; i < tops.size(); i++)
    {
        if (tops[i] == startOfEdge) return true;
    }
    return false;
}

bool isTopInList_forEnd(vector<char> tops, char endOfEdge)
{
    for (int i = 0; i < tops.size(); i++)
    {
        if (tops[i] == endOfEdge) return true;
    }
    return false;
}

int getIndex(vector<char> tops, char top)
{
    for (int i = 0; i < tops.size(); i++)
    {
        if (tops[i] == top) return i;
    }
    
}

bool consistOfTop(vector<char> tops, char top)
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

double costOfWayFromCurTop(vector<char> cameTo, vector<double> wayCosts, char top)
{
	return wayCosts.at(getIndex(cameTo, top));
}

double difference(char topA, char topB)
{
	return abs(topB - topA);
}

void print(vector<char> cameFrom, vector<char> cameTo, char start, char end)
{
    if (end != start)
	{
		print(cameFrom, cameTo, start, cameFrom[getIndex(cameTo, end)]);
	}
	cout << end;
}

void findWay(vector<char> tops, vector<vector<Edge>> edges, char start, char end) 
{ 
    PriorityQueue queue;
	stack <char> stack;
	vector<char> cameTo;
	vector<char> cameFrom;
	vector<double> wayCost;
	cameTo.push_back(start);
	cameFrom.push_back(0);
	wayCost.push_back(0);
	queue.push(Priority(start, 0));
	while (!queue.empty())
	{
		Priority curPriority = queue.top();
		int curPosition = getIndex(tops, curPriority.top);
		if (curPriority.top == end)
		{
			print(cameFrom, cameTo, start, curPriority.top);
			cout << endl;
			break;
		}
		for (int i = 0; i < edges[curPosition].size() ;i++)
		{
			Edge curEdge = edges[curPosition][i];
			double costOfCurWay = curEdge.getlength() + costOfWayFromCurTop(cameTo, wayCost, curPriority.top);
			if (consistOfTop(cameTo, curEdge.getEndOfEdge()))
			{
				if (costOfCurWay < wayCost.at(getIndex(cameTo, curEdge.getEndOfEdge())))
				{
					wayCost[getIndex(cameTo, curEdge.getEndOfEdge())] = costOfCurWay;
					cameFrom[getIndex(cameTo, curEdge.getEndOfEdge())] = curPriority.top;
				}
			}
			else
			{
				cameTo.push_back(curEdge.getEndOfEdge());
				cameFrom.push_back(curPriority.top);
				wayCost.push_back(costOfCurWay);
			}
			double priority = costOfCurWay + difference(curEdge.getEndOfEdge(), end);
			queue.push(Priority(curEdge.getEndOfEdge(), priority));
		}
		queue.pop(curPriority.top);
	}
}

int main()
{
    ifstream fin("piaa2.txt");

    char start;
    char end;

    fin >> start;
    fin >> end;

    char startOfEdge;
    char endOfEdge;
    double length;
    
    vector<char> tops;
    vector<vector<Edge>> edges;

    while (fin >> startOfEdge && fin >> endOfEdge && fin >> length)
    {
        
        if(!isTopInList(tops, startOfEdge))
        {
            tops.push_back(startOfEdge);
            vector<Edge> a;
            edges.push_back(a);

        }

        if (!isTopInList_forEnd(tops, endOfEdge))
        {
            tops.push_back(endOfEdge);
            vector<Edge> a;
            edges.push_back(a);
        }

        edges[getIndex(tops, startOfEdge)].push_back(Edge(startOfEdge, endOfEdge, length));
    }

    findWay(tops, edges, start, end);
    fin.close();

    return 0;  
}
#include <iostream>
#include "Graph.hpp"

using namespace std;

int main()
{
     DM::Graph g;
	char s = 0, e = 0;
	cin >> s >> e;
	// cout << s << " " << e << endl;
	g.readOr();
	// g.print();
	std::cout << std::endl;
	std::list<char> Result;
	g.pathSearchGreedy(s, e, Result);
	for (auto i = Result.begin(), end = Result.end(); i != end; ++i)
	{
		cout << *i;
	}
     return 0;
}

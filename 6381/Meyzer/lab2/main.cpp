#include <iostream>
#include "Graph.hpp"

using namespace std;

int main()
{
     DM::Graph g;
	char s = 0, e = 0;
	cin >> s >> e;
	g.read();
	g.print();
     return 0;
}

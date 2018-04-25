#include <iostream>
// #define COUT_INPUT
#include "Graph.hpp"

using namespace std;

int main()
{
	DM::Graph g;
	char s = 0, e = 0;
	int n = 0;
	// cin.ignore(10, '\n');
	cin >> n;
	cin >> s >> e;
	#ifdef COUT_INPUT
		cout << s << " " << e << endl;
	#endif
	// g.readOr();
	char a = 0, b = 0;
	double w = 0;
	for(int i = 0; i < n; ++i)
	{
		std::cin >> a >> b >> w;
		// if (a<'a' || a>'z')
		// {
		// 	throw std::out_of_range(std::string(1,a));
		// }
		#ifdef COUT_INPUT
			std::cout << a << " " << b << " " << w << std::endl;
		#endif
		g.addEdge(a, b, w);
	}
	DM::Graph Result;
	g.searchMaxFlow(s, e, Result);
	return 0;
}

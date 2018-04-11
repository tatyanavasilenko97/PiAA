#include <iostream>

int main () 
{
	char first_edge, second_edge,
		 initial_vertex, terminal_vertex;
	int minimum, res = 0;
	char resulte[50] = {' '};
	float graf[26][26] = {0};
	float weight;
	
    std::cin >> initial_vertex >> terminal_vertex;
    resulte[0] = initial_vertex;
    
	while (std::cin >> first_edge >> second_edge >> weight)
		graf[(int)first_edge - 97][(int)second_edge - 97] = weight;
	
	while (resulte[res] != terminal_vertex)
	{
		minimum = 1000;
		res++;
		for (int i = 0; i < 26; i++) 
			if ((minimum > graf[(int)resulte[res-1] - 97][i]) &&
				(graf[(int)resulte[res-1] - 97][i] != 0)) 
					{minimum = graf[(int)resulte[res-1] - 97][i]; resulte[res] = (char)(i + 97);}
	}
	
	std::cout << resulte << std::endl;
	return 0;
}

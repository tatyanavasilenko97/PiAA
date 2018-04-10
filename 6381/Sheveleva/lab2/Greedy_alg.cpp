#include <iostream>

int main () 
{
	char first_edge, second_edge,
		 initial_vertex, terminal_vertex;
	char resulte[50] = {' '};
	int minimum, res = 0;
	float graf[26][26] = {0};
	float weight;
	
    std::cin >> initial_vertex >> terminal_vertex;
    resulte[0] = initial_vertex;
    
	while (std::cin >> first_edge >> second_edge >> weight)
	{
		graf[(int)first_edge - 97][(int)second_edge - 97] = weight;
		graf[(int)second_edge - 97][(int)first_edge - 97] = weight;
	}
	
	while (resulte[res] != terminal_vertex)
	{
		minimum = 1000;
		res++;
		for (int i = 0; i < 26; i++) 
			if ((minimum > graf[(int)resulte[res-1] - 97][i]) &&
				(graf[(int)resulte[res-1] - 97][i] != 0)) 
			{
				minimum = graf[(int)resulte[res-1] - 97][i]; 
				resulte[res] = (char)(i + 97);
			}
		if (minimum == 1000)
		{
			graf[(int)resulte[res - 2] - 97][(int)resulte[res - 1] - 97] = 0;
			resulte[res - 1] = ' ';
			res -= 2;
		}	
		else  
		{
			graf[(int)resulte[res-1] - 97][(int)resulte[res] - 97] = 0;
			graf[(int)resulte[res] - 97][(int)resulte[res-1] - 97] = 0;
		}
	}	
	std::cout << resulte << std::endl;
	return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

struct Open 
{
	char resulte[26]={' '};
	float weight=0;
	int prior = 0;
};

int main () 
{
	std::vector<Open> solution;//Вектор решений
	Open *curr_sol;
	char first_edge, second_edge,//Входные данные
		 initial_vertex, terminal_vertex, 
		 str[26] = {0}, *finish = nullptr;
	bool vertex_duplication;
	float weight_cur, fin_w;
	int sol = 0, current = 0;//Вспомогательные переменные
	float graf[26][26] = {0};
	
    std::cin >> initial_vertex >> terminal_vertex;
    current = initial_vertex - 97;
    
	while (std::cin >> first_edge >> second_edge >> weight_cur){
		graf[(int)first_edge - 97][(int)second_edge - 97] = weight_cur;
		graf[(int)second_edge - 97][(int)first_edge - 97] = weight_cur;
	}
	weight_cur = 0;	
	
	while(1)
	{
		for (int i = 0; i < 26; i++) 
			if (graf[current][i] != 0) 
			{
				vertex_duplication = false;// флаг дублирования вершины
				for (int j = 0; j < strlen(str); j++)
					if((char)(i + 97) == str[j]) {vertex_duplication = true; break;}//поиск дублирующей вершины
				if ((vertex_duplication == false) && ((char)(i + 97) != initial_vertex))
				{
					curr_sol = new Open;//запись элемента в вектор
					solution.push_back(*curr_sol);
					strcpy(solution.at(sol).resulte, &str[0]);
					solution.at(sol).resulte[strlen(str)]=(char)(i + 97);
					solution.at(sol).weight=graf[current][i] + weight_cur;
					solution.at(sol).prior=terminal_vertex - 97 - i;
					delete curr_sol;
					sol++;
				}
			}
		sol--;	
		std::sort(solution.begin(), solution.end(), [](const Open& a, const Open& b) {//сортировка по убыванию
				  return (a.weight+a.prior) > (b.weight+b.prior);});
		
		if(finish != nullptr)//если есть уже какой-то результат, то отсекаем решения, дающие вес больше имеющегося
		{
			while (sol >=0)
				{
					if(solution.at(sol).weight < fin_w) break;
					else {solution.erase(solution.begin() + sol); sol--;}
				}
			if (sol == -1) break; //выход из главного цикла
		}
		if(solution.at(sol).resulte[strlen(solution.at(sol).resulte) - 1] == terminal_vertex)
		{	
			if(finish == nullptr) //сохранение получившегося решения
			{
				finish = new char(strlen(solution.at(sol).resulte));
				strcpy(finish, &solution.at(sol).resulte[0]);
				fin_w=solution.at(sol).weight;
				solution.erase(solution.begin() + sol);
			}
			else {
				if(solution.at(sol).weight < fin_w)
					{
						delete[] finish; finish = new char(strlen(solution.at(sol).resulte));
						strcpy(finish, &solution.at(sol).resulte[0]);
						fin_w=solution.at(sol).weight;
					}
					solution.erase(solution.begin() + sol);
				}	
			sol--;
			while (sol >=0)//удаление решений, дающих больший вес
			{
				if(solution.at(sol).weight < fin_w) break;
				else {solution.erase(solution.begin() + sol); sol--;}
			}
			
			if (sol == -1) break;//выход из главного цикла
		}
		current = (int)(solution.at(sol).resulte[strlen(solution.at(sol).resulte) - 1]) - 97;
		strcpy(str, &solution.at(sol).resulte[0]);
		weight_cur = solution.at(sol).weight;
	}
	std::cout<<initial_vertex<<finish<<std::endl;	
	return 0;
}

#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <set>
#include <type_traits>
#include <fstream>
#include <queue>

#define MAX     100000

int heuristic_function(const int & a, const int & end, const std::map < char, int > newCode)
{
    char a_;
    for (auto it = newCode.begin(); it != newCode.end(); ++it)
			{

				if (it->second == a)
				{
					a_ = it->first;
				}
			}
    char end_;
    for (auto it = newCode.begin(); it != newCode.end(); ++it)
			{

				if (it->second == end)
				{
					end_ = it->first;
				}
			}
	return abs((int)(end_) - (int)(a_));
}

void a_star(const std::vector < std::vector < std::pair < int, double > > > al,const int & start,
	const int & end_, const int & sz, std::vector < int > & buf, const std::map < char, int > newCode)
{
	std::vector < int > prev(sz);
    std::vector < int > f(sz);
	std::vector < double > dist(sz, MAX);
	std::set < std::pair < double, int >/*, Compare*/> queue;
	dist[start] = 0;
	queue.insert(std::pair < double, int >(dist[start], start));
    queue.insert(std::pair < double, int >(dist[start], start));
    while (!queue.empty())
	{
		int minIndex = queue.begin()->second;
		queue.erase(queue.begin());
		for (size_t j = 0; j < al[minIndex].size(); j++)
		{
			if ( dist[minIndex] + al[minIndex][j].second < dist[al[minIndex][j].first])
			{
				queue.erase(std::pair < double, int >(dist[al[minIndex][j].first], al[minIndex][j].first));
				dist[al[minIndex][j].first] = dist[minIndex]  + al[minIndex][j].second;
				f[al[minIndex][j].first] = dist[al[minIndex][j].first] + heuristic_function(j,end_, newCode);
				prev[al[minIndex][j].first] = minIndex;
				queue.insert(std::pair < double, int >(f[al[minIndex][j].first], al[minIndex][j].first));
			}
		}
	}
	for (size_t i = end_; i != start; i = prev[i])
	{
		buf.push_back(i);
	}
	buf.push_back(start);
	std::reverse(buf.begin(), buf.end());
	int i = buf.size() - 1;
	while (buf[i] == 0)
	{
		buf.pop_back();
		i--;
	}
}

int main()
{
	char start;
    char end;
	std::ifstream cin ("in.txt");
	std::cin >> start >> end;
	std::map< char, int > charToInt;
    std::map < char, int > newCode;
	std::map < std::pair < char, char >, double > way_buf;
	std::map < std::pair < int, int >, double > way;
	std::vector< std::vector< std::pair < int, double > > > adjacencyList;
	char u; char v = 0; double len;
	while (!std::cin.eof())
	{
		std::cin >> u >> v >> len;
		charToInt.insert(std::pair < char, int >(u, charToInt.size()));
		charToInt.insert(std::pair < char, int >(v, charToInt.size()));
		way_buf.insert({ std::pair < int, int >(charToInt.find(u)->first, charToInt.find(v)->first) , len });
	}
	for (auto it = charToInt.begin(); it != charToInt.end(); ++it)
	{
		newCode.insert(std::pair <char, int >(it->first, newCode.size()));

	}
	for (auto it = way_buf.begin(); it != way_buf.end(); ++it)
	{
		way.insert({ std::pair <int, int>(newCode.find((it->first).first)->second,
			newCode.find((it->first).second)->second), it->second });
	}
	adjacencyList.resize(newCode.size());
	for (size_t i = 0; i < newCode.size(); i++)
		adjacencyList[i].resize(newCode.size());
	int k = 0;
	for (size_t i = 0; i < newCode.size(); i++)
		for (size_t j = 0; j < newCode.size(); j++)
			adjacencyList[i][j] = std::make_pair(j, ((way.find({ i, j }) != way.end()) ? way.find({ i, j })->second : MAX));
	std::vector <int> intRes(newCode.size());
    a_star(adjacencyList, newCode.find(start)->second,
		newCode.find(end)->second, newCode.size(), intRes, newCode);
		std::string answer;
		for (size_t i = 0; i < intRes.size(); i++)
			for (auto it = newCode.begin(); it != newCode.end(); ++it)
			{

				if (it->second == intRes[i])
				{
					answer += it->first;
				}
			}
		std::cout << answer << std::endl;
	return 0;
}
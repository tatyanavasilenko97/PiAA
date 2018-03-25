#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#define MAX     100000

void greedy(std::vector < std::vector < std::pair < int, double > > > al, int start,
        int end, int sz, std::vector < int > & buf)
{
    std::vector < int > prev(sz, 0);
    std::vector < double > dist(sz, MAX);
    std::set < std::pair < double, int > > queue;
    dist[start] = 0;
    queue.insert(std::pair < double, int > (dist[start], start));
    while (!queue.empty())
    {
       int minIndex = queue.begin()->second;
       queue.erase(queue.begin());
       for (size_t j = 0; j < al[minIndex].size(); j++)
            if (al[minIndex][j].second < dist[al[minIndex][j].first])
            {
                queue.erase(std::pair < double, int > (dist[al[minIndex][j].first], al[minIndex][j].first));
                dist[al[minIndex][j].first] = al[minIndex][j].second;
                prev[al[minIndex][j].first] = minIndex;
                queue.insert(std::pair < double, int > (dist[al[minIndex][j].first], al[minIndex][j].first));
            }   
    }
    for (int i = end; i != start; i = prev[i])
        buf.push_back(i);
    buf.push_back(start);
    std::reverse(buf.begin(), buf.end());
    int i = buf.size() - 1;
    while(buf[i] == 0)
    {
        buf.pop_back();
        i--;
    }
    return;
}

int main()
{
    char start;
    char end;
    std::cin >> start >> end;
    std::map< char, int > charToInt;
    std::map < std::pair < int, int >, double > way;
    std::vector< std::vector< std::pair < int, double > > > adjacencyList;
    char u; char v; double len;
    while (v != end)
    {
        std::cin >> u >> v >> len;
        charToInt.insert(std::pair < char, int > (u, charToInt.size()));
        charToInt.insert(std::pair < char, int > (v, charToInt.size()));
        way.insert( {std::pair < int, int > ( charToInt.find(u)->second, charToInt.find(v)->second ) , len });
    }
    adjacencyList.resize(charToInt.size());
    for (size_t i = 0; i < charToInt.size(); i++)
        adjacencyList[i].resize(charToInt.size());
    int k = 0;
    for (size_t i = 0; i < charToInt.size(); i++)
        for (size_t j = 0; j < charToInt.size(); j++)
                    adjacencyList[i][j] = std::make_pair(j, ((way.find({i, j}) != way.end()) ? way.find({i, j})->second : MAX));
    std::cout << "Coding by tops:\n";
    for (auto i = charToInt.begin(); i != charToInt.end(); ++i)
    {
        std::cout << i->first << " -> " << i->second << std::endl;
    }
    std::cout << "New table:\n";
    for (auto i = way.begin(); i != way.end(); ++i)
    {
        std::cout << i->first.first << "->" << i->first.second << " : " <<  i->second << std::endl;
    }
    std::cout << std::endl << "The adjacency list:\n";
    for (size_t i = 0; i < charToInt.size(); i++)
    {
        std::cout << i << ": ";
        for (size_t j = 0; j < charToInt.size(); j++)
            std::cout << adjacencyList[i][j].first << "--"
                    << ((adjacencyList[i][j].second == MAX) ? 99 :  adjacencyList[i][j].second ) << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::vector <int> intRes(charToInt.size());
    greedy(adjacencyList, charToInt.find(start)->second,
            charToInt.find(end)->second, charToInt.size(), intRes);
    std::string answer;
    for (size_t i = 0; i < intRes.size(); i++)
    	for (auto it = charToInt.begin(); it != charToInt.end(); ++it)         
    		if (it->second == intRes[i]) 
        		answer += it->first;
    std::cout << std::endl;
    std::cout << "Greedy way: "<< answer << std::endl;
    return 0;
}



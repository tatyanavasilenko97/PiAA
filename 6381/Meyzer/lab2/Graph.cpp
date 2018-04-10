#include "Graph.hpp"
#include <limits>

char DM::Vertex::getName() const
{
	return name;
}

void DM::Vertex::addEdge(char a, double weight)
{
	assocVertices.push_back(DM::Dyad(a, weight));
}

std::list<DM::Dyad>::iterator DM::Vertex::getAssocBegin()
{
	return assocVertices.begin();
}
std::list<DM::Dyad>::iterator DM::Vertex::getAssocEnd()
{
	return assocVertices.end();
}

void DM::Vertex::sortEdgesByName()
{
	assocVertices.sort([](const Dyad &a, const Dyad &b) { return (a.name < b.name); });
}

void DM::Vertex::sortEdgesByWeight()
{
	assocVertices.sort([](const Dyad &a, const Dyad &b) { return (a.weight < b.weight); });
}

bool DM::Vertex::hasEdges()
{
	return !(assocVertices.empty());
}

void DM::Vertex::printEdges()
{
	// std::cout << "Vertex printEdges called" << std::endl;
	for(auto i = assocVertices.begin(), end = assocVertices.end(); i != end; ++i)
	{
		std::cout << "   " << (*i).name << " " << (*i).weight << std::endl;
	}
}

void DM::Graph::read()
{
	char a = 0, b = 0;
	double w = 0;
	while (std::cin >> a)
	{
		std::cin >> b >> w;
		// std::cout << a << " " << b << " " << w << std::endl;
		addEdge(a, b, w);
		addEdge(b, a, w);
	}
}

void DM::Graph::readOr()
{
	char a = 0, b = 0;
	double w = 0;
	while (std::cin >> a)
	{
		std::cin >> b >> w;
		std::cout << a << " " << b << " " << w << std::endl;
		addEdge(a, b, w);
	}
}

void DM::Graph::addEdge(char a, char b, double weight)
{
	vertices.at(a-'a').addEdge(b, weight);
}

DM::Vertex& DM::Graph::getVertex(char a)
{
	return vertices.at(a-'a');
}

void DM::Graph::sortEdgesByName()
{
	for (auto i = vertices.begin(); i < vertices.end(); ++i)
	{
		i->sortEdgesByName();
	}
}

void DM::Graph::sortEdgesByWeight()
{
	for (auto i = vertices.begin(); i < vertices.end(); ++i)
	{
		i->sortEdgesByWeight();
	}
}

void DM::Graph::print()
{
	// std::cout << "Called print" << std::endl;
	for (int i = 0; i < vertN; ++i)
	{
		if (vertices.at(i).hasEdges())
		{
			// std::cout << "Printing edges of " << 'a'+i << " vertex" << std::endl;
			std::cout << char('a'+i) << ": " << std::endl;
			vertices.at(i).printEdges();
		}
	}
}

void DM::Graph::pathSearchGreedy(char s, char e, std::list<char>& Result)
{
	Result.clear();
	std::array<char, 26> path; // path[i] хранит вершину, из которой мы пришли в вершину i+'a'
	std::array<double, 26> dist; // dist[i] хранит длину пути от начальной вершины до вершины i+'a'
	std::array<bool, 26> vis; // vis[i] - были ли мы в вершине i+'a'
	dist.fill(std::numeric_limits<double>::max()); // Заполняем dist максимальными значениями
	vis.fill(false);
	sortEdgesByName(); // Сортируем ребра по имени
	sortEdgesByWeight(); // По весу
	dist.at(s-'a') = 0;
	char curr = s; // Текущая вершина - начальная
	// std::cout << curr << e << std::endl;
	while (curr != e) // Пока не дошли до конечной
	{
		// std::cout << curr << std::endl;
		vis.at(curr-'a') = true;
		Dyad next{0,0}; // Хранит имя следующей вершины и расстояние до неё от текущей
		for (auto i = getVertex(curr).getAssocBegin(),
			end = getVertex(curr).getAssocEnd(); i != end; ++i)
		{
			next = *i;
			if (!vis.at((*i).name-'a')) break;
		}
		// Если все вершины, смежные с данной, уже были посещены, или их нет:
		if (next.name==0 || vis.at(next.name-'a'))
		{
			curr = path.at(curr - 'a'); // Возвращаемся в предыдущую
			continue;
		}
		path.at(next.name-'a') = curr; // Задаём путь к следующей вершине
		dist.at(next.name-'a') = dist.at(curr-'a') + next.weight; // Задаём расстояние до следующей вершины от начальной
		curr = next.name; // В следующей итерации обрабатываем следующую вершину
		// std::cout << curr << dist.at(curr-'a') << std::endl; //
	}
	// std::cout << curr << std::endl; //
	// Добавляем путь до конечной вершины в Result
	curr = e;
	while (curr != s)
	{
		Result.push_front(curr);
		curr = path.at(curr-'a');
	}
	Result.push_front(curr);
}

void DM::Graph::pathSearchAStar(char s, char e, std::list<char>& Result)
{
	Result.clear(); // Очищаем список, в котором будет храниться результат
	struct n_pr{ // Структура, хранящая имя вершины и приоритет и реализующая operator<
	    char name;
	    double priority;
	    bool operator<(const n_pr& b) const
	    {
		    return priority > b.priority;
	    }
	};
	std::priority_queue<n_pr> q; // Очередь с приоритетом обрабатываемых вершин
	std::array<char, 26> path; // path[i] хранит вершину, из которой мы пришли в вершину i+'a'
	std::array<double, 26> dist; // dist[i] хранит длину пути от начальной вершины до вершины i+'a'
	dist.fill(std::numeric_limits<double>::max()); // Заполняем dist максимальным значениями
	// sortEdgesByName();
	// sortEdgesByWeight();
	q.push({s, 0}); // Добавляем в очередь начальную вершину
	dist.at(s-'a') = 0; // Расстояние до начальной вершины равно нулю

	while (!q.empty()) // Пока очередь не пуста
	{
	 char curr = q.top().name; // Берем элемент из вершины очереди
	 q.pop(); // Удаляем элемент из вершины очереди
	 // std::cout << curr << dist.at(curr-'a') << std::endl; //
	 for (auto i = getVertex(curr).getAssocBegin(),
		 end = getVertex(curr).getAssocEnd(); i != end; ++i) // Для всех вершин, смежных с текущей
	 {
		 if (dist.at((*i).name-'a') > (dist.at(curr-'a') + (*i).weight)) // Если мы можем уменьшить расстояние до смежной вершины
		 {
			 path.at((*i).name-'a') = curr; // Меняем путь к этой вершине
			 dist.at((*i).name-'a') = dist.at(curr-'a') + (*i).weight; // Меняем расстояние до неё
			 q.push({(*i).name, dist.at((*i).name-'a') + abs((*i).name-e)}); // Добавляем её в очередь с приоритетом расстояние+ASCII-разница
			 // std::cout << "Added ";
		 }
		 // std::cout << (*i).name << " vertex done " << dist.at((*i).name-'a') << std::endl; //
	 }
	}
	// std::cout << std::endl; //
	// Добавляем путь до конечной вершины в Result
	char curr = e;
	while (curr != s)
	{
	 Result.push_front(curr);
	 curr = path.at(curr-'a');
	}
	Result.push_front(curr);
}

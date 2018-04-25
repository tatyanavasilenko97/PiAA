#include "Graph.hpp"
// #define COUT_INPUT
// #define DEBUG
#include <limits>

char DM::Vertex::getName() const
{
	return name;
}

DM::Dyad& DM::Vertex::to(char a)
{
	for(auto& i : assocVertices)
	{
		if (i.name == a) return i;
	}
	std::cout << "Couldn't find an incident vertex " << a
		<< " to vertex " << getName() << std::endl;
	std::terminate();
}

std::list<DM::Dyad>& DM::Vertex::getEdges()
{
	return assocVertices;
}

DM::Dyad& DM::Vertex::frontTo()
{
	if (assocVertices.empty())
	{
		std::cout << "Couldn't get front in " << getName() << " incidents" << std::endl;
		std::terminate();
	}
	return assocVertices.front();
}

void DM::Vertex::addEdge(char a, int weight, int flow)
{
	assocVertices.push_back(DM::Dyad(a, weight, flow));
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

void DM::Vertex::sortEdgesByWeight(char c)
{
	if (c == '<')
		assocVertices.sort([](const Dyad &a, const Dyad &b) { return (a.weight < b.weight); });
	else if (c == '>')
		assocVertices.sort([](const Dyad &a, const Dyad &b) { return (a.weight > b.weight); });
}

bool DM::Vertex::hasEdges() const
{
	return !(assocVertices.empty());
}

void DM::Vertex::printEdges() const
{
	// std::cout << "Vertex printEdges called" << std::endl;
	for(auto i = assocVertices.begin(), end = assocVertices.end(); i != end; ++i)
	{
		std::cout << "   " << (*i).name << " " << (*i).weight
			<< " " << (*i).flow << std::endl;
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
		#ifdef COUT_INPUT
			std::cout << a << " " << b << " " << w << std::endl;
		#endif
		addEdge(a, b, w);
	}
}

void DM::Graph::addEdge(char a, char b, int weight, int flow)
{
	vertices.at(a-'0').addEdge(b, weight, flow);
}

DM::Vertex& DM::Graph::getVertex(char a)
{
	return vertices.at(a-'0');
}

void DM::Graph::sortEdgesByName()
{
	for (auto i = vertices.begin(); i < vertices.end(); ++i)
	{
		i->sortEdgesByName();
	}
}

void DM::Graph::sortEdgesByWeight(char c)
{
	for (auto i = vertices.begin(); i < vertices.end(); ++i)
	{
		i->sortEdgesByWeight(c);
	}
}

void DM::Vertex::sortEdgesByFlow(char c)
{
	if (c == '<')
		assocVertices.sort([](const Dyad &a, const Dyad &b) { return (a.flow < b.flow); });
	else if (c == '>')
		assocVertices.sort([](const Dyad &a, const Dyad &b) { return (a.flow > b.flow); });
}

void DM::Graph::sortEdgesByFlow(char c)
{
	for (auto &i : vertices)
		i.sortEdgesByFlow(c);
}

bool DM::Graph::hasEdge(char a, char b) const
{
	for(auto& c : this->at(a).assocVertices)
		if (c.name == b) return true;
	return false;
}

void DM::Graph::print()
{
	for (int i = 0; i < vertN; ++i)
	{
		if (vertices.at(i).hasEdges())
		{
			std::cout << char('a'+i) << ": " << std::endl;
			vertices.at(i).printEdges();
		}
	}
}

std::array<DM::Vertex, 100>& DM::Graph::getVertices()
{
	return vertices;
}

void DM::Graph::clear()
{
	for (auto& x: vertices)
	{
		if (x.hasEdges())
		{
			x.assocVertices.clear();
		}
	}
}

DM::Graph& DM::Graph::operator=(const DM::Graph& rh)
{
	// std::cout << "Called operator=" << std::endl;
	clear();
	for(const Vertex& x : rh.vertices)
	{
		if (x.hasEdges())
		{
			for(auto& y : x.assocVertices)
			{
				addEdge(x.getName(), y.name, y.weight);
				// vertices.at(x.getName()-'0').addEdge(y.name, y.weight);
			}
		}
	}
}

void DM::Graph::fillWeights(double w)
{
	for(auto& i: vertices)
	{
		if(i.hasEdges())
		{
			for(auto& j : i.assocVertices)
				j.weight = w;
		}
	}
}

int& DM::Graph::getWeight(char a, char b)
{
	return this->at(a).to(b).weight;
}
int& DM::Graph::getFlow(char a, char b)
{
	return this->at(a).to(b).flow;
}

void DM::Graph::reverse()
{
	Graph tmp;
	for(auto& i : vertices)
		if(i.hasEdges())
			for(auto& j : i.assocVertices)
				tmp.addEdge(j.name, i.getName(), j.weight, j.flow);
	*this = tmp;
}

void DM::Graph::pathSearchGreedy(char s, char e, std::list<char>& Result, char c)
{
	Result.clear();
	std::array<char, 100> path; // path[i] хранит вершину, из которой мы пришли в вершину i+'0'
	std::array<double, 100> dist; // dist[i] хранит длину пути от начальной вершины до вершины i+'0'
	std::array<bool, 100> vis; // vis[i] - были ли мы в вершине i+'0'
	path.fill(-1);
	dist.fill(std::numeric_limits<double>::max()); // Заполняем dist максимальными значениями
	vis.fill(false);
	sortEdgesByName(); // Сортируем ребра по имени
	sortEdgesByWeight(c); // По весу
	dist.at(s-'0') = 0;
	char curr = s; // Текущая вершина - начальная
	// std::cout << curr << e << std::endl;
	while (curr != e) // Пока не дошли до конечной
	{
		// std::cout << curr << std::endl;
		vis.at(curr-'0') = true;
		Dyad next{0,0}; // Хранит имя следующей вершины и расстояние до неё от текущей
		for (auto i = getVertex(curr).getAssocBegin(),
			end = getVertex(curr).getAssocEnd(); i != end; ++i)
		{
			next = *i;
			if (!vis.at((*i).name-'0') && next.weight != 0) break;
		}
		// Если все вершины, смежные с данной, уже были посещены, или их нет:
		if (next.name==0 || vis.at(next.name-'0') || next.weight==0)
		{
			if (curr == s) break;
			curr = path.at(curr - '0'); // Возвращаемся в предыдущую
			continue;
		}
		path.at(next.name-'0') = curr; // Задаём путь к следующей вершине
		dist.at(next.name-'0') = dist.at(curr-'0') + next.weight; // Задаём расстояние до следующей вершины от начальной
		curr = next.name; // В следующей итерации обрабатываем следующую вершину
		// std::cout << curr << dist.at(curr-'0') << std::endl; //
	}
	// std::cout << curr << std::endl; //
	if (path.at(e-'0') == -1)
	{
		#ifdef DEBUG
			std::cout << "No path" << std::endl;
		#endif
		return; // Если путь не найден
	}
	// Добавляем путь до конечной вершины в Result
	curr = e;
	while (curr != s)
	{
		Result.push_front(curr);
		curr = path.at(curr-'0');
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
	std::array<char, 100> path; // path[i] хранит вершину, из которой мы пришли в вершину i+'0'
	std::array<double, 100> dist; // dist[i] хранит длину пути от начальной вершины до вершины i+'0'
	dist.fill(std::numeric_limits<double>::max()); // Заполняем dist максимальным значениями
	// sortEdgesByName();
	// sortEdgesByWeight();
	q.push({s, 0}); // Добавляем в очередь начальную вершину
	dist.at(s-'0') = 0; // Расстояние до начальной вершины равно нулю

	while (!q.empty()) // Пока очередь не пуста
	{
	 char curr = q.top().name; // Берем элемент из вершины очереди
	 q.pop(); // Удаляем элемент из вершины очереди
	 // std::cout << curr << dist.at(curr-'0') << std::endl; //
	 for (auto i = getVertex(curr).getAssocBegin(),
		 end = getVertex(curr).getAssocEnd(); i != end; ++i) // Для всех вершин, смежных с текущей
	 {
		 if (dist.at((*i).name-'0') > (dist.at(curr-'0') + (*i).weight)) // Если мы можем уменьшить расстояние до смежной вершины
		 {
			 path.at((*i).name-'0') = curr; // Меняем путь к этой вершине
			 dist.at((*i).name-'0') = dist.at(curr-'0') + (*i).weight; // Меняем расстояние до неё
			 q.push({(*i).name, dist.at((*i).name-'0') + abs((*i).name-e)}); // Добавляем её в очередь с приоритетом расстояние+ASCII-разница
			 // std::cout << "Added ";
		 }
		 // std::cout << (*i).name << " vertex done " << dist.at((*i).name-'0') << std::endl; //
	 }
	}
	// std::cout << std::endl; //
	// Добавляем путь до конечной вершины в Result
	char curr = e;
	while (curr != s)
	{
	 Result.push_front(curr);
	 curr = path.at(curr-'0');
	}
	Result.push_front(curr);
}

const DM::Vertex& DM::Graph::at(char c) const
{
	return vertices.at(c-'0');
}

DM::Vertex& DM::Graph::at(char c)
{
	return vertices.at(c-'0');
}

// Объединяет два графа
DM::Graph DM::Graph::operator+(const Graph& rhs)
{
	const Graph& lhs = *this;
	Graph tmp;
	for(auto& i : lhs.vertices)
		if(i.hasEdges())
			for(auto& j : i.assocVertices)
				tmp.addEdge(i.name, j.name, j.weight);
	for(auto& i : rhs.vertices)
		if(i.hasEdges())
			for(auto& j : i.assocVertices)
				tmp.addEdge(i.name, j.name, j.weight);
	return tmp;
}

struct pathType
{char a; char b; int flow;};

void flowSearchGreedy(char s, char e, DM::Graph& g, std::list<pathType>& Result, char c = '<')
{
	Result.clear();
	std::array<char, 100> path; // path[i] хранит вершину, из которой мы пришли в вершину i+'0'
	std::array<bool, 100> vis; // vis[i] - были ли мы в вершине i+'0'
	path.fill(-1);
	vis.fill(false);
	// sortEdgesByName(); // Сортируем ребра по имени
	g.sortEdgesByWeight(c); // По весу
	g.sortEdgesByFlow(c); // По потоку
	char curr = s; // Текущая вершина - начальная
	while (curr != e) // Пока не дошли до конечной
	{
		int flowValue = 0;
		bool found = false;
		vis.at(curr-'0') = true;
		char next = 0; // Хранит имя следующей вершины
		// Находим вершину, к которой можем пустить поток
		for (auto& i : g.at(curr).getEdges())
		{
			next = i.name;
			// Если вершина не посещена и есть поток/ребро
			if (!vis.at(next-'0'))
			{
				if (g.getFlow(curr, next)>0)
				{
					flowValue += g.getFlow(curr, next);
					found = true;
					#ifdef DEBUG
						std::cout << "Flow " << curr << " " << next << std::endl;
					#endif
					// break;
				}

				if (g.getWeight(curr, next)>0)
				{
					flowValue += g.getWeight(curr,next);
					found = true;
					#ifdef DEBUG
						std::cout << "Edge " << curr << " " << next << std::endl;
					#endif
					// break;
				}

			}
			if (found)
				break;
		}

		// Если все вершины в остаточной сети и в сети потоков,
		// смежные с данной, уже были посещены, или их нет:
		if (!found)
		{
			if (curr == s) break;
			#ifdef DEBUG
				std::cout << "Returning from " << Result.back().b << std::endl;
			#endif
			curr = path.at(curr - '0'); // Возвращаемся в предыдущую
			Result.pop_back();
			continue;
		}
		Result.push_back({curr, next, flowValue});
		path.at(next-'0') = curr; // Задаём путь к следующей вершине
		curr = next; // В следующей итерации обрабатываем следующую вершину
	}
	if (path.at(e-'0') == -1)
	{
		#ifdef DEBUG
			std::cout << "No path" << std::endl;
		#endif
		return; // Если путь не найден
	}
}


// s - исток, e - сток
// g - остаточная сеть, f - сеть потоков
// Выход: path, min - путь и пропускная способность потока
void searchMaxFlow_findAdditionalPath(char s, char e, DM::Graph& g,
		std::list<pathType>& path, int& min)
{
	min = std::numeric_limits<int>::max();
	flowSearchGreedy(s, e, g, path, '>');
	for(auto c : path)
	{
		if (c.flow < min)
		{
			min = c.flow;
		}
	}
}

void searchMaxFlow_addWeight(DM::Graph& g, const std::list<pathType>& path, int min)
{
	#ifdef DEBUG
		std::cout << "   New weights: " << std::endl;
	#endif
	for(auto& x : path)
	{
		// Идём через поток:
			// Вычитаем из потока ab максимум, прибавляем его к ребру ba
		int tmin = min;
		{
			tmin = std::min(min, g.getFlow(x.a, x.b));
			g.getFlow(x.a, x.b) -= tmin;
			if (g.hasEdge(x.b, x.a))
				g.getWeight(x.b, x.a) += tmin;
			else
				g.addEdge(x.b, x.a, tmin, 0);
			tmin = min - tmin; // Поток через ребро ab - то, что осталось
		}
		// Идём через ребро:
			// Вычитаем из ребра ab максимум, прибавляем его к потоку ba
		if (tmin)
		{
			g.getWeight(x.a, x.b) -= tmin;
			g.getFlow(x.b, x.a) += tmin;
		}

		// Отладочный вывод
		#ifdef DEBUG
			std::cout << "   " << x.a << " " << x.b << " "
			<< g.getWeight(x.a, x.b) << " " << g.getFlow(x.a, x.b) << std::endl;
				// << " " << g.at(x.a).to(x.b).flow << std::endl;
			if (g.hasEdge(x.b, x.a))
				std::cout << "   " << x.b << " " << x.a << " "
					<< g.getWeight(x.b, x.a) << " " << g.getFlow(x.b, x.a) << std::endl;
		#endif
	}
}

void DM::Graph::searchMaxFlow(char s, char e, Graph& Result)
{
	Result = *this; // Сеть потоков и остаточная сеть
	#ifdef DEBUG
		Result.print();
	#endif
	// DM::Graph both = R + Result;
	std::list<pathType> path; // Для хранения найденного потока
	int i = 0;
	while(true)
	{
		int min = 0;
		#ifdef DEBUG
			std::cout << "Found additional path: " << std::endl;
		#endif
		// Ищем путь s->e в графе R(по нулям ходить нельзя), попутно выбирая
			// min - минимальный вес ребра на всем пути, и кладём его в path
		searchMaxFlow_findAdditionalPath(s, e, Result, path, min);
		#ifdef DEBUG
			for (auto &c : path)
				std::cout << c.a;
			std::cout << path.back().b << std::endl;
		#endif
		// Если не найден, то break
		if (path.empty()) break;
		// Вычитаем по всему пути min в R, прибавляем - в Result
		#ifdef DEBUG
			std::cout << "Flow is: " << min << std::endl;
			std::cout << "Changing network: " << std::endl;
		#endif
		searchMaxFlow_addWeight(Result, path, min);
		#ifdef DEBUG
			Result.print();
		#endif
		// if (i==3) break;
		i++;
	}
	// Printing answer
	// Result.print();
	// Result.reverse();
	this->sortEdgesByName();
	int tmp = 0;
	#ifdef DEBUG
		Result.print();
	#endif
	for (auto& i : Result.at(e).getEdges())
		tmp += i.flow;
	std::cout << tmp << std::endl;
	for (auto& i : this->getVertices())
	{
		for(auto& j : i.getEdges())
		{

			std::cout << i.getName() << " " << j.name << " "
				<< (Result.hasEdge(j.name, i.getName()) ? Result.getFlow(j.name, i.getName()) : 0) << std::endl;
		}
	}
}

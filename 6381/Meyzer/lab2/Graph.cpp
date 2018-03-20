#include "Graph.hpp"

char DM::Vertex::getName() const
{
	return name;
}

void DM::Vertex::addEdge(char a, double weight)
{
	assocVertices.push_back(DM::Triplet(a, weight));
}

std::list<DM::Triplet>::iterator DM::Vertex::getAssocBegin()
{
	return assocVertices.begin();
}
std::list<DM::Triplet>::iterator DM::Vertex::getAssocEnd()
{
	return assocVertices.end();
}

void DM::Vertex::sortEdgesByName()
{
	assocVertices.sort([](const Triplet &a, const Triplet &b) { return (a.name < b.name); });
}

void DM::Vertex::sortEdgesByWeight()
{
	assocVertices.sort([](const Triplet &a, const Triplet &b) { return (a.weight < b.weight); });
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
	std::array<bool, 26> isVisited;
	isVisited.fill(false);
	sortEdgesByWeight();
	char curr = s;
	isVisited.at(curr-'a') = true;
	Result.push_back(curr);
	while (curr != e)
	{
		// std::cout << curr << " ";
		auto v = getVertex(curr).getAssocBegin(),
			end = getVertex(curr).getAssocEnd();
		for(; v != end; ++v) // Для всех смежных вершин
		{
			if (!isVisited.at((*v).name-'a')) // Если вершина еще не посещена
			{
				isVisited.at((*v).name-'a') = true;
				// std::cout << "Added " << (*v).name << " to result" << std::endl;
				Result.push_back((*v).name); // Помещаем ее в конец Result
				curr = (*v).name;
				break;
			}
		}
		// Если все связанные вершины посещены
			// curr = последний элемент из Result
			// Удаляем последний элемент из Result
		if (v == end)
		{
				// curr = Result.back();
				// std::cout << "Removed " << curr << " from result" << std::endl;
			Result.pop_back();
			curr = Result.back();
		}
	}
}

void DM::Graph::pathSearch(char s, char e, std::list<char>& Result)
{

}

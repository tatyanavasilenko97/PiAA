#include <iostream>
#include <list>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstring>

bool test = false; //  переменная тестирования 
// Глобальные переменные  - зло!

struct vertex_id {
	char ID;
	explicit vertex_id(char id) : ID(id) {} ;
	explicit vertex_id() : ID(0) {} ;

	friend bool operator==(vertex_id lhs, vertex_id rhs){
		if (lhs.ID == rhs.ID) 
			return true;
		else
			return false;
	}

	friend bool operator!=(vertex_id lhs, vertex_id rhs){
		return !(lhs == rhs);
	}

	friend std::ostream& operator<<(std::ostream &out, vertex_id id){
		out << id.ID;
		return out;
	}	
};


// Полуребро: вершина на втором конце ребра и его вес
// Элемент в списке смежности (с какой вершиной смежно)
struct SemiEdge { 
	vertex_id Name;
	double length;

	SemiEdge(vertex_id name, double length) : Name(name), length(length) {} ;

	friend std::ostream& operator<<(std::ostream &out, SemiEdge semiEdge){
		out << semiEdge.Name << "(" << semiEdge.length << ")";
		return out;
	}
};

// Элемент списка смежности (какие вершины смежны)
struct VertexOfAdjacencyList { 
	vertex_id Name;
	std::list <SemiEdge> AdjacentVertices;

	VertexOfAdjacencyList(vertex_id name) : Name(name) {} ; 

	friend std::ostream& operator<<(std::ostream &out, VertexOfAdjacencyList vertexList){
		out << vertexList.Name;
		for (auto &ListElem : vertexList.AdjacentVertices)
			out << " - " << ListElem;
		out << " - End!";
		return out;
	}
};

// Не самая лучшая реализация
class PriorityQueue {
private:
	std::deque <std::pair<vertex_id, int>> container;
public:
	void add(vertex_id new_vertex, int length){
		for (auto &element : container)
			if (element.first == new_vertex)
				if (element.second > length){
					element.second = length;
					return;
				}
		container.push_back(std::make_pair(new_vertex, length));
	}

	vertex_id pop() {
		// Проверку на пустоту в данной релазиции можно не делать,
		// ибо цикл работает пока очередь не пуста, а из других мест мы к ней не обращаемся
		auto min = std::min_element(container.begin(), container.end(), cmp);
		vertex_id result = min->first;
		container.erase(min);
		return result;
	}

	bool empty() {
		return container.empty();
	}

	friend std::ostream& operator<<(std::ostream &out, PriorityQueue queue){
		for (const auto &elem: queue.container)
			out << elem.first << " " << elem.second << std::endl;
		return out;
	}

private:	
	static bool cmp(const std::pair<vertex_id, int> &lhs, const std::pair<vertex_id, int> &rhs){
		if (lhs.second < rhs.second)
			return true;
		else
			return false;
	}
};


// Список смежности. Реализация хранения графа.
// В векторе находятся структуры типа: (название вершины, список смежных ей вершин с расстояниями до них)
class AdjacencyList { 
	std::vector <VertexOfAdjacencyList> AdjList;
public:
	void addVertex(vertex_id name){
		for (auto &cur_vertex : AdjList)
			if (cur_vertex.Name == name)
				return;
		AdjList.emplace_back(name);
	}

	void addEdge(vertex_id start, vertex_id destination, double length){
		addVertex(start);
		addVertex(destination);
		for (auto &vectorElem : AdjList){
			if (vectorElem.Name == start){
				vectorElem.AdjacentVertices.emplace_back(SemiEdge(destination, length));
			}
		}
	}

	// Возвращает копию списка смежности у заданной вершины.
	std::list <SemiEdge> operator[](vertex_id name){
		for (auto vertex : AdjList)
			if (vertex.Name == name)
				return vertex.AdjacentVertices;
	}

	friend std::ostream& operator<<(std::ostream &out, AdjacencyList &list){
		out << "\n";
		for (auto &cur_vertex : list.AdjList){
			out << cur_vertex << std::endl;
			out << "|\n";
			// if (list.AdjList.back().Name != cur_vertex.Name) out << "|\n";
		}
		out << "End!\n" << std::endl;
		return out;
	}

/////////////////////////// Секция алгоритмы \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

public:
	std::deque <vertex_id> GreedyAlgorithm(vertex_id start, vertex_id destination){
		std::vector <VertexOfAdjacencyList> tmpAdjacencyList(AdjList);
		std::deque <vertex_id> Track;
		Track.push_back(start);

		while (Track.back() != destination) {
			std::pair<bool, vertex_id> NextVertex = findMinEdge(tmpAdjacencyList, Track.back());
			if (!NextVertex.first){ // Если вершина висячая
				Track.pop_back(); // Вернуться к предыдущей верщине
				if (Track.empty()) // такого пути в графе нет
					break;
			}
			else {
				Track.push_back(NextVertex.second);
			}
		}
		return Track;
	}

private:
	std::pair<bool,vertex_id> findMinEdge(std::vector <VertexOfAdjacencyList> &tmpAdjacencyList, vertex_id whence){
		for (auto &vertex : tmpAdjacencyList)
			if (vertex.Name == whence){
				auto result = std::min_element(vertex.AdjacentVertices.begin(), vertex.AdjacentVertices.end(), cmpEdges);
				if (result == vertex.AdjacentVertices.end())
					return std::make_pair(false, whence);
				else {
					vertex.AdjacentVertices.erase(result);
					return std::make_pair(true, result->Name);
				}
			}
	}

	static bool cmpEdges(const SemiEdge &lhs, const SemiEdge &rhs){
		if (lhs.length < rhs.length)
			return true;
		else
			return false;
	}

public:
	typedef std::deque <std::pair<vertex_id, vertex_id> > Vertex_Vertex_Pairs;
	typedef std::deque <std::pair<vertex_id, double> >    Vertex_Length_Pairs;
	std::deque <vertex_id> HeuristicAlgorithm(vertex_id start, vertex_id destination){
		PriorityQueue WaitingList;
		Vertex_Length_Pairs CurrentCosts;
		Vertex_Vertex_Pairs MinChains; // Цепочка из пар врешин - мин путь до каждой

		WaitingList.add(start,0);
		CurrentCosts.push_back(std::make_pair(start, 0));
		// MinChains.push_back(start);

		while (!WaitingList.empty()){
			vertex_id cur_vertex_name = WaitingList.pop();
			if (test) std::cout << "Cur vertex_name: " << cur_vertex_name << std::endl;

			if (cur_vertex_name == destination){
				break;	
			}

			for (auto next_vertex : (*this)[cur_vertex_name]) {
				double newCost = next_vertex.length + getCurrentLenght(CurrentCosts, cur_vertex_name);

				if (test) std::cout << "	Check vertex: " << next_vertex.Name << std::endl;
				if (test) std::cout << "	newCost = " << next_vertex.length << "(length to add) + " << getCurrentLenght(CurrentCosts, cur_vertex_name) << "(old)" <<std::endl;

				if (!checkVertexExist(CurrentCosts, next_vertex.Name) || newCost < getCurrentLenght(CurrentCosts, next_vertex.Name)) {
					setNewLength(CurrentCosts, next_vertex.Name, newCost);
					double priority = newCost + (double)HeuristicFunction(next_vertex.Name, destination);
					WaitingList.add(next_vertex.Name, priority);
					// MinChains.push_back(std::make_pair(cur_vertex_name, next_vertex.Name)); // fix
					changeChains(MinChains, cur_vertex_name, next_vertex.Name);

					if (test) std::cout << "	newPriority: " << priority << " = " << newCost << "(newCost) + " << (double)HeuristicFunction(next_vertex.Name, destination) << std::endl << std::endl;				
				}

			}
		}
		if (test){
			std::cout << "\n\nEnd of algorithm. Received pairs of verteces:\n";
			for (const auto &vertex : MinChains)
					std::cout << vertex.first << " " << vertex.second << std::endl;
		}

		std::deque <vertex_id> Track;
		// Сбойный кусок кода.
		/*
		if (MinChains.back().second != destination)
			return Track; // Проверка на валидность пути. Если последняя точка не точка назначения, возвращаем пустой дек.
		*/
		if (!checkForValidTrack(MinChains, destination))
			return Track;
		vertex_id tmp = destination;
		while (tmp != start){
			for (auto &element : MinChains){
				if (element.second == tmp){
					Track.push_front(tmp);
					tmp = element.first;
				}
			}
		}
		Track.push_front(tmp);		
		return Track;
	}

private:
	int HeuristicFunction(vertex_id lhs, vertex_id rhs){
		return abs(rhs.ID - lhs.ID);
	}
	// далее не будем проверять на отсутствие, хотя надо бы
	double getCurrentLenght(Vertex_Length_Pairs &CurrentCosts, vertex_id vertex_name){
		for (const auto &vertex : CurrentCosts)
			if (vertex.first == vertex_name)
				return vertex.second;
	}

	bool checkVertexExist(Vertex_Length_Pairs &CurrentCosts, vertex_id vertex_name){
		for (const auto &vertex : CurrentCosts)
			if (vertex.first == vertex_name)
				return true;
		return false;
	}

	void setNewLength(Vertex_Length_Pairs &CurrentCosts, vertex_id vertex_name, double newLenght){
		for (auto &vertex : CurrentCosts)
			if (vertex.first == vertex_name){
				vertex.second = newLenght;
				return;
			}
		CurrentCosts.push_back(std::make_pair(vertex_name, newLenght));
	}

	bool checkForValidTrack(const Vertex_Vertex_Pairs &MinChains, vertex_id destination){
		for (auto const &element : MinChains)
			if (element.second == destination)
				return true;
		return false;
	}

	void changeChains(Vertex_Vertex_Pairs &MinChains, vertex_id from, vertex_id destination){
		for (auto &element : MinChains)
			if (element.second == destination){
				element.first = from;
				return;
			}
		MinChains.push_back(std::make_pair(from, destination));
	}
};


int main(int argc, char** argv) {
	if (argc == 2 && !strcmp(argv[1], "-test\0"))
		test = true;

	AdjacencyList graph;

	char word1;
	char word2;
	double length;
	std::cin >> word1;
	vertex_id start(word1);
	std::cin >> word1;
	vertex_id destination(word1);

	while (std::cin >> word1 >> word2 >> length){
		graph.addEdge(vertex_id(word1), vertex_id(word2), length);
	}

	if (test){
		std::cout << "Adjacency List from input data:\n";
		std::cout << graph << std::endl;
		std::cout << "Start: " << start << std::endl;
		std::cout << "Destination: " << destination << "\n\n";
	}
	// std::deque <vertex_id> Track =  graph.GreedyAlgorithm(start, destination);
	// for (auto vertex : Track)
	// 	std::cout << vertex;

	// std::cout << graph << std::endl;
	// std::cout << "start: " << start << std::endl;
	// std::cout << "Destination: " << destination << std::endl;
	std::deque <vertex_id> Track =  graph.HeuristicAlgorithm(start, destination);
	if (test) std::cout << "\nTrack from " << start << " to " << destination << ": ";
	for (auto &vertex : Track)
		std::cout << vertex;
	std::cout << std::endl;
}

// мб алгоритмы в отдельные классы?
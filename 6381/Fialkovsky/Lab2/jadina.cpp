#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <deque>
#include <algorithm>


struct vertex_id {
	char ID;
	explicit vertex_id(char id) : ID(id) {} ;
	explicit vertex_id() : ID(0) {} ;

	// vertex_id(const vertex_id &rhs){
	// 	ID = rhs.ID;
	// }

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


struct SemiEdge { // Полуребро: вершина на втором конце ребра и его вес
	vertex_id Name;
	int length;

	SemiEdge(vertex_id name, int length) : Name(name), length(length) {} ;

	friend std::ostream& operator<<(std::ostream &out, SemiEdge semiEdge){
		out << semiEdge.Name << "(" << semiEdge.length << ")";
		return out;
	}
};

struct VertexOfAdjacencyList { // Элемент списка смежности
	vertex_id Name;
	std::list <SemiEdge> AdjacentVertices;

	VertexOfAdjacencyList(vertex_id name) : Name(name) {
	} ; 

	friend std::ostream& operator<<(std::ostream &out, VertexOfAdjacencyList vertexList){
		out << vertexList.Name;
		for (auto &ListElem : vertexList.AdjacentVertices)
			out << " - " << ListElem;
		out << " - End!";
		return out;
	}
};


class AdjacencyList { // Список смежности.
	std::vector <VertexOfAdjacencyList> AdjList;
public:
	void addVertex(vertex_id name){
		for (auto &cur_vertex : AdjList)
			if (cur_vertex.Name == name)
				return;
		AdjList.emplace_back(name);
	}

	void addEdge(vertex_id start, vertex_id destination, int length){
		addVertex(start);
		addVertex(destination);
		for (auto &vectorElem : AdjList){
			// std::cout << "Compare " << vectorElem.Name << " and " << start << std::endl;
			if (vectorElem.Name == start){
				vectorElem.AdjacentVertices.emplace_back(SemiEdge(destination, length)); // судя по всему, не туда вставляет ( в копию)
			}
		}
	}		

	friend std::ostream& operator<<(std::ostream &out, AdjacencyList &list){
		out << "\n";
		for (auto &cur_vertex : list.AdjList){
			out << cur_vertex << std::endl;
			out << "|\n"; 
		}
			out << std::endl;
		return out;
	}

	std::deque <vertex_id> GreedyAlgorithm(vertex_id begin, vertex_id destination){
		std::vector <VertexOfAdjacencyList> tmpAdjacencyList(AdjList);
		// std::deque <vertex_id> VisitedVerteces;
		// VisitedVerteces.push_back(begin);
		std::deque <vertex_id> Track;
		Track.push_back(begin);

		while (Track.back() != destination) {
			std::pair<bool, vertex_id> NextVertex = findMinEdge(tmpAdjacencyList, Track.back());
			if (!NextVertex.first){ // Если вершина висячая
				Track.pop_back(); // Вернуться к предыдущей верщине
				if (Track.empty()) // такого пути в графе нет
					break;
			}
			else {
				Track.push_back(NextVertex.second);
				// VisitedVerteces.push_back(NextVertex.second);
			}
		}

		return Track;
	}

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
};

int main() {

	// std::ifstream in(std::stdin);

	AdjacencyList graph;

	char word1;
	char word2;
	double length;
	std::cin >> word1;
	vertex_id begin(word1);
	std::cin >> word1;
	vertex_id destination(word1);

	while (std::cin >> word1 >> word2 >> length){
		graph.addEdge(vertex_id(word1), vertex_id(word2), length);
	}

	std::cout << graph << std::endl;

	std::cout << "Begin: " << begin << std::endl;
	std::cout << "Destination: " << destination << std::endl;
	std::deque <vertex_id> Track =  graph.GreedyAlgorithm(begin, destination);

	for (auto vertex : Track)
		std::cout << vertex;

}
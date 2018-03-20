#pragma once
#include <iostream>
#include <array>
#include <list>
//#include "Vertex.hpp"

namespace DM
{
class Triplet
{
public:
	Triplet();
	Triplet(char name, double weight)
		: name(name), weight(weight)
	{ }
     char name = 0;
     double weight = 0;
	// Deprecated?
	bool isVis = false;
};

class Vertex
{
public:
     Vertex() : name(0) { }
     char getName() const;
	void addEdge(char a, double weight);
	// void getUnvis();
	std::list<DM::Triplet>::iterator getAssocBegin();
	std::list<DM::Triplet>::iterator getAssocEnd();
	// Sort incident edges of this vertex
	void sortEdgesByName();
	void sortEdgesByWeight();
	bool hasEdges();
	void printEdges();
protected:
     // Associated vertices
     // List keeps class with name, weight and bool isVis
     std::list<Triplet> assocVertices;
     // Identifier(name) of a vertex
	char name;
};

class Graph
{
public:
     Graph() = default;
	void read();
	// Read Graph as oriented
	void readOr();
     void addEdge(char a, char b, double weight);
	DM::Vertex& getVertex(char a);
     // Sort incident edges of each vertex
     void sortEdgesByName();
	void sortEdgesByWeight();
	// Print all the Graph
	void print();
     // Find path from a to b and return it in Result
     void pathSearchGreedy(char s, char e, std::list<char>& Result);
     void pathSearch(char s, char e, std::list<char>& Result);
private:
     // Vertices named a-z.
     std::array<Vertex, 26> vertices;
     int vertN = 26;
};
} // namespace DM

#pragma once
#include <iostream>
#include <array>
#include <list>
#include <queue>

namespace DM
{
class Dyad
{
public:
	Dyad();
	Dyad(char name, double weight, double flow = 0)
	: name(name), weight(weight), flow(flow)
	{ }
	char name = '-';
	int weight = 0;
	int flow = 0;
};

class Graph;

class Vertex
{
public:
	friend class Graph;
	Vertex() : name(0) { }
	char getName() const;
	Dyad& to(char a);
	// Returns first element in assicVertices
	Dyad& frontTo();
	void addEdge(char a, int weight, int flow);
	bool hasEdges() const;
	std::list<Dyad>& getEdges();
	void printEdges() const;
	void sortEdgesByFlow(char c = '<');
	std::list<DM::Dyad>::iterator getAssocBegin();
	std::list<DM::Dyad>::iterator getAssocEnd();
	// Sort incident edges of this vertex
	void sortEdgesByName();
	void sortEdgesByWeight(char c = '<');
protected:
	// Associated vertices
	// List keeps class with name and weight
	std::list<Dyad> assocVertices;
	// Identifier(name) of a vertex
	char name = '-';
};

class Graph
{
public:
	Graph()
	{
		for(int i = 0; i < 10; ++i)
			vertices[i].name = i+'0';
		for(int i = 'a'-'0'; i < int('a'-'0'+26); ++i)
			vertices[i].name = i+'0';
	}
	void clear();
	// Read Graph as oriented
	void readOr();
	void read();
	void addEdge(char a, char b, int weight = 0, int flow = 0);
	bool hasEdge(char a, char b) const;
	DM::Vertex& getVertex(char a);
	std::array<Vertex, 100>& getVertices();
	int& getWeight(char a, char b);
	int& getFlow(char a, char b);
	// Sort incident edges of each vertex
	void sortEdgesByName();
	void sortEdgesByWeight(char c = '<');
	void sortEdgesByFlow(char c = '<');
	// Print all the Graph
	void print();
	// Find path from a to b and return it in Result
	void pathSearchGreedy(char s, char e, std::list<char>& Result, char c = '<');
	void pathSearchAStar(char s, char e, std::list<char>& Result);
	void searchMaxFlow(char s, char e, Graph& Result);
	void fillWeights(double w);
	// void addWeight(char a, char b, double weight);
	// void addFlow(char a, char b, double flow);
	const Vertex& at(char c) const;
	void reverse();
	Vertex& at(char c);
	// Returning a graph with edges from both lhs and rhs operands
	Graph operator+(const Graph& rhs);
	Graph& operator=(const Graph& rh);
private:
	// Vertices named a-z.
	std::array<Vertex, 100> vertices;
	int vertN = 100;
};
} // namespace DM

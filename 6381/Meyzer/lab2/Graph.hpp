#pragma once
#include <array>
#include <list>

namespace DM
{
class Pair
{
public:
     char name;
     int weight;
};

class Vertex
{
public:
     Vertex() : id(0) { }
     Vertex(char a) : id(a) { }
     // void setId(char a);
     // void addEdge(char b);
     // void sortEdges();
     char getId() const;
protected:
     // Identifier(name) of a vertex

     // Associated vertices
     // List should keep pair name-weight
     std::list<Pair> assocVertices;
private:
     char id;

};

// class Edge
// {
// public:
//      Edge() : v1(nullptr), v2(nullptr), weight(0) { }
//      // Edge(char a, char b, int w);
//      Edge(Vertex *a, Vertex *b, int w);
// private:
//      Vertex *v1, *v2;
//      int weight;
// };

class Graph
{
public:
     Graph();
     void addEdge(char a, char b, double weight);
     // Sort incident edges of each vertex
     void sortEdges();
     // Find path and print it to the std::cout
     void pathSearchGreedy(char a, char b);
     void pathSearch(char a, char b);
private:
     // Vertices named a-z.
     std::array<Vertex, 26> vertices;
     int vertN;
     int edgN;
};
} // namespace DM

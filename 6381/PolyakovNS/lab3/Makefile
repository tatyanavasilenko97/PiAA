all: Edge.o Vertex.o Graph.o main.o
	g++ -std=c++11 Edge.o Vertex.o Graph.o main.o -o lab3
Vertex.o: Vertex.cpp Vertex.hpp
	g++ -std=c++11 Vertex.cpp -c -o Vertex.o
Graph.o: Graph.cpp Graph.hpp
	g++ -std=c++11 Graph.cpp -c -o Graph.o
Edge.o: Edge.cpp Edge.hpp
	g++ -std=c++11 Edge.cpp -c -o Edge.o
main.o: main.cpp
	g++ -std=c++11 main.cpp -c -o main.o
all: lab2.cpp Edge.o Vertex.o Graph.o Priority_list.o
	g++ -std=c++11 lab2.cpp Edge.o Priority_list.o Vertex.o Graph.o -o lab2
Vertex.o: Vertex.cpp Vertex.hpp
	g++ -std=c++11 Vertex.cpp -c -o Vertex.o
Graph.o: Graph.cpp Graph.hpp
	g++ -std=c++11 Graph.cpp -c -o Graph.o
Edge.o: Edge.cpp Edge.hpp
	g++ -std=c++11 Edge.cpp -c -o Edge.o
Priority_list.o: Priority_list.cpp Priority_list.hpp
	g++ -std=c++11 Priority_list.cpp -c -o Priority_list.o
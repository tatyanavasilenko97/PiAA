all: Astar.o 
	g++ Astar.o -o Astar 
Astar.o: Astar.cpp
	g++ -c Astar.cpp
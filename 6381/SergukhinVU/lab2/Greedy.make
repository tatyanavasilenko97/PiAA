all: Greedy.o 
	g++ Greedy.o -o Greedy 
Greedy.o: Greedy.cpp
	g++ -c Greedy.cpp
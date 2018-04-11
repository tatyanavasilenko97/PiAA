all: greedy Astar
greedy: lab2_greedy.o
	g++ -std=c++11 lab2_greedy.o -o greedy 
Astar: lab2_A_star.o
	g++ -std=c++11 lab2_A_star.o -o Astar 
lab2_greedy.o: lab2_greedy.cpp
	g++ -std=c++11 -c lab2_greedy.cpp 
lab2_A_star.o: lab2_A_star.cpp
	g++ -std=c++11 -c lab2_A_star.cpp 
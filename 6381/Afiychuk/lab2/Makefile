all: greedy a_star

greedy: greedy.o
	g++ greedy.o -o greedy -std=c++11
a_star: A.o
	g++ lab2_2.o -o a_star -std=c++11
greedy.o: greedy.cpp
	g++ -c greedy.cpp -std=c++11
A.o: A.cpp
	g++ -c A.cpp -std=c++11

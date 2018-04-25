all: greedy A

greedy: greedy.o
	g++ greedy.o -o greedy -std=c++11
A: A.o
	g++ lab2_2.o -o A -std=c++11
greedy.o: greedy.cpp
	g++ -c greedy.cpp -std=c++11
A.o: A.cpp
	g++ -c A.cpp -std=c++11

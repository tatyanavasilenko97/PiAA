all: Main.o Node.o Flow.o
	g++ Main.o Node.o Flow.o -o out -std=c++11
Main.o: Main.cpp Node.h Flow.h
	g++ -c Main.cpp -std=c++11
Node.o: Node.cpp Node.h Flow.h
	g++ -c Node.cpp -std=c++11
Flow.o: Flow.cpp Flow.h Node.h
	g++ -c Flow.cpp -std=c++11
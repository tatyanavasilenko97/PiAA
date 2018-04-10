all: lab1.o 
	g++ lab1.o -o lab1 
lab1.o: lab1.cpp
	g++ -c lab1.cpp
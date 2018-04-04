all: lab1 clean

lab1: main.o function.o major_func.o
	g++ main.o function.o major_func.o -o lab1

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

function.o: function.cpp
	g++ -std=c++11 -c function.cpp

major_func.o: major_func.cpp
	g++ -std=c++11 -c major_func.cpp
		
clean:
	rm -rf *.o lab1


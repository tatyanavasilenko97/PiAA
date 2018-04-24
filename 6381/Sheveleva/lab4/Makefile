all: lab1 lab2 clean

lab1: kmp.o 
	g++ kmp.o -o kmp

lab2: cycle.o 
	g++ cycle.o -o cycle

kmp.o: kmp.cpp
	g++ -std=c++11 -c kmp.cpp

cycle.o: cycle.cpp
	g++ -std=c++11 -c cycle.cpp
		
clean:
	rm -rf *.o lab1
	rm -rf *.o lab2

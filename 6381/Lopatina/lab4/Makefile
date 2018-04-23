all: kmp cycle
kmp: kmp.o
	g++ -std=c++11 kmp.o -o kmp 
cycle: cycle.o
	g++ -std=c++11 cycle.o -o cycle 
kmp.o: kmp.cpp
	g++ -std=c++11 -c kmp.cpp 
cylcle.o: cycle.cpp
	g++ -std=c++11 -c cycle.cpp 
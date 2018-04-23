all: Main.o Methods.o
	g++ Main.o Methods.o -o out -std=c++11
Main.o: Main.cpp Methods.h
	g++ -c Main.cpp -std=c++11
Methods.o: Methods.cpp Methods.h
	g++ -c Methods.cpp -std=c++11
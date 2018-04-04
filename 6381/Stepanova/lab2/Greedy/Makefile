all: Main.o Methods.o Vertex.o
	g++ Main.o Methods.o Vertex.o -o out -std=c++11
Main.o: Main.cpp Vertex.h Methods.h
	g++ -c Main.cpp -std=c++11
Methods.o: Methods.cpp Methods.h Vertex.h
	g++ -c Methods.cpp -std=c++11
Vertex.o: Vertex.cpp Vertex.h
	g++ -c Vertex.cpp -std=c++11
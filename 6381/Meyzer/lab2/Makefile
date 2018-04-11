CKEYS = -std=c++11 -static
BLDPATH = ./Build

all: dir $(BLDPATH)/main.o $(BLDPATH)/Graph.o
	g++ $(BLDPATH)/*.o -o $(BLDPATH)/out $(CKEYS)
dir:
	mkdir -p $(BLDPATH)
$(BLDPATH)/main.o: main.cpp $(BLDPATH)/Graph.o
	g++ -c main.cpp -o $(BLDPATH)/main.o $(CKEYS)
$(BLDPATH)/Graph.o: Graph.cpp Graph.hpp
	g++ -c Graph.cpp -o $(BLDPATH)/Graph.o $(CKEYS)

#include <iostream>
#include <vector>
#include <conio.h>
#include <fstream>

using namespace std;

class Pair{
	char neighbor = '0';
	double distance = 0;
public:
	Pair();
	Pair(char neighbor, double distance) : neighbor(neighbor), distance(distance){};
	char getNameOfNeighbor(){ return neighbor; };
	double getDistance(){ return distance; };
};

class Vertex{
	char name;
	int amount_neighbors = 0;
	vector<Pair> neighbors;
	bool visited = 0;
public:
	Vertex(char name) : name(name){};
	Vertex(char name, char neighbor, double distance);
	char getName(){ return name; };
	int &getAmountNeighbors(){ return amount_neighbors; };
	Pair getNeighbors(int n){ return neighbors[n]; };
	vector<Pair>& getNeighbors(){ return neighbors; };
	bool &getVisited(){ return visited; };
	void pushNewNeighbor(char neighbor, double distance);
};

class Pair_prior {
public:
    Vertex vertex;
    double prior;
	char came_back;
    Pair_prior(Vertex vertex, double prior) : vertex(vertex), prior(prior){};
};

Vertex::Vertex(char name, char neighbor, double distance): name(name){
	Pair temp(neighbor, distance);
	neighbors.push_back(temp);
}

void Vertex::pushNewNeighbor(char neighbor, double distance){
	Pair temp(neighbor, distance);
	neighbors.push_back(temp);
}

class Graph{
	int size_list = 0;
	vector<Vertex> list_ver;
public:
	vector<Vertex> getListVer();
	void pushNewRoad(char a, char b, double dist);
	void getInputData(char&, char&);
	void test();
	double heuristic(Vertex vertex, Vertex goal);
	void AStar(char, char);
};

void Graph::pushNewRoad(char a, char b, double dist){
	if(!size_list){
		size_list += 2;
		Vertex tempB(b);
		Vertex tempA(a, b, dist);
		list_ver.push_back(tempA);
		list_ver.push_back(tempB);
		++list_ver[0].getAmountNeighbors();
	}
	else{
		for(int i = 0; i < size_list; i++){
			if(list_ver[i].getName() == a){
				Pair tempB(b, dist);
				list_ver[i].getNeighbors().push_back(tempB);
				++list_ver[i].getAmountNeighbors();
				break;
			}
			if(i == size_list - 1){
				size_list++;
				Vertex tempA(a, b, dist);
				list_ver.push_back(tempA);
				++list_ver[size_list - 1].getAmountNeighbors();
			}
		}
		for(int i = 0; i < size_list; i++){
			if(list_ver[i].getName() == b)
				break;
			if(i == size_list - 1){
				size_list++;
				Vertex tempB(b);
				list_ver.push_back(tempB);
			}
		}
	}
}
	
void Graph::getInputData(char &st, char &finish){
	char ver_a, ver_b;
	double distance;
	char choice;
	system("cls");
	while(1){
		cout << "Input graph from file? (y/n) ";
		choice = getch();
		system("cls");
		switch (choice) {
			case 'y':{
				ifstream fin;
				fin.open("GraphForStar.txt");
				if(!fin){
					cout << "File wasnt founded\n";
					system("pause");
					break;
				}
				fin >> st >> finish;
				while(fin >> ver_a && fin >> ver_b && fin >> distance)
					pushNewRoad(ver_a, ver_b, distance);
				fin.close();
				return;
			}
			case 'n':{
				cin >> st >> finish;
				while(cin >> ver_a){
					if(ver_a == '!')
						break;
					cin >> ver_b && cin >> distance;
					pushNewRoad(ver_a, ver_b, distance);
				}
				return;
			}
			default:
				printf("Repeat command\n");
		}
	}
}

void Graph::AStar(char st, char fin){
	bool neighbor_in_openSet, tentative_is_better, continue_add_neigh;
	int indexCurr;
	double tentative_cost;
	Vertex start('0'), finish('0'), currNeig('0');
	for(int i = 0; i < size_list; i++){
		if(list_ver[i].getName() == st)
			start = list_ver[i];
		if(list_ver[i].getName() == fin)
			finish = list_ver[i];
	}
	vector<Pair_prior> openSet, closedSet;
	openSet.push_back(*(new Pair_prior(start, 0)));
	openSet[0].came_back = '0';
	Pair_prior currPair(*(new Vertex('0')), 0);
	while(!openSet.empty()){
		currPair.prior = 1000;
		for(int i = 0; i < openSet.size(); i++)
			if(currPair.prior > openSet[i].prior){
				currPair = openSet[i];
				indexCurr = i;
			}
		if(currPair.vertex.getName() == finish.getName()){
			vector<char> path;
			while(start.getName() != currPair.vertex.getName())
				for(int i = 0; i < closedSet.size(); i++)
					if(closedSet[i].vertex.getName() == currPair.came_back){
						path.push_back(currPair.vertex.getName());
						currPair = closedSet[i];
					}
			path.push_back(start.getName());
			for(int i = path.size() - 1; i >= 0; i--)
				cout << path[i];
			return;
		}
		openSet.erase(openSet.begin() + indexCurr);
		closedSet.push_back(currPair);
		
		for(int i = 0; i < currPair.vertex.getAmountNeighbors(); i++){ //Test all neighbors
			for(int j = 0; j < list_ver.size(); j++)
				if(currPair.vertex.getNeighbors(i).getNameOfNeighbor() == list_ver[j].getName())
					currNeig = list_ver[j];
			continue_add_neigh = 1;
			for(int j = 0; j < closedSet.size(); j++)                   //
				if(currNeig.getName() == closedSet[j].vertex.getName()) //Miss neighbors from closedSet
					continue_add_neigh = 0;                             //
			if(continue_add_neigh){
					tentative_cost = currPair.prior + currPair.vertex.getNeighbors(i).getDistance();
				neighbor_in_openSet = 0;
				for(int j = 0; j < openSet.size(); j++)
					if(currNeig.getName() == openSet[j].vertex.getName())
						neighbor_in_openSet = 1;
				tentative_is_better = 1;
				if(!neighbor_in_openSet)
					openSet.push_back(*(new Pair_prior(currNeig, tentative_cost + heuristic(currNeig, finish))));
				else
					if(tentative_cost < currPair.prior)
						tentative_is_better = 0;
				if(tentative_is_better)
					for(int j = 0; j < openSet.size(); j++)
						if(currNeig.getName() == openSet[j].vertex.getName())
							openSet[j].came_back = currPair.vertex.getName();
			}
		}
	}
}

double Graph::heuristic(Vertex vertex, Vertex goal){
	double x = (double)goal.getName() - (double)vertex.getName();
	return x > 0 ? x : -x;
}

int main(){
	Graph *graph = new Graph;
	char st, fin;
	graph->getInputData(st, fin);
	graph->AStar(st, fin);
	return 0;
}

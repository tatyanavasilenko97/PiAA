#include <iostream>
#include <vector>
#include <queue>
#include <conio.h>
#include <fstream>

using namespace std;

class Pair{
	char neighbor = '0';
	double distance = 0;
	bool visited = 0;
public:
	Pair();
	Pair(char neighbor, double distance) : neighbor(neighbor), distance(distance){};
	char getNameOfNeighbor(){ return neighbor; };
	double getDistance(){ return distance; };
	bool &getVisited(){ return visited; };
	void getVisited(bool visited){ visited = visited; };
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
	Pair &getNeighbors(int n){ return neighbors[n]; };
	vector<Pair>& getNeighbors(){ return neighbors; };
	bool &getVisited(){ return visited; };
	void pushNewNeighbor(char neighbor, double distance);
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
	void greedy(char, char);
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
				fin.open("GraphForGreedy.txt");
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

void Graph::greedy(char start, char finish){
	int all_visited, min_val, indexNeigh;
	char min_name;
	Vertex curr('0');
	vector<Vertex> path;
	for(int i = 0; i < size_list; i++)
		if(list_ver[i].getName() == start)
			curr = list_ver[i];
	path.push_back(curr);
	while(curr.getName() != finish){
		all_visited = 0;
		for(int i = 0; i < curr.getAmountNeighbors(); i++)
			for(int j = 0; j < path.size(); j++)
				if(curr.getNeighbors(i).getNameOfNeighbor() == path[j].getName())
					curr.getNeighbors(i).getVisited() = 1;
		for(int i = 0; i < curr.getAmountNeighbors(); i++)
			if(curr.getNeighbors(i).getVisited())
				++all_visited;
		if(curr.getAmountNeighbors() && curr.getAmountNeighbors() != all_visited){
			min_val = 100;
			for(int i = 0; i < curr.getAmountNeighbors(); i++)
				if(min_val > curr.getNeighbors(i).getDistance() && !curr.getNeighbors(i).getVisited()){
					min_val = curr.getNeighbors(i).getDistance();
					min_name = curr.getNeighbors(i).getNameOfNeighbor();
					indexNeigh = i;
				}
			for(int i = 0; i < list_ver.size(); i++)
				if(list_ver[i].getName() == min_name)	
					curr = list_ver[i];
			path.push_back(curr);
			path[path.size() - 2].getNeighbors(indexNeigh).getVisited() = 1;
		}
		else{
			path.pop_back();
			curr = path.back();
		}
	}
	for(int i = 0; i < path.size(); i++)
		cout << path[i].getName();
}

int main(){
	Graph *graph = new Graph;
	char st, fin;
	graph->getInputData(st, fin);
	graph->greedy(st, fin);
	return 0;
}

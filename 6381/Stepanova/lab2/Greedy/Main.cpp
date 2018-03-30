#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include "Vertex.h"
#include "Methods.h"

using namespace std;

int main(){
	char StartVertex, EndVertex;//начало и конец
	double Weight = 0.0;//с ребра
	char Vertex1, Vertex2;//инцидентные вершины
	vector<Vertex*> MyGraph;//массив указателей на вершины
	vector<char> Way;//массив для записи пройденного пути
	int S = 0, E = 0;//номер начала и конца
	ifstream fin("Test.txt");

	fin >> StartVertex >> EndVertex;//получение начальной и конечной вершины
	cout << StartVertex <<" "<< EndVertex<<endl;
	while (fin >> Vertex1 >> Vertex2 >> Weight) {//цикл запроса весов ребёр
		ProcessingData(Vertex1, Vertex2, Weight, MyGraph);
		cout<< Vertex1 << " " << Vertex2 << " " << Weight << endl;
	}

	for (int i = 0; i < MyGraph.size(); i++) {//ищем номера начальной и конечной вершины в массиве
		if (MyGraph[i]->getName() == StartVertex)
			S = i;
		if (MyGraph[i]->getName() == EndVertex)
			E = i;
	}

	cout << endl << "Answer: ";
	
	if (GreedyAlgorithm(MyGraph[S], MyGraph[E], Way)) {
		for (int i = 0; i < Way.size(); i++)
			cout << Way[i];
	}

	cout << endl << endl;
	system("pause");
	return 0;
}


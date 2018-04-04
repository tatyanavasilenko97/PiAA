#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include "Vertex.h"
#include "Methods.h"

using namespace std;

int main()
{
	char StartVertex, EndVertex;
	double Weight = 0.0;
	char Vertex1, Vertex2;
	vector<Vertex*> MyGraph;
	vector<Vertex*> Queue;
	vector<char> Way;
	ifstream fin("Test.txt");
	int S = 0, E = 0;//номер начала и конца

	fin >> StartVertex >> EndVertex;//получение начальной и конечной вершины
	cout << StartVertex << " " << EndVertex << endl;
	while (fin >> Vertex1 >> Vertex2 >> Weight) {//цикл запроса весов ребёр
		ProcessingData(Vertex1, Vertex2, Weight, MyGraph);
		cout << Vertex1 << " " << Vertex2 << " " << Weight << endl;
	}

	for (int i = 0; i < MyGraph.size(); i++) {
		if (MyGraph[i]->getName() == StartVertex)
			S = i;
		if (MyGraph[i]->getName() == EndVertex)
			E = i;
	}

	for (int i = 0; i < MyGraph.size(); i++) {//устанавливаем эвристичесвую оценку для каждой вершины
		MyGraph[i]->setHeuristicEvaluation(abs((int)MyGraph[E]->getName() - (int)MyGraph[i]->getName()));
	}

	AstarAlgorithm(MyGraph[S], MyGraph[E], Way, Queue); 
	cout << endl << "Answer: ";
	for (int i = Way.size()-1; i >=0; i--)
		cout << Way[i];

	cout << endl << endl;
	system("pause");
	return 0;
}


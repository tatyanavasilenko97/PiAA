#include "Methods.h"

using namespace std;

void ProcessingData(char Vertex1, char Vertex2, double Weight, vector<Vertex*>& MyGraph) {
	int V1 = -1;
	int V2 = -1;

	for (int i = 0; i < MyGraph.size(); i++) {//проверяем на то, что эти вершины уже были добавлены
		if (Vertex1 == MyGraph[i]->getName())
			V1 = i;
		if (Vertex2 == MyGraph[i]->getName())
			V2 = i;
	}

	if (V1 < 0) {//если нет первой вершины
		Vertex* A1 = new Vertex(Vertex1);
		MyGraph.push_back(A1);
		V1 = MyGraph.size() - 1;
	}
	if (V2 < 0) {//если нет второй вершины
		Vertex* A2 = new Vertex(Vertex2);
		MyGraph.push_back(A2);
		V2 = MyGraph.size() - 1;
	}

	MyGraph[V1]->AddRib(MyGraph[V2], Weight);
	MyGraph[V2]->AddRib(MyGraph[V1], Weight);
}

void AstarAlgorithm(Vertex* StartVertex, Vertex* EndVertex, vector<char>& Way, vector<Vertex*>& Queue) {
	Vertex* NewCurrVertex = StartVertex;
	bool IsSuccess = false;
	NewCurrVertex->setPriority(0.0);//для первого приоритет 0

	while (!IsSuccess) {

		if (NewCurrVertex->getName() == EndVertex->getName())//если дошли до конца
			IsSuccess = true;

		else {//если не дошли до конца
			NewCurrVertex->setIsVisit(true);//посетили вершину
			NewCurrVertex->setRelatedPriorities(Queue);//обрабатываем смежные вершины
			
			std::sort(Queue.begin(), Queue.end(), [](Vertex* a, Vertex* b) {//сортируем по убыванию приоритетов
				return a->getPriority() > b->getPriority();
			});

			NewCurrVertex = Queue[Queue.size()-1];//берём самый приоритетный
			Queue.pop_back();//удалем его
		}
	}

	while (NewCurrVertex != NULL) {
		Way.push_back(NewCurrVertex->getName());
		NewCurrVertex = NewCurrVertex->getCameFrom();
	}
}
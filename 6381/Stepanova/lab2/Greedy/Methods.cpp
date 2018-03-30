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

bool GreedyAlgorithm(Vertex* StartVertex, Vertex* EndVertex, vector<char>& Way) {
	Vertex* NewCurrVertex;
	bool IsSuccess = true;

	if (StartVertex->getName() == EndVertex->getName()) {//если дошли до конца
		Way.push_back(EndVertex->getName());
		return true;
	}

	else {//если не дошли до конца
		Way.push_back(StartVertex->getName());//занесли в ответ вершину
		StartVertex->setIsVisit(true);//посетили вершину
		NewCurrVertex = StartVertex->FindMinRib();//ищем минимальное ребро

		if (NewCurrVertex == NULL) {//если не нашли минимального, значит дальше пути нет
			Way.pop_back();//удаляем из пути текущую вершину
			return false;
		}

		else {//если нашли минимальный
			IsSuccess = GreedyAlgorithm(NewCurrVertex, EndVertex, Way);
			if (IsSuccess)//если дошли до конца
				return true;
			else {//если на предыдущем шаге не нашлось вершины, в которую бы мы могли пойти
				while ((!IsSuccess) && (NewCurrVertex != NULL)) {//пока у нас на какой то из итераций не закончится всё нормально или неракрашенные инцидентные данной вершине не закончатся
					NewCurrVertex = StartVertex->FindMinRib();//ищем минимальное ребро
					if (NewCurrVertex != NULL) {//если нашлось, то запускаем новую итерацию
						IsSuccess = GreedyAlgorithm(NewCurrVertex, EndVertex, Way);
					}
				}
				if (!IsSuccess)//если не получилось найти путь из этой вершины, то удалим ее из пути
					Way.pop_back();//удаляем из пути текущую вершину
				return IsSuccess;
			}
		}
	}
}
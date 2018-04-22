#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <algorithm>

class Vertex 
{
private:
	char Name;//имя вершины
	double Priority;//приоритет для рассмотрения (вес до вершины + Heuristic)
	double Heuristic;//эвристическое значение (разница кодов в ASCII таблице)
	Vertex* CameFrom;//укзатель на вершину из которой мы пришли
	bool IsVisit;//false -не посещена, true - посещена
	std::vector<Vertex*> Ribs;//массив указателей на инцидентные вершин
	std::vector<double> Weight;//массив весов 

public:
	Vertex(char);
	char getName();
	bool getIsVisit();
	void setIsVisit(bool);
	void AddRib(Vertex*, double);
	void setHeuristic(double);
	double getHeuristic();
	void setCameFrom(Vertex*);
	Vertex* getCameFrom();
	void setPriority(double);
	double getPriority();
	void SetPriorityQueue(std::vector<Vertex*>&);
};

using namespace std;

Vertex::Vertex(char name) :Name(name), IsVisit(false), CameFrom(NULL), Priority(0) {}

char Vertex::getName()
{
	return Name;
}

bool Vertex::getIsVisit()
 {
	return IsVisit;
}

void Vertex::setIsVisit(bool answer)
{
	IsVisit = answer;
}

void Vertex::AddRib(Vertex* vertex, double weight)
{
	Ribs.push_back(vertex);
	Weight.push_back(weight);
}

void Vertex::setHeuristic(double delta)
{
	Heuristic = delta;
}

double Vertex::getHeuristic()
{
	return Heuristic;
}

void Vertex::setCameFrom(Vertex* came_from)
{
	CameFrom = came_from;
}

Vertex* Vertex::getCameFrom()
{
	return CameFrom;
}

void Vertex::setPriority(double way_to)
{
	Priority = way_to + Heuristic;
}

double Vertex::getPriority()
{
	return Priority;
}

void Vertex::SetPriorityQueue(vector<Vertex*>& Queue)
{
	double Way_to = Priority - Heuristic;
	bool inQueue = false;

	for (int i = 0; i < Weight.size(); i++)
	{//проставляем приоритет у смежных вершин
		if (!Ribs[i]->getIsVisit()) //если вершина ещё не была посещена
			if (((Way_to + Weight[i] + Ribs[i]->getHeuristic()) < (Ribs[i]->getPriority())) || (Ribs[i]->getPriority() == 0))
			{//если вес легче предыдущего или мы первый раз его устанавливаем
				Ribs[i]->setPriority(Way_to + Weight[i]);//ставим новый приоритет
				Ribs[i]->setCameFrom(this);//меняем поле откуда пришли
				inQueue = false;
				for(int j = 0; j < Queue.size(); j++)//ищем в очереди
					if(Ribs[i]->getName() == Queue[j]->getName())
						inQueue = true;
				if (!inQueue)//если нет в очереди, то добавляем
					Queue.push_back(Ribs[i]);
			}
	}
	//сортируем по убыванию приоритетов
	std:sort( Queue.begin(), Queue.end(),
		[](Vertex* a, Vertex* b)//лямбда-выражение
		{	return a->getPriority() > b->getPriority();	   } );
}

void FillAdjacencyList(char vertex1, char vertex2, double weight, std::vector<Vertex*>& MyGraph);

void Astar(Vertex* StartVertex, Vertex* EndVertex, std::vector<char>& Way, std::vector<Vertex*>& Queue);

int main()
{
	char StartVertex, EndVertex;
	double weight = 0.0;
	char vertex1, vertex2;
	vector<Vertex*> AdjacencyList;//список смежности
	vector<char> Way;
	vector<Vertex*> Queue;//Очередь приоритетов 
	int first = 0, last = 0;//индексы
	cin >> StartVertex >> EndVertex;//получение начальной и конечной вершины
	//cout << StartVertex << " " << EndVertex << endl;
	while (cin >> vertex1 >> vertex2 >> weight)
	{//цикл запроса весов ребёр
		FillAdjacencyList(vertex1, vertex2, weight, AdjacencyList);
		//cout << vertex1 << " " << vertex2 << " " << weight << endl;
	}

	for (int i = 0; i < AdjacencyList.size(); i++)
	{
		if (AdjacencyList[i]->getName() == StartVertex)
			first = i;
		if (AdjacencyList[i]->getName() == EndVertex)
			last = i;
	}

	for (int i = 0; i < AdjacencyList.size(); i++)
	{//устанавливаем эвристичесвую оценку для каждой вершины
		AdjacencyList[i]->setHeuristic(abs((int)AdjacencyList[last]->getName() - (int)AdjacencyList[i]->getName()));
	}

	Astar(AdjacencyList[first], AdjacencyList[last], Way, Queue); 
	//cout << endl << "Answer: ";
	for (int i = Way.size()-1; i >=0; i--)
		cout << Way[i];

	cout << endl << endl;
	return 0;
}

void FillAdjacencyList(char vertex1, char vertex2, double weight, vector<Vertex*>& AdjacencyList)
{
	int v1 = -1;
	int v2 = -1;

	for (int i = 0; i < AdjacencyList.size(); i++)
	{//Если вершины ещё не добавлены
		if (vertex1 == AdjacencyList[i]->getName())
			v1 = i;
		if (vertex2 == AdjacencyList[i]->getName())
			v2 = i;
	}

	if (v1 < 0) 
	{//если нет первой вершины
		Vertex* A1 = new Vertex(vertex1);
		AdjacencyList.push_back(A1);
		v1 = AdjacencyList.size() - 1;
	}
	if (v2 < 0)
	{//если нет второй вершины
		Vertex* A2 = new Vertex(vertex2);
		AdjacencyList.push_back(A2);
		v2 = AdjacencyList.size() - 1;
	}

	AdjacencyList[v1]->AddRib(AdjacencyList[v2], weight);
}

void Astar(Vertex* StartVertex, Vertex* EndVertex, vector<char>& Way, vector<Vertex*>& Queue)
{
	Vertex* NewCurrVertex = StartVertex;
	bool isSuccess = false;
	NewCurrVertex->setPriority(0.0);//для начальной вершины приоритет 0

	while (!isSuccess)//пока не дошли до конца
	{
		if (NewCurrVertex->getName() == EndVertex->getName())//если дошли до конца
			isSuccess = true;

		else
		{//если не дошли до конца
			NewCurrVertex->setIsVisit(true);// отмечаем вершину как посещенную
			NewCurrVertex->SetPriorityQueue(Queue);//обрабатываем смежные вершины

			NewCurrVertex = Queue[Queue.size()-1];//берём самый приоритетный
			Queue.pop_back();//удалем его из очереди
		}
	}

	while (NewCurrVertex != NULL)//идем от конечной вершины в начальную и записываем в путь
	{
		Way.push_back(NewCurrVertex->getName());
		NewCurrVertex = NewCurrVertex->getCameFrom();
	}
}
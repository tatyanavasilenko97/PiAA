#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>

class Vertex {
private:
	char Name;//имя вершины
	bool IsVisit;//false - не посещена, true - посещена
	std::vector<Vertex*> Ribs;//массив указателей на инцидентные вершины
	std::vector<double> Weight;//массив весов между вершинами
public:
	Vertex(char);
	char getName();
	bool getIsVisit();
	void setIsVisit(bool);
	void AddRib(Vertex*, double);
	Vertex* FindMinRib();
};

Vertex::Vertex(char name) :Name(name), IsVisit(false) {}

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

Vertex* Vertex::FindMinRib() 
{
		int minNumber = 0;
		double minWeight = 0.0;
		int currentNumber = 0;

		if (Weight.size()==0)	//если вершина не имеет исходящих из нее ребер
			return NULL;

		while ((minWeight == 0.0) && (currentNumber<Weight.size())) 
		{//находим первый нераскрашенный элемент, чтобы с ним сравнивать
			if (!(Ribs[currentNumber]->getIsVisit()))
			 {//если не раскрашен
				minWeight = Weight[currentNumber];//запоминаем его вес и выходим
				minNumber = currentNumber;
			}
			currentNumber++;
		}

		for (int i = currentNumber; i < Weight.size(); i++)
		 {//ищем минимальное ребро, которое ещё не посещено
			if ((minWeight >= Weight[i]) && (!(Ribs[i]->getIsVisit())))
			 {//если вес ребра меньше последнего минимального и вершина ещё не расркашена
				if (minWeight == Weight[i])
				 {//равен минимальному, тогда идём в лексикографическом порядке
					if ((int)Ribs[i]->getName() < (int)Ribs[minNumber]->getName())
					 {//если текущая буква раньше в алфавите
						minNumber = i;
						minWeight = Weight[i];
					}
				}
				else 
				{//меньше минимального веса
					minNumber = i;//запоминаем номер
					minWeight = Weight[i];//запоминаем вес
				}
			}
		}

		if (Ribs[minNumber]->getIsVisit()) //если не нашли незакрашенных минимальных ребер
			return NULL;

		else //если нашли минимальное незакрашенное ребро
			return Ribs[minNumber];
}

using namespace std;

bool Greedy(Vertex* StartVertex, Vertex* EndVertex, vector<char>& Way);
void FillAdjacencyList(char vertex1, char vertex2, double weight, vector<Vertex*>& AdjacencyList);

int main()
{
	char startVertex, endVertex;//начало и конец
	double weight = 0.0;//вес ребра
	char vertex1, vertex2;
	vector<Vertex*> AdjacencyList;//список смежности
	vector<char> Way;//массив для записи пройденного пути
	int first = 0, last = 0;//номер начала и конца


	cin >> startVertex >> endVertex;//получение начальной и конечной вершины
	while (cin>> vertex1 >> vertex2 >> weight) {//цикл запроса весов ребёр
		FillAdjacencyList(vertex1, vertex2, weight, AdjacencyList);
	}

	for (int i = 0; i < AdjacencyList.size(); i++) {//ищем номера начальной и конечной вершины в массиве
		if (AdjacencyList[i]->getName() == startVertex)
			first = i;
		if (AdjacencyList[i]->getName() == endVertex)
			last = i;
	}

	
	if (Greedy(AdjacencyList[first], AdjacencyList[last], Way)) {
		for (int i = 0; i < Way.size(); i++)
			cout << Way[i];
	}


	return 0;
}

void FillAdjacencyList(char vertex1, char vertex2, double weight, vector<Vertex*>& AdjacencyList)
{
	int v1 = -1;
	int v2 = -1;

	for (int i = 0; i < AdjacencyList.size(); i++)
	{
		if (vertex1 == AdjacencyList[i]->getName())
			v1 = i;
		if (vertex2 == AdjacencyList[i]->getName())
			v2 = i;
	}

	if (v1 < 0)
	{
		Vertex* A1 = new Vertex(vertex1);
		AdjacencyList.push_back(A1);
		v1 = AdjacencyList.size() - 1;
	}
	
	if (v2 < 0)
	{
		Vertex* A2 = new Vertex(vertex2);
		AdjacencyList.push_back(A2);
		v2 = AdjacencyList.size() - 1;
	}

	AdjacencyList[v1]->AddRib(AdjacencyList[v2], weight);
}

bool Greedy(Vertex* StartVertex, Vertex* EndVertex, vector<char>& Way) 
{
	Vertex* NewCurrVertex;
	bool isSuccess = true;

	Way.push_back(StartVertex->getName());
	StartVertex->setIsVisit(true);

	if (StartVertex->getName() == EndVertex->getName()) // если добрались до конечной вершины
		return true;
	

	else // если не добрались до конечной вершины
	{

		while( ( NewCurrVertex = StartVertex->FindMinRib() )!=NULL )
		{
			isSuccess = Greedy(NewCurrVertex, EndVertex, Way);
			if (isSuccess)
				return true;
		}

		Way.pop_back();
		return false;

	}
		
}
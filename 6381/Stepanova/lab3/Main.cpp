#include <iostream>
#include <fstream>
#include <math.h>
#include "Node.h"
#include "Flow.h"

using namespace std;

void ProcessingData(char node1, char node2, int value, vector<Node*>& MyNetwork, vector<Flow*>& MyNetworkFlow) {
	int V1 = -1;
	int V2 = -1;
	bool NeedToAdd = true;

	for (int i = 0; i < MyNetwork.size(); i++) {//проверяем на то, что эти вершины уже были добавлены
		if (node1 == MyNetwork[i]->getName())
			V1 = i;
		if (node2 == MyNetwork[i]->getName())
			V2 = i;
	}

	if (V1 < 0) {//если нет первой вершины
		Node* A1 = new Node(node1);
		MyNetwork.push_back(A1);
		V1 = MyNetwork.size() - 1;
	}
	if (V2 < 0) {//если нет второй вершины
		Node* A2 = new Node(node2);
		MyNetwork.push_back(A2);
		V2 = MyNetwork.size() - 1;
	}

	for (int i = 0; i < MyNetworkFlow.size(); i++) {
		if ((MyNetworkFlow[i]->getBegin()->getName() == node2) && (MyNetworkFlow[i]->getEnd()->getName() == node1)) {
			MyNetworkFlow[i]->getPair()->setFlowValue(value);
			MyNetworkFlow.push_back(MyNetworkFlow[i]->getPair());
			NeedToAdd = false;
		}
	}

	if (NeedToAdd) {
		MyNetworkFlow.push_back(MyNetwork[V1]->newFlowOut(MyNetwork[V2], value));//создаём ребро и кладём в список
	}
}

int FordFulkersonAlgorithm(Node* StartNode, Node* EndNode, Node* CurrentNode, Node* PastNode, vector<int>& Way) {
	Flow* currentFlow = NULL;//выбранное ребро
	int Sub = 0;//то, что будем вычитать

	if (CurrentNode == EndNode) {//если дошли до конца
		sort(Way.begin(), Way.end(), [](int a, int b) {//сортируем по возрастанию величин потоков
			return a < b;
		});

		return Way[0];//возвращаем минимальный, который нужно вычесть
	}

	else {//если не дошли до конца
		currentFlow = CurrentNode->findMaxFlowOut(StartNode, PastNode);//ищем поток, по которому можем пойти

		while ((currentFlow != NULL) && (Sub <= 0)) {//пока есть куда ходить

			Way.push_back(currentFlow->getFlowValue());//положили значение в вектор

			Sub = FordFulkersonAlgorithm(StartNode, EndNode, currentFlow->getEnd(), CurrentNode, Way);//вызываем новый цикл функции

			if (Sub > 0) {//если мы дошли и всё хорошо
				currentFlow->subFlowValue(Sub);//вычитаем
				currentFlow->getPair()->subFlowValue(-Sub);
				if (CurrentNode == StartNode)
					Sub = 0;//зануляем, чтобы не выйти из цикла для истока
			}

			else {
				currentFlow->mulFlowValue(-1);//зануляем поток, чтобы не ходить по нему 1000 раз
			}

			Way.pop_back();//достаём то, что положили на этом цикле
			currentFlow = CurrentNode->findMaxFlowOut(StartNode, PastNode);//ищем поток, по которому можем пойти
		}

		if (Sub > 0)
			return Sub;
		else
			return -1;
	}
}

int main()
{
	int number = 0;//количество ребер
	char begin, end;//начало и конец
	char node1, node2;//узлы
	int value = 0;//величина потока
	vector<Node*> MyNetwork;//для хранения сети (вершины)
	vector<Flow*> MyNetworkFlow;//для хранения сети (ребра)
	int S = 0, E = 0;//номера начала и конца
	vector<int> Way;
	int Input = 0;
	ifstream fin("Test.txt");

	fin >> number;
	cout << number << endl;
	fin >> begin >> end;
	cout << begin << " " << end << endl;
	for (int i = 0; i < number; i++) {
		fin >> node1 >> node2 >> value;
		cout << node1 << " " << node2 << " " << value << endl;
		ProcessingData(node1, node2, value, MyNetwork, MyNetworkFlow);
	}

	for (int i = 0; i < MyNetwork.size(); i++) {
		if (MyNetwork[i]->getName() == begin)
			S = i;
		if (MyNetwork[i]->getName() == end)
			E = i;
	}

	for (int i = 0; i < MyNetworkFlow.size(); i++) {
		MyNetworkFlow[i]->setMaxFlowValue(MyNetworkFlow[i]->getFlowValue());
		if (MyNetworkFlow[i]->getEnd()->getName() == MyNetwork[E]->getName())
			Input += MyNetworkFlow[i]->getFlowValue();
	}

	FordFulkersonAlgorithm(MyNetwork[S], MyNetwork[E], MyNetwork[S], MyNetwork[S], Way);

	for (int i = 0; i < MyNetworkFlow.size(); i++) {
		if (MyNetworkFlow[i]->getEnd()->getName() == MyNetwork[E]->getName())
			Input -= MyNetworkFlow[i]->getFlowValue();
	}

	cout <<endl<< Input << endl;

	sort(MyNetworkFlow.begin(), MyNetworkFlow.end(), [](Flow* a, Flow* b) {//сортируем по возрастанию величин потоков
		if (a->getBegin()->getName() == b->getBegin()->getName()) //если совпадают первые буквы
			return a->getEnd()->getName() < b->getEnd()->getName();
		else
			return a->getBegin()->getName() < b->getBegin()->getName();
	});

	for (int i = 0; i < MyNetworkFlow.size(); i++) {
		cout << (MyNetworkFlow[i]->getBegin())->getName() << " " << (MyNetworkFlow[i]->getEnd())->getName() << " ";
		if ((MyNetworkFlow[i]->getMaxFlowValue() - abs(MyNetworkFlow[i]->getFlowValue())) > 0)
			cout << MyNetworkFlow[i]->getMaxFlowValue() - abs(MyNetworkFlow[i]->getFlowValue()) << endl;
		else
			cout << 0 << endl;
	}

	return 0;
}
#include <iostream>
#include <fstream>
#include "Node.h"
#include "Flow.h"

using namespace std;

void ProcessingData(char node1, char node2, int value, vector<Node*>& MyNetwork, vector<Flow*>& MyNetworkFlow) {
	int V1 = -1;
	int V2 = -1;
	Flow* newFlow = NULL;

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

	newFlow = MyNetwork[V1]->addFlowOut(MyNetwork[V2], value);//создаём ребро
	MyNetwork[V2]->addFlowIn(newFlow);//кладём в вершины
	MyNetworkFlow.push_back(newFlow);//создаём ребро и кладём в список
}

int FordFulkersonAlgorithm(Node* StartNode, Node* EndNode, Node* CurrentNode, Node* PastNode, vector<int>& Way) {
	Flow* currentFlow = NULL;//выбранное ребро
	int Sub = 0;//то, что будем вычитать
	int K = 1;

	if (CurrentNode == EndNode) {//если дошли до конца
		sort(Way.begin(), Way.end(), [](int a, int b) {//сортируем по возрастанию величин потоков
			return a < b;
		});
					
		return Way[0];//возвращаем минимальный, который нужно вычесть
	}

	else{//если не дошли до конца
		currentFlow = CurrentNode->findMaxFlowOut();//ищем поток, по которому можем пойтb
		if (currentFlow == NULL) {
			currentFlow = CurrentNode->findMaxFlowIn(StartNode, PastNode);
			if (currentFlow != NULL)
				K = -1;
		}

		while ((currentFlow != NULL) && (Sub <= 0)) {//пока есть куда ходить
			if (K > 0) {
				Way.push_back(currentFlow->getFlowValue());//положили значение в вектор
				Sub = FordFulkersonAlgorithm(StartNode, EndNode, currentFlow->getEnd(), CurrentNode, Way);//вызываем новый цикл функции
			}
			else {
				Way.push_back(currentFlow->getActualFlowValue());//положили значение в вектор
				Sub = FordFulkersonAlgorithm(StartNode, EndNode, currentFlow->getBegin(),CurrentNode, Way);//вызываем новый цикл функции
			}
								

			if (Sub > 0) {//если мы дошли и всё хорошо
				currentFlow->addFlowValue(Sub*K);//вычитаем
				if (CurrentNode == StartNode)
					Sub = 0;//зануляем, чтобы не выйти из цикла для истока
			}
			else {
				currentFlow->setFlowValue(0);//зануляем поток, чтобы не ходить по нему 1000 раз
			}
			Way.pop_back();//достаём то, что положили на этом цикле
			K = 1;
			currentFlow = CurrentNode->findMaxFlowOut();//ищем поток, по которому можем пойти
			if (currentFlow == NULL) {
				currentFlow = CurrentNode->findMaxFlowIn(StartNode, PastNode);
				if (currentFlow != NULL)
					K = -1;
			}
		}

		if(CurrentNode==StartNode)
			return StartNode->countMaxFlow();
		else {
			if (Sub > 0)
				return Sub;
			else
				return -1;
		}	
	}
}

int main()
{
	int number=0;//количество
	char begin, end;//начало и конец
	char node1, node2;//узлы
	int value = 0;//величина потока
	vector<Node*> MyNetwork;//для хранения сети (вершины)
	vector<Flow*> MyNetworkFlow;//для хранения сети (ребра)
	int S = 0, E = 0;//номера начала и конца
	vector<int> Way;
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

	cout<<endl<<FordFulkersonAlgorithm(MyNetwork[S], MyNetwork[E], MyNetwork[S], MyNetwork[S],Way)<<endl;

	sort(MyNetworkFlow.begin(), MyNetworkFlow.end(), [](Flow* a, Flow* b) {//сортируем по возрастанию величин потоков
		if (a->getBegin()->getName() == b->getBegin()->getName()) //если совпадают первые буквы
			return a->getEnd()->getName() < b->getEnd()->getName();
		else
			return a->getBegin()->getName() < b->getBegin()->getName();
		});

	for (int i = 0; i < MyNetworkFlow.size(); i++) {
		cout << (MyNetworkFlow[i]->getBegin())->getName() << " " << (MyNetworkFlow[i]->getEnd())->getName() << " " << MyNetworkFlow[i]->getActualFlowValue() << endl;
	}

    return 0;
}


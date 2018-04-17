#pragma once
class Node;
#include <vector>
#include <algorithm>
#include "Flow.h"

class Node
{
private:
	char Name;//символ, которым обозначается вершина
	std::vector<Flow*> FlowsOut;//исходящие потоки
	std::vector<Flow*> FlowsIn;//входящие потоки

public:
	Node(char name);
	~Node();
	char getName();//для взятия имени

	Flow* addFlowOut(Node* node, int weight);//устанавливаем исходящие потоки
	void addFlowIn(Flow* flow);//устанавливаем входящие потоки

	Flow* findMaxFlowOut();//ищет максимальный поток
	Flow* findMaxFlowIn(Node* Start, Node* Current);//ищет максимальный поток

	int countMaxFlow();//считает максимальный поток
};


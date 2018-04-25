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
public:
	Node(char name);
	~Node();
	char getName();//для взятия имени
	Flow* newFlowOut(Node* node, int weight);//устанавливаем исходящие потоки
	void addFlowOut(Flow* newFlow);//добавляем исходящие потоки
	Flow* findMaxFlowOut(Node* Start, Node* Current);//ищет максимальный поток
};


#include "Node.h"
#include<iostream>

Node::Node(char name) {
	Name = name;
}

Node::~Node() {
}

char Node::getName() {
	return Name;
}

void Node::addFlowOut(Flow* newFlow) {
	FlowsOut.push_back(newFlow);
}

Flow* Node::newFlowOut(Node* node, int weight) {
	Flow* newFlow = new Flow(this, node, weight);//создаём новое ребро
	Flow* newPair = new Flow(node, this, 0);
	newFlow->setPair(newPair);
	newPair->setPair(newFlow);
	FlowsOut.push_back(newFlow);//записываем в вектор
	node->addFlowOut(newPair);
	return newFlow;//возвращаем указатель
}

Flow* Node::findMaxFlowOut(Node* Start, Node* Current) {
	Flow* ret = NULL;
	int size = FlowsOut.size();

	if (FlowsOut.size() > 0) {
		std::sort(FlowsOut.begin(), FlowsOut.end(), [](Flow* a, Flow* b) {//сортируем по возрастанию величин потоков
			return a->getFlowValue() < b->getFlowValue();
		});

		while ((size > 0) && (FlowsOut[size - 1]->getFlowValue() > 0) && ((FlowsOut[size - 1]->getEnd()->getName() == Start->getName()) || (FlowsOut[size - 1]->getEnd()->getName() == Current->getName())))
			size--;
		if (size > 0) {
			if (FlowsOut[size - 1]->getFlowValue() > 0)
				ret = FlowsOut[size - 1];
		}
	}

	return ret;
}

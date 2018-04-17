#include "Node.h"

Node::Node(char name){
	Name = name;
}

Node::~Node(){
}

char Node::getName() {
	return Name;
}

Flow* Node::addFlowOut(Node* node, int weight) {
	Flow* newFlow = new Flow(this, node, weight);//создаём новое ребро
	FlowsOut.push_back(newFlow);//записываем в вектор
	return newFlow;//возвращаем указатель
}

void Node::addFlowIn(Flow* flow) {
	FlowsIn.push_back(flow);//записываем в вектор
}

Flow* Node::findMaxFlowOut() {
	Flow* ret=NULL;

	if (FlowsOut.size() > 0) {
		std::sort(FlowsOut.begin(), FlowsOut.end(), [](Flow* a, Flow* b) {//сортируем по возрастанию величин потоков
			return a->getFlowValue() < b->getFlowValue();
		});

		if (FlowsOut[FlowsOut.size() - 1]->getFlowValue() > 0)//если есть куда идти
			ret = FlowsOut[FlowsOut.size() - 1];
	}
	return ret;
}

Flow* Node::findMaxFlowIn(Node* Start, Node* Current) {
	Flow* ret = NULL;
	int size = FlowsIn.size();
	if (size > 0) {
		std::sort(FlowsIn.begin(), FlowsIn.end(), [](Flow* a, Flow* b) {//сортируем по возрастанию величин потоков
			return a->getActualFlowValue() < b->getActualFlowValue();
		});

		if (FlowsIn[size - 1]->getActualFlowValue() > 0) {//есть смысл мучиться
			while ((size > 0) && (FlowsIn[size - 1]->getActualFlowValue() > 0) && ((FlowsIn[size - 1]->getBegin()->getName() == Start->getName()) || (FlowsIn[size - 1]->getBegin()->getName() == Current->getName())))
				size--;
			if (size > 0) {
				if (FlowsIn[size - 1]->getActualFlowValue() > 0)
					ret = FlowsIn[size - 1];
			}
		}
	}

	return ret;
}

int Node::countMaxFlow() {
	int Summ=0;
	for (int i = 0; i < FlowsOut.size(); i++) {
		Summ += FlowsOut[i]->getActualFlowValue();
	}
	return Summ;
}
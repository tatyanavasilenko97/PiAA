#include "Flow.h"

Flow::Flow(Node* begin, Node* end, int value){
	Begin = begin;
	End = end;
	FlowValue = value;
	ActualFlowValue = 0;
}

Flow::~Flow(){
}

int Flow::getFlowValue() {
	return FlowValue;
}

int Flow::getActualFlowValue() {
	return ActualFlowValue;
}

void Flow::setFlowValue(int value) {
	FlowValue = value;
}

Node* Flow::getEnd() {
	return End;
}

Node* Flow::getBegin() {
	return Begin;
}

void Flow::addFlowValue(int value) {
	FlowValue -= value;
	ActualFlowValue += value;
}

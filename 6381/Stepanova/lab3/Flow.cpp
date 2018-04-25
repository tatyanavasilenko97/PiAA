#include "Flow.h"

Flow::Flow(Node* begin, Node* end, int value) {
	Begin = begin;
	End = end;
	FlowValue = value;
}

Flow::~Flow() {
}

int Flow::getFlowValue() {
	return FlowValue;
}

int Flow::getMaxFlowValue() {
	return MaxFlowValue;
}

void Flow::mulFlowValue(int value) {
	FlowValue *= value;
}

void Flow::setMaxFlowValue(int value) {
	MaxFlowValue = value;
}

void Flow::setFlowValue(int value) {
	FlowValue = value;
}

void Flow::subFlowValue(int value) {
	FlowValue -= value;
}

Node* Flow::getEnd() {
	return End;
}

Node* Flow::getBegin() {
	return Begin;
}

void Flow::setPair(Flow* pair) {
	Pair = pair;
}

Flow* Flow::getPair() {
	return Pair;
}
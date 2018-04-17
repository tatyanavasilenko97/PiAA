#pragma once
class Flow;
#include "Node.h"

class Flow
{
private:
	Node* Begin;//указател на узел из которого течет поток
	Node* End;//указател на узел в который течет поток
	int FlowValue;//величина потока
	int ActualFlowValue;//актуальная величина потока
public:
	Flow(Node* begin, Node* end, int value);
	~Flow();

	int getFlowValue();
	int getActualFlowValue();

	void setFlowValue(int value);

	void addFlowValue(int value);

	Node* getEnd();
	Node* getBegin();
	
};


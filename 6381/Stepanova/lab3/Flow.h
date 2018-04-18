#pragma once
class Flow;
#include "Node.h"

class Flow
{
private:
	Node* Begin;//указател на узел из которого течет поток
	Node* End;//указател на узел в который течет поток
	int FlowValue;//актуальная величина потока
	int MaxFlowValue;//
	Flow* Pair;//пара данному ребру в другом направлении
public:
	Flow(Node* begin, Node* end, int value);
	~Flow();
	int getFlowValue();
	int getMaxFlowValue();
	void mulFlowValue(int value);
	void setFlowValue(int value);
	void subFlowValue(int value);
	void setMaxFlowValue(int value);
	Node* getEnd();
	Node* getBegin();
	void setPair(Flow* pair);
	Flow* getPair();
};


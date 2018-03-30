#pragma once
#include <vector>
#include <stddef.h>

class Vertex {
private:
	char Name;//имя вершины
	bool IsVisit;//false - не раскрашена, true - раскрашена
	std::vector<Vertex*> Ribs;//массив указателей на инцидентные вершины
	std::vector<double> Weight;//массив весов между вершинами
public:
	Vertex(char);
	char getName();
	bool getIsVisit();
	void setIsVisit(bool);
	void AddRib(Vertex*, double);
	Vertex* FindMinRib();
};
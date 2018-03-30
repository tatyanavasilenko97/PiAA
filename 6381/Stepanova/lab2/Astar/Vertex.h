#pragma once
#include <vector>
#include <stddef.h>

class Vertex {
private:
	char Name;//имя вершины
	double Priority;//приоритет для рассмотрения
	double HeuristicEvaluation;//разница кодов в ASCII таблице 
	Vertex* CameFrom;//укзатель на вершину из которой мы пришли
	bool IsVisit;//false - не раскрашена, true - раскрашена
	std::vector<Vertex*> Ribs;//массив указателей на инцидентные вершины
	std::vector<double> Weight;//массив весов между вершинами
public:
	Vertex(char);
	char getName();
	bool getIsVisit();
	void setIsVisit(bool);
	void AddRib(Vertex*, double);
	void setHeuristicEvaluation(double);
	double getHeuristicEvaluation();
	void setCameFrom(Vertex*);
	Vertex* getCameFrom();
	void setPriority(double);
	double getPriority();
	void setRelatedPriorities(std::vector<Vertex*>&);
};
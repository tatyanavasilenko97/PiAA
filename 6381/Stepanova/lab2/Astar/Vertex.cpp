#include "Vertex.h"

using namespace std;

Vertex::Vertex(char name) :Name(name), IsVisit(false), CameFrom(NULL), Priority(0) {}

char Vertex::getName() {
	return Name;
}

bool Vertex::getIsVisit() {
	return IsVisit;
}

void Vertex::setIsVisit(bool answer) {
	IsVisit = answer;
}

void Vertex::AddRib(Vertex* vertex, double weight) {
	Ribs.push_back(vertex);
	Weight.push_back(weight);
}

void Vertex::setHeuristicEvaluation(double delta) {
	HeuristicEvaluation = delta;
}

double Vertex::getHeuristicEvaluation() {
	return HeuristicEvaluation;
}

void Vertex::setCameFrom(Vertex* came_from) {
	CameFrom = came_from;
}

Vertex* Vertex::getCameFrom() {
	return CameFrom;
}

void Vertex::setPriority(double length) {
	Priority = length + HeuristicEvaluation;
}

double Vertex::getPriority() {
	return Priority;
}

void Vertex::setRelatedPriorities(vector<Vertex*>& Queue) {
	double Way_to = Priority - HeuristicEvaluation;
	bool inQueue = false;

	for (int i = 0; i < Weight.size(); i++) {//проставляем приоритет у смежных вершин
		if (!Ribs[i]->getIsVisit()) //если вершина ещё не была посещена
			if (((Way_to + Weight[i] + Ribs[i]->getHeuristicEvaluation()) < (Ribs[i]->getPriority())) || (Ribs[i]->getPriority() == 0)) {//если вес легче предыдущего или мы первый раз его устанавливаем
				Ribs[i]->setPriority(Way_to + Weight[i]);//ставим новый приоритет
				Ribs[i]->setCameFrom(this);//меняем поле откуда пришли
				inQueue = false;
				for(int j = 0; j < Queue.size(); j++)//ищем в очереди
					if(Ribs[i]->getName() == Queue[j]->getName())
						inQueue = true;
				if (!inQueue)//если нет в очереди, то добавляем
					Queue.push_back(Ribs[i]);
			}
	}
}
#include "Vertex.h"

using namespace std;

Vertex::Vertex(char name) :Name(name), IsVisit(false) {}

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

Vertex* Vertex::FindMinRib() {
		int MinNumber = 0;
		double MinWeight = 0.0;
		int CurrentNumber = 0;

		while ((MinWeight == 0.0) && (CurrentNumber<Weight.size())) {//находим первый нераскрашенный элемент, чтобы с ним сравнивать
			if (!(Ribs[CurrentNumber]->getIsVisit())) {//если не раскрашен
				MinWeight = Weight[CurrentNumber];//запоминаем его вес и выходим
				MinNumber = CurrentNumber;
			}
			CurrentNumber++;
		}

		for (int i = CurrentNumber; i < Weight.size(); i++) {//ищем минимальное ребро, которое ещё не посещено
			if ((MinWeight >= Weight[i]) && (!(Ribs[i]->getIsVisit()))) {//если вес ребра меньше последнего минимального и вершина ещё не расркашена
				if (MinWeight == Weight[i]) {//равен минимальному, тогда идём в лексикографическом порядке
					if ((int)Ribs[i]->getName() < (int)Ribs[MinNumber]->getName()) {//если текущая буква раньше в алфавите
						MinNumber = i;
						MinWeight = Weight[i];
					}
				}
				else {//меньше минимального веса
					MinNumber = i;//запоминаем номер
					MinWeight = Weight[i];//запоминаем вес
				}
			}
		}

		if (Ribs[MinNumber]->getIsVisit()) //если не нашли незакрашенных минимальных ребер
			return NULL;

		else //если нашли минимальное незакрашенное ребро
			return Ribs[MinNumber];
}
#include "Methods.h"

void PrefixFunction(std::string& Common, std::vector<unsigned long long int>& Pi) {
	int k = 0;

	Pi[0] = 0;//у первого символа 0
	for (int i = 1; i < Common.size(); i++) {//проходим по всем элементам
		k = Pi[i - 1];
		while (k > 0 && Common[i] != Common[k]) {
			k = Pi[k - 1];
		}
		if (Common[i] == Common[k])
			k++;
		Pi[i] = k;
	}
}

void AlgorithmKMP(std::string& P, std::string& T) {
	std::string Common = P + '\0' + T;//создали P#T
	std::vector<unsigned long long int> Pi(Common.size());//создали Пи массив
	unsigned long long int ps = P.size();//запоминаем размеры
	unsigned long long int ts = T.size();
	unsigned int count = 0;//считает количество ответов для вывода

	PrefixFunction(Common, Pi);//заполняем Пи массив

	for (unsigned long long int i = ps + 1; i < Pi.size(); i++) {
		if (Pi[i] == ps) {//если является ответом
			if (count == 0) {//если первый ответ
				std::cout << i - 2 * ps;//выводим на экран без запятой
				count++;
			}
			else//иначе с запятой
				std::cout << "," << i - 2 * ps;
		}
	}
	if (count == 0)//если не было ответов, то выводим -1
		std::cout << -1;
}
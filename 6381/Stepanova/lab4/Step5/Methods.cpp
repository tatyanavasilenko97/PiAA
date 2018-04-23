#include "Methods.h"

void PrefixFunction(std::string& Common, std::vector<unsigned long long int>& Pi, unsigned long long int start, unsigned long long int end) {
	int k = 0;

	Pi[0] = 0;//для первого 0
	for (unsigned long long int i = start+1; i < end; i++) {//проходим от start до end не включительно
		k = Pi[i - 1-start];
		while (k > 0 && Common[i] != Common[k+start]) {
			k = Pi[k - 1];
		}
		if (Common[i] == Common[k+start])
			k++;
		Pi[i-start] = k;
	}
}

unsigned long long int AlgorithmKMP(std::string& A, std::string& B) {
	std::string Common = B + '\0' + A;//создали P#T
	std::vector<unsigned long long int> Pi(Common.size());//Пи массив
	unsigned long long int as = A.size();//запоминаем размеры
	unsigned long long int bs = B.size();
	unsigned long long int cs = Common.size();

	PrefixFunction(Common, Pi, 0, Common.size());//заполняем Пи массив

	for (unsigned long long int i = as + 1; i < cs; i++) {//проходим по всем элементам второй части Пи массива
		if (Pi[i] == 1) {//возможно, это начало
			bool eq = true;//переменная для выхода

			for (unsigned long long int j = 0; j < cs - i && eq; j++) {//проверяем до конца
				if (Pi[i + j] != j + 1)//если последовательность нарушилась
					eq = false;//то это не вхождение
			}

			if (eq) {//если последовательность прошла до конца массива
				unsigned long long int ns = 2 *i - cs;
				std::vector<unsigned long long int> newPi(2 *i - cs);//создаём новый Пи массив для проверки

				PrefixFunction(Common, newPi, cs - i, i);//проверяем

				for (unsigned long long int j = 0; j < (ns-1)/2 && eq; j++) {//если от начала и до конца второй части это последовательность +1
					if (newPi[(ns+1)/2+j] != j + 1)//если где то нарушилось
						eq = false;//это не является вхождением
				}

				if (eq)//если нашли вхождение
					return i - as - 1;//возвращаем номер
			}
		}
	}
	return -1;//если не нашли вхождений
}
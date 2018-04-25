#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Methods.h"

using namespace std;

int main()
{
	ifstream fin("Test.txt");
	string P;//шаблон
	string T;//текст

	fin >> P >> T;//считываем строки
	cout<<P<<endl<<T<<endl;//выводим на экран

	if ((T.size() >= P.size()) && (!P.empty()) && (!T.empty())) {//если шаблон больше текста или строки пусты, то нет смысла их сравнивать
		AlgorithmKMP(P, T);
	}

	else {//поэтому выводим -1 сразу
		cout << -1;
	}

	return 0;
}

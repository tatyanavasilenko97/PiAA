#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Methods.h"

using namespace std;

int main()
{
	ifstream fin("Test.txt");
	string A;//строка A
	string B;//строка B

	fin >> A >> B;
	cout<<A<<endl<<B<<endl;

	if ((A.size() == B.size()) && (!A.empty()) && (!B.empty())) {//если строки пусты или их размеры не совпадают, нет смысла их проверять
		cout<<AlgorithmKMP(A, B);
	}

	else {
		cout << -1;
	}

	return 0;
}
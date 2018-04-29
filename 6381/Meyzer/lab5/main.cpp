#include <iostream>
#include <string>
#include <vector>

using namespace std;


void readData(string &Text, unsigned& PattN, vector<string> &Patterns)
{
	cin >> Text >> PattN;
	string Pattern;
	for (unsigned i = 0; i < PattN; ++i)
	{
		cin >> Pattern;
		Patterns.push_back(Pattern);
	}
}

int main()
{
	string Text;
	unsigned PattN = 0;
	vector<string> Patterns;
	readData(Text, PattN, Patterns);

	return 0;
}

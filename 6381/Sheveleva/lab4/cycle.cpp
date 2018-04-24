#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

int main ()
{
	string text, cycle;
	cin >> cycle >> text; ;

	string bonding = text + '\n' + cycle + cycle;
	int size = text.size();

	string().swap(cycle);//перемещение во временный объект, где потом вызывается диструктор
	string().swap(text);

	vector <int> prefix(bonding.size());

	prefix[0]=0;

	for(int i = size + 1, j = 0; i < bonding.size(); i++)
	{
		while(j > 0 && bonding[i] != bonding[j])
			j=prefix[j - 1];

		if(bonding[i] == bonding[j]) j++;
		prefix[i] = j;

		if (prefix[i] == size)
		{
			cout<< (i - size*2)<<endl;
			return 0;
		}
	}

	cout<< -1<<endl;
	return 0;
}

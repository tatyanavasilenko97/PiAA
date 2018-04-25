#include <iostream>
#include <string.h>
using namespace std;

int* prefix_function(string text)
{
	int* prefix = new int[text.size()];
	
	prefix[0]=0;
	
	for(int i = 1, j = 0; i < text.size(); i++)
	{
		while(j > 0 && text[i] != text[j])
			j=prefix[j - 1];
		if(text[i] == text[j]) j++;
		prefix[i] = j;
	}
	return prefix;
}

int main ()
{
	string text, pattern, bonding;

	cin >> pattern >> text;
	bonding = pattern + '\n' + text;

	int* prefix = new int [bonding.size()];

	prefix = prefix_function(bonding);

	bool flag = true;
	for (int i = pattern.size() * 2 - 1; i < bonding.size(); i++)
		if (prefix[i] == pattern.size())
		{
			if (flag == false) cout << ',';
			cout << i - pattern.size() * 2;
			flag = false;
		}
	if (flag == true) cout << "-1";
	cout << endl;

	return 0;
}

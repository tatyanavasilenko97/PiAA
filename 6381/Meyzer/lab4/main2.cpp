#include <iostream>
#include <string>
#include <vector>
#define DEBUG
using namespace std;

void prefixEval(const string& Text1, const string& Text2, vector<unsigned>& Result, unsigned& ResultSize)
{
	ResultSize=0;
	Result[ResultSize]=0;
	++ResultSize;
	for(size_t i = 1; i < Text1.size(); ++i)
	{
		size_t k = Result[i-1];
		while(k>0 && Text1[i]!=Text1[k])
			k = Result[k-1];
		if (Text1[i]==Text1[k])
			++k;
		Result[ResultSize]=k;
		++ResultSize;
	}
	Result[ResultSize]=0;
	++ResultSize;
	size_t size1 = Text1.size();
	size_t size2 = Text2.size();
	for(size_t i = 0; i < size2*2; ++i)
	{
		size_t k = Result[i+size1];
		while(k>0 && Text2[i%size2]!=Text1[k])
			k = Result[k-1];
		if (Text2[i%size2]==Text1[k])
			++k;
		Result[ResultSize]=k;
		++ResultSize;
	}
}

int main(int argc, char const *argv[]) {
	vector<unsigned> pi(15000005,0);
	unsigned piSize;
	string Text1, Text2;
	cin >> Text1 >> Text2;
	if (Text1.size() != Text2.size())
	{
		cout << -1;
		return 0;
	}
   prefixEval(Text2, Text1, pi, piSize);
	#ifdef DEBUG
		for(auto i : Text2)
			cout << i;
		cout << " ";
		for(auto i : Text1)
			cout << i;
		for(auto i : Text1)
			cout << i;
		cout << endl;
		for(size_t i = 0; i < piSize; ++i)
			cout << pi[i];
		cout << endl;
	#endif
	int offset = -1;
	for (unsigned size1 = Text1.size(), i = size1+1; i < piSize; ++i)
	{
		if (pi.at(i) == size1)
		{
			offset = i - size1 - Text2.size();
			break;
		}
	}
	cout << offset;
	return 0;
}

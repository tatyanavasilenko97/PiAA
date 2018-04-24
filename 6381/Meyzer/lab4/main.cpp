#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

vector<size_t> prefixEval(string Text)
{
	vector<size_t> Result;
	Result.push_back(0);
	for(size_t i = 1; i < Text.size(); ++i)
	{
		size_t k = Result[i-1];
		while(k>0 && Text[i]!=Text[k])
			k = Result[k-1];
		if (Text[i]==Text[k])
			++k;
		Result.push_back(k);
	}
	return Result;
}

int main(int argc, char const *argv[]) {
	string Pattern, Text;
	cin >> Pattern >> Text;
	vector<size_t> pi = prefixEval(Pattern+'\0'+Text);
	list<int> Result;
	for (size_t i = 0; i < pi.size(); ++i)
		if (pi[i] == Pattern.size())
			Result.push_back(i);
	int PattSize = Pattern.size();
	for(auto i : pi)
		cout << i << " ";
	cout << endl;
	if (Result.empty())
		cout << -1;
	else
	{
		for (size_t i = 0, size=Result.size(); i < size-1; ++i)
		{
			int a = Result.front() - PattSize - PattSize;
			cout << a << ",";
			Result.pop_front();
		}
		cout << Result.front() - PattSize - PattSize;
	}
	cout << endl;

	return 0;
}

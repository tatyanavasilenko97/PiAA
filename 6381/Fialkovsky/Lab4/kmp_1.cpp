#include <iostream>
#include <string>
#include <vector>

void getPrefix(std::vector <int> &ans,  std::string const &str);

int main() {
	std::string Needle;
	std::string HayStack;
	std::vector <int> answer;
	std::vector <int> PrefixValue;
	size_t k = 0;

	std::cin >> Needle >> HayStack;

	getPrefix(PrefixValue, Needle);
	for (size_t i = 0; i < HayStack.size(); ++i) {
		while (k > 0 && (k >= Needle.size() || Needle[k] != HayStack[i]))
			k = PrefixValue[k - 1];
		if (HayStack[i] == Needle[k]) 
			k++;
		if (k == Needle.size())
			answer.push_back(i - k + 1);
	}
	if (answer.size() > 0) {
		for (size_t i = 0; i < answer.size() - 1; i++)
			std::cout << answer[i] << "," ;
		std::cout << answer.back();
	}
	else 
		std::cout << "-1" << std::endl;
	return 0;
}

void getPrefix(std::vector <int> &ans,  std::string const &str){
	ans.reserve(str.length());	            
	ans[0] = 0;
    int k = 0;	
	for (size_t i = 1; i < str.length(); i++){	
		while ((k > 0) && (str[k] != str[i])) 
			k = ans[k - 1]; 
		if (str[k] == str[i])
			k++;
		ans[i] = k;
	}
}
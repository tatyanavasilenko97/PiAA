#include <iostream>
#include <vector> 
using namespace std;
 
vector <int> KMP(string init, string search) {
	vector<int> p(search.size()); 
    vector <int> result; 
	p[0] = 0; 
    int k = 0;	
	for (int i = 1; i < search.size(); i++) {	
		while ((k > 0) && (search[k]!= search[i])) 
			k = p[k - 1]; 
		if (search[k] == search[i])
			k++;
		p[i] = k;
	}
	
    int j = 0;
    for (int i = 0; i<init.size(); i++){
        while ((j > 0) && (init[i]!= search[j])) 
			j = p[j - 1]; 
		if (init[i] == search[j])
			j++;
        if (j == search.size())
            result.push_back(i-search.size()+1);
    }
    return result; 
}

int main(){
    string init;
    string search;
    cin >> search;
    cin >> init;
    vector <int> res = KMP(init, search);
    if (res.empty())
        cout << "-1";
    else {
         for (int i = 0; i<res.size()-1; i++)
            cout << res[i] << ",";
         cout << res [res.size()-1];
    } 
}
#include <iostream>
#include <vector> 
#include <string>
using namespace std;

int KMP(string init, string search) {
	vector<int> p(search.size()); 
    int res = -1;
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
            return (i-search.size()+1);
    } 
    return -1;
}

int position (string first, string second, string f_half, string s_half, int index, int flag){
     int j = 0;
    for (int i = index+s_half.length(); i<first.length(); i++){
        if (f_half[j]== first[i])
            j++;
        else return -1;
    }
    if (j == f_half.length() && flag == 2) return index+s_half.length();
    if (j == f_half.length() && flag == 1) return index;
    int k = j;
    for (int i = 0; i<f_half.length()-k; i++){
        if (f_half[j]== first[i])
            j++;
        else return -1;
    }
    if (j == f_half.length() && flag == 2) return index+s_half.length();  
    if (j == f_half.length() && flag == 1) return index; 
        else return -1; 
}

int find_cycle (string first, string second) {
    string f_half = second.substr(0, second.length()/2);
    string s_half = second.substr(second.length()/2);
    int index = -1;

    index = KMP(first, f_half);
    if (index == -1){
         index = KMP(first, s_half);
        return position (first, second, f_half, s_half, index, 2); 
    }
  else return position (first, second, s_half, f_half, index, 1);
}

int main(){
    string first;
    string second;
    cin >> first;
    cin >> second;
    int res = find_cycle(first, second);
    cout << res;
}
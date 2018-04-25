#include <iostream>
#include <string>
#include <vector>

using namespace std;
vector<int> compute_prefix_function(const string& s) 
{
	int len = s.length();
	vector<int> p(len); 
	p[0] = 0; 

    int k = 0;	
	for (int i = 1; i < len; ++i) {	
		while ((k > 0) && (s[k] != s[i])) 
			k = p[k - 1]; 
		if (s[k] == s[i])
			++k;
		p[i] = k;
	}
	return p;
}

int main(){
    bool first=true;
    vector<int> q;
    string p,t,s;
    cin >> p;
    cin>> t;
    s=p+"@"+t;
    q=compute_prefix_function(s); 
    for(int i=p.length();i<q.size();i++){
      if(q[i]==p.length() && first) {
      cout << i-p.length()*2;
      first = false;
      }else if(q[i]==p.length())cout <<","<< i-p.length()*2;
    }
    if(first)cout <<"-1";
    return 0;
}

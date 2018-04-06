#include <iostream>
#include <vector>
using namespace std;
void pf (string &s,vector <int>&pi) { 
    for (int i=1; i<s.length(); i++) { 	
        int j = pi[i-1]; 		
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
}

int check(string &p, string &t){
   string str=t+'\n'+p+p;
   std::string().swap(p);
   vector <int>pi(str.length());
   pf(str,pi);
   for(int i=0;i<pi.size();i++)
       if(pi[i]==t.length())
         return i-2*t.length();
    return -1;    
}


int main() {
  string t,p;
  cin>>p>>t;
  cout<<check(p,t);
  return 0;
}

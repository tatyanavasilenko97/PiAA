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

void KMP(string &p, string &t){
  string str=p+'\n'+t;
  vector <int>pi(str.length());
  pf(str,pi);
  int k=0;
  int y=-1;
  for(int i=0;i<pi.size();i++)
     if(pi[i]==p.length()&&k==0){ cout<<i-2*p.length();k++;}
      else if(pi[i]==p.length()) cout<<","<<i-2*p.length();
      if(k==0)cout<<y;
}

int main() {
  string t,p;
  cin>>p>>t;
  KMP(p,t);
  return 0;
}

#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <queue>
#include <set>

using namespace std;

struct Vertex{
    map<char,Vertex*> e;
    Vertex* simpleFail= nullptr;
    vector<int> numOfPattern;
    Vertex* smartFail= nullptr;
};

void newStrInBohr(Vertex *bohr, string &str, int indexOfPattern){
    for(char ch:str){
        if(bohr->e.find(ch)!=bohr->e.end()){
            //cout<<bor<<endl;
            bohr=bohr->e.find(ch)->second;
        }
        else{
            //cout<<bor<<endl;
            Vertex *tmp=new Vertex;
            bohr->e.insert(pair<char, Vertex*>(ch,tmp));
            bohr=tmp;
        }
    }
    bohr->numOfPattern.push_back(indexOfPattern);
}

void obhod(Vertex *bohr){
    queue <Vertex *> queue;
    bohr->simpleFail=bohr;
    for (auto edge:bohr->e) {
        queue.push(edge.second);
        edge.second->simpleFail=bohr;
    }
    while (!queue.empty()){
        Vertex *tmp=queue.front();
        queue.pop();
        for (auto edge:tmp->e){
            char letter = edge.first;
            queue.push(edge.second);
            /*  if(tmp->failNode->e.find(letter) != tmp->failNode->e.end())
              {
                  tmp->failNode=tmp->failNode->e.find(letter)->second;
                  edge.second->failNode=tmp->failNode;
              }
              else {*/
            Vertex *fail = tmp->simpleFail;
            while(fail->e.find(letter)==fail->e.end()) {
                if(fail==bohr) break;
                fail=fail->simpleFail;
            }
            if(fail->e.find(letter)!=fail->e.end())
                fail=fail->e.find(letter)->second;
            edge.second->simpleFail=fail;
        }
    }
    // }
    queue.push(bohr);
    while (!queue.empty()){
        Vertex *cur=queue.front();
        queue.pop();
        for(auto edge: cur->e) queue.push(edge.second);
        if(!cur->simpleFail->numOfPattern.empty()) cur->smartFail=cur->simpleFail;
        else  cur->smartFail=cur->simpleFail->smartFail;
    }
}

void t(int *k){
    cout<<k<<endl;

}

Vertex* newBohr(vector<pair<string,int>>s) {
    Vertex *root = new Vertex();
    for (int i = 0; i < s.size(); i++) {
            newStrInBohr(root, s[i].first, s[i].second);
    }

        return root;

}

vector <int>find(string str, Vertex *bohr){
    vector <int> C(str.size());
    Vertex *cur = bohr;
    int i=0;
    for(char ch:str){
        i++;
        while (cur->e.find(ch) == cur->e.end() && cur != bohr)
            cur = cur->simpleFail;
        if (cur->e.find(ch) != cur->e.end())
            cur = cur->e.find(ch)->second;

        Vertex *tmp = cur;
        while (tmp->smartFail != nullptr) {
            tmp = tmp->smartFail;
           for(int np:tmp->numOfPattern)if(i-np>=0)C[i-np]++;
        }

            for(int np:cur->numOfPattern)
                if(i-np>=0)
                    C[i-np]++;
    }

    return C;

}

vector <pair<string,int>> subStr(string &str, char joker,int &k) {
    vector<pair<string,int>> s;
    int first = 0;
    str += joker;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == joker) {
            if (i == first) {
                first = i + 1;
                continue;
            }
            s.push_back(pair<string, int>(str.substr(first, i - first), i));
            k++;
            first = i + 1;
        }
    }
        return s;

}

int main() {
    string f ;
    vector <pair<string,int>> s;
    string pattern;
    char joker;
    cin>>f;
    cin>>pattern;
    cin>>joker;
    int k=0;
    s=subStr(pattern,joker,k);
    Vertex *bohr = newBohr(s);
    obhod(bohr);
    vector <int> C = find(f, bohr);
    vector<int> rs;
    //for (int i:y)cout<<i+1<<endl;
    for(int i=0;i<C.size();i++)if(C[i]==k)rs.push_back(i);
        for (int v:rs)cout<<v+1<<endl;

    return 0;
}
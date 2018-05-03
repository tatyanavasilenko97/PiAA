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
    int numOfPattern =-1;
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
    bohr->numOfPattern=indexOfPattern;
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
        if(cur->simpleFail->numOfPattern!=-1) cur->smartFail=cur->simpleFail;
        else  cur->smartFail=cur->simpleFail->smartFail;
    }
}

void t(int *k){
    cout<<k<<endl;
    
}

Vertex* newBohr(vector<string> &strs){
    Vertex* root=new Vertex();
    for(int i=0;i<strs.size();i++) {
        newStrInBohr(root, strs[i], i);
    }
    return root;
}

vector <pair<int,int>>find(string str, Vertex *bohr, vector<string> &strs){
    vector <pair<int,int>> res;
    Vertex *cur = bohr;
    int i=0;
    for(char ch:str) {
        i++;
        while (cur->e.find(ch) == cur->e.end() && cur != bohr)
            cur = cur->simpleFail;
        if (cur->e.find(ch) != cur->e.end())
            cur = cur->e.find(ch)->second;

        Vertex *tmp = cur;
        while (tmp->smartFail != nullptr) {
            tmp = tmp->smartFail;
            res.push_back(pair<int, int>(i - strs[tmp->numOfPattern].size(), tmp->numOfPattern));
        }

        if (cur->numOfPattern != -1) {
            res.push_back(pair<int, int>(i - strs[cur->numOfPattern].size(), cur->numOfPattern));
        }

    }

    return res;

};

int main() {
    string f ;
    vector <string> s;
    cin>>f;
    int k;
    cin>>k;
    for(int i=0;i<k;i++){
        string st;
        cin>>st;
        s.push_back(st);
    }
    Vertex *bohr = newBohr(s);
    obhod(bohr);
    vector <pair<int,int>> res = find(f, bohr, s);
    struct Comparator{
        bool operator()(pair<int,int> const & l,pair<int,int> const & r)const {
            if(l.first!=r.first)return l.first<r.first;
            return l.second<r.second;
        }
    };
    set<pair<int,int>,Comparator> resSorted;
    for(auto p:res) resSorted.insert(p);
    for(auto p:resSorted)cout<<p.first+1<<" "<<p.second+1<<"\n";
    return 0;

}

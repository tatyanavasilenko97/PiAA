#include <iostream>
#include <vector>
#include <map>
#include <list>

using namespace std;

struct Node{
    map<char,Node*> v;
    Node* failNode= nullptr;
    Node* nearPattern= nullptr;
    int patternMatched=-1;
};

Node* createBor(vector<string>& strs){
    Node* root=new Node();
    for(int i=0;i<strs.size();i++){
        string& str=strs[i];
        Node* current=root;
        for(char c:str){
            if(current->v.find(c)!=current->v.end()){
                current=current->v.find(c)->second;
            }
            else{
                Node* newNode=new Node();
                current->v.insert(pair<char,Node*>(c,newNode));
                current=newNode;
            }
        }
        current->patternMatched=i;
    }
    return root;
}

void createFails(Node* root){
    root->failNode=root;
    list<Node*> queue;
    for(auto p:root->v){
        p.second->failNode=root;
        queue.push_front(p.second);
    }
    while(!queue.empty()){
        Node* parent=*queue.begin();
        queue.pop_front();
        for(auto n:parent->v){
            char letter=n.first;
            Node* child=n.second;
            queue.push_front(child);
            ////////////////////////
            Node* failNode=parent->failNode;
            while (failNode->v.find(letter)==failNode->v.end() && failNode!= root){
                failNode=failNode->failNode;
            }
            if(failNode->v.find(letter)!=failNode->v.end())failNode=failNode->v.find(letter)->second;
            child->failNode=failNode;
        }
    }
}

void createSubPatterns(Node* root) {
    list<Node *> queue={root};
    while (!queue.empty()) {
        Node *current = *queue.begin();
        queue.pop_front();
        for(auto child:current->v)queue.push_back(child.second);
        if(current->failNode->patternMatched!=-1)current->nearPattern=current->failNode;
        else current->nearPattern=current->failNode->nearPattern;
    }
}

vector<pair<int,int>> findPatterns(string str, Node* root, vector<string>& strs){
    vector<pair<int,int>> res;
    Node* current=root;
    for(int i=0;i<str.size();i++){
        char c=str[i];
        while(current->v.find(c)==current->v.end()&&current!=root){
            current=current->failNode;
        }
        if(current->v.find(c)!=current->v.end())current=current->v.find(c)->second;
        Node *t=current;
        while(t->nearPattern!= nullptr){
            t=t->nearPattern;
            res.push_back(pair<int,int>(i-strs[t->patternMatched].size()+1,t->patternMatched));
        }
        if(current->patternMatched!=-1){
            res.push_back(pair<int,int>(i-strs[current->patternMatched].size()+1,current->patternMatched));
        }
    }
    return res;
};

int main() {
    vector<string> strs{"vab","better","spl","ert","tri","plus","tt","t","luspl","lu","aab","aa"};
    Node* n=createBor(strs);
    createFails(n);
    createSubPatterns(n);
    vector<pair<int,int>> res=findPatterns("myjavabetterthancplusplusplaab",n,strs);
    for(auto p:res)cout<<p.first<<" "<<strs[p.second]<<"\n";
    return 0;
}
#include <iostream>
#include <fstream>
using  namespace std;
//using namespace std;
const int SIZE = 300;
const int noPath = -10000000;
const int inPath = 0;


int n;
int c[SIZE][SIZE];
int prevs[SIZE];
int p[SIZE];
bool visited[SIZE];
int flow[SIZE][SIZE];
int finish,start;
bool v[SIZE][SIZE];
void read(istream& cin){
    cin>>n;cin.get();
    start=cin.get()-'a';cin.get();
    finish=cin.get()-'a';cin.get();

    while (cin){
        int v1=cin.get()-'a';cin.get();
        int v2=cin.get()-'a';cin.get();
        int cost;cin>>cost;
        c[v1][v2] = cost;
        v[v1][v2] = true;
        cin.get();
    }
}
void dfs(int v){
    visited[v]=true;
    if(v==finish)
        return ;
    for(int i=0;i<SIZE;i++)
        if(!visited[i] && (c[v][i]-flow[v][i]>0&&c[v][i]!=0 || flow[v][i]<0&&c[i][v]!=0)){
            prevs[i]=v;
            //cout<<(char)(i+'a');
            dfs(i);
        }
}

bool getPath(int v){
    dfs(v);
    for (int i=0;i<SIZE;i++)
        visited[i]= false;

    return (prevs[finish]!=noPath);
}

void initPrevs(){
    for(int i=0;i<SIZE;i++)
        prevs[i]=noPath;
}

int FF(){

    int maxFlow=0;
    for (int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++) {
            flow[i][j] = 0;
        }
    while (getPath(start)){
        int tmp=100000;
        for (int v=finish;prevs[v]>=0;v=prevs[v]){
            tmp=min(tmp,c[prevs[v]][v]-flow[prevs[v]][v]);
           
        }
        for (int v=finish;prevs[v]>=0;v=prevs[v]){
            flow[prevs[v]][v]+=tmp;
            flow[v][prevs[v]]-=tmp;
          
        }
        //cout<<1<<endl;
        maxFlow+=tmp;
        //cout<<tmp<<" "<<maxFlow<<endl;
        initPrevs();
    }
    return maxFlow;
}
int main() {
    for(int i=0;i< SIZE;i++)
        for (int j = 0; j < SIZE; ++j) {
            c[i][j] = inPath;
            v[i][j]=false;
        }
    initPrevs();
    //ifstream cin("../input.txt");
    //if(!cin) exit(123);
    read(cin);

    cout<<FF()<<endl;
    for (int i=0;i<SIZE;i++)
        for (int j=0;j<SIZE;j++)
            if(v[i][j]==true)cout <<(char)(i+'a')<<" "<<(char)(j+'a')<<" "<<flow[i][j] <<endl;

    return 0;
}

#include <iostream>
#include <cfloat>
#include <fstream>
#include <list>
#include <vector>
#include <set>

using namespace std;

const int V=50;
const double INFINITY= DBL_MAX*2;
int startV;
int finishV;

struct Vertex;

struct Edge{
    const double w;
    Vertex* const to;
};

struct Vertex{
    int n;
    double pathFromStart=INFINITY;
    Vertex* prevBestVertex= nullptr;
    list<Edge> e;
};

struct Comparator {
    bool operator()(Vertex * const &l,  Vertex * const &r) const {
        if (l->pathFromStart != r->pathFromStart)return l->pathFromStart < r->pathFromStart;
        return l->n < r->n;
    }
};

Vertex vert[V];


void read(istream& cin){
    for(int i=0;i<V;i++)vert[i].n=i;
    startV=cin.get()-'a';
    cin.get();
    finishV=cin.get()-'a';
    cin.get();
    vert[startV].pathFromStart=0;
    while(true){
        int v1=cin.get()-'a';
        cin.get();
        int v2=cin.get()-'a';
        cin.get();
        double cost;
        cin>>cost;
        vert[v1].e.push_back({cost,&vert[v2]});
        if(cin.eof())return;
        cin.get();
    }
}

void deicstra(){
    std::set<Vertex*,Comparator> queue;
    for(Vertex& v:vert)queue.insert(&v);
    while(!queue.empty()){
        Vertex* current=*queue.begin();
        if(current->pathFromStart==INFINITY)return;
        queue.erase(current);
        for(Edge& e:current->e){
            if(e.to->pathFromStart>=e.w+current->pathFromStart){
                queue.erase(e.to);
                e.to->pathFromStart=e.w+current->pathFromStart;
                e.to->prevBestVertex=current;
                queue.insert(e.to);
            }
        }
    }
}

void printResult(Vertex* start,Vertex* finish){
    if(start==finish){
        cout<<(char)(start->n+'a');
        return;
    }
    printResult(start,finish->prevBestVertex);
    cout<<(char)(finish->n+'a');
}

int main() {
    ifstream ifs("../input4.txt");if(!ifs)exit(123);
    read(ifs);
    deicstra();
    printResult(&vert[startV],&vert[finishV]);
    return 0;
}